#pragma once
#include "ECS/Component.h"
#include "ECS/Transform.h"
#include "Logger.h"
#include <sol/sol.hpp>
#include <string>

class LuaScriptComponent : public Component {
public:
  std::string filepath;             // La ruta del archivo .lua
  sol::environment env;             // Entorno aislado para que los scripts no mezclen variables
  sol::function updateFunction;     // Guardamos la función Update para llamarla rápido cada frame
  Transform* transformPtr = nullptr; // Referencia al Transform de este Actor

  // Le pasamos el enum SCRIPT que creaste en Prerequisites.h
  LuaScriptComponent() : Component(ComponentType::SCRIPT) {}
  ~LuaScriptComponent() = default;

  void
    init() override {};

  void 
    update(float deltaTime) override {}

  void 
    render(DeviceContext& deviceContext) override {}

  void
    destroy() override {};

  // Para cuando dupliques un objeto en el editor
  EU::TSharedPointer<Component> clone() const override {
    auto cloned = new LuaScriptComponent();
    cloned->filepath = this->filepath;
    return EU::TSharedPointer<Component>(cloned);
  }

  // Inicializa el script (Se llama al darle Play)
  void startScript(sol::state& luaState, Transform* actorTransform) {
    transformPtr = actorTransform;

    // Creamos un entorno único para este script (como un "sandbox")
    env = sol::environment(luaState, sol::create, luaState.globals());

    // ¡Magia! Inyectamos el puntero de C++ dentro del script de Lua con el nombre "transform"
    env["transform"] = transformPtr;

    try {
      // Cargamos y ejecutamos el archivo una vez para leer sus funciones
      luaState.script_file(filepath, env);

      // Buscamos si el usuario escribió un function Start()
      sol::function startFunction = env["Start"];
      if (startFunction.valid()) {
        startFunction(); // Lo ejecutamos
      }

      // Guardamos el function Update(deltaTime) para usarlo en el bucle
      updateFunction = env["Update"];

    }
    catch (const sol::error& e) {
      Logger::Get().LogRaw("LuaScript", e.what(), LogLevel::Error);
    }
  }

  // Se llama cada frame durante el estado PLAY
  void executeUpdate(float deltaTime) {
    if (updateFunction.valid()) {
      try {
        updateFunction(deltaTime); // Le pasamos el deltaTime de C++ a Lua
      }
      catch (const sol::error& e) {
        Logger::Get().LogRaw("LuaScript", e.what(), LogLevel::Error);
      }
    }
  }
};