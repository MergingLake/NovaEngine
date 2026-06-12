#pragma once

#include "Prerequisites.h"
#include "ECS/Component.h"

class Mesh;
class MaterialInstance;
class DeviceContext;

/*
* @class MeshRendererComponent
* @brief Componente que representa la capacidad de renderizar una malla en la escena.
*
* Este componente almacena una referencia a una malla y a una o varias instancias de material,
* así como información sobre visibilidad y capacidad de proyectar sombras. Es responsable de
* configurar los recursos necesarios para renderizar la malla con los materiales asignados.
*/
class
	MeshRendererComponent : public Component {
public:
	MeshRendererComponent()
		: Component(ComponentType::MESH) {
	}

	/*
	* @brief Inicializa el componente de renderizado de malla.
	*/
	void init() override {}

	/*
	* @brief Actualiza el componente de renderizado de malla en cada frame.
	* @param deltaTime Tiempo transcurrido desde la última actualización.
	* @param deviceContext Contexto del dispositivo para operaciones gráficas.
	*/
	void update(float deltaTime) override {}

	/*
	* @brief Renderiza la malla asociada al componente en la escena.
	* @param deviceContext Contexto del dispositivo para operaciones gráficas.
	*/
	void render(DeviceContext& deviceContext) override {}

	/*
	* @brief Destruye el componente de renderizado de malla, liberando recursos si es necesario.
	*/
	void destroy() override {}

	/*
	* @brief Establece la malla que se renderizará con este componente.
	* @param mesh Puntero a la malla que se asignará al componente.
	*/
	void setMesh(Mesh* mesh) { m_mesh = mesh; }

	/*
	* @brief Obtiene la malla actualmente asignada al componente.
	* @return Puntero a la malla asignada al componente, o nullptr si no se ha asignado ninguna malla.
	*/
	Mesh* getMesh() const { return m_mesh; }

	/*
	* @brief Establece la instancia de material que se usará para renderizar la malla.
	* @param materialInstance Puntero a la instancia de material que se asignará al componente.
	*/
	void setMaterialInstance(MaterialInstance* materialInstance) {
		m_materialInstance = materialInstance;
		m_materialInstances.clear();
		if (materialInstance) {
			m_materialInstances.push_back(materialInstance);
		}
	}

	/*
	* @brief Obtiene la instancia de material actualmente asignada al componente.
	* @return Puntero a la instancia de material asignada al componente, o nullptr si no se ha asignado ninguna instancia de material.
	*/
	MaterialInstance* getMaterialInstance() const { return m_materialInstance; }

	/*
	* @brief Establece las instancias de material que se usarán para renderizar la malla.
	* @param materialInstances Vector de punteros a instancias de material que se asignarán al componente. La primera instancia del vector se usará como instancia de material principal.
	*/
	void setMaterialInstances(const std::vector<MaterialInstance*>& materialInstances) {
		m_materialInstances = materialInstances;
		m_materialInstance = m_materialInstances.empty() ? nullptr : m_materialInstances.front();
	}

	/*
	* @brief Agrega una instancia de material adicional para renderizar la malla.
	* @param materialInstance Puntero a la instancia de material que se agregará al componente. Si no se ha asignado una instancia de material principal, esta instancia se establecerá como la principal.
	*/
	void addMaterialInstance(MaterialInstance* materialInstance) {
		if (!materialInstance) {
			return;
		}
		if (!m_materialInstance) {
			m_materialInstance = materialInstance;
		}
		m_materialInstances.push_back(materialInstance);
	}

	/*
	* @brief Obtiene las instancias de material actualmente asignadas al componente.
	* @return Vector de punteros a las instancias de material asignadas al componente. El primer elemento del vector es la instancia de material principal.
	*/
	const std::vector<MaterialInstance*>& getMaterialInstances() const { return m_materialInstances; }

	/*
	* @brief Establece si la malla es visible en la escena.
	* @param visible Valor booleano que habilita o deshabilita la visibilidad de la malla.
	* @return Valor booleano que indica si la malla es visible en la escena.
	*/
	bool isVisible() const { return m_visible; }

	/*
	* @brief Establece si la malla es visible en la escena.
	* @param visible Valor booleano que habilita o deshabilita la visibilidad de la malla.
	* @return void
	*/
	void setVisible(bool visible) { m_visible = visible; }

	/*
	* @brief Establece si la malla proyecta sombras en la escena.
	* @param value Valor booleano que habilita o deshabilita la proyección de sombras para esta malla.
	* @return Valor booleano que indica si la malla proyecta sombras en la escena.
	*/
	bool canCastShadow() const { return m_castShadow; }

	/*
	* @brief Establece si la malla proyecta sombras en la escena.
	* @param value Valor booleano que habilita o deshabilita la proyección de sombras para esta malla.
	* @return void
	*/
	void setCastShadow(bool value) { m_castShadow = value; }

private:
	Mesh* m_mesh = nullptr;
	MaterialInstance* m_materialInstance = nullptr;
	std::vector<MaterialInstance*> m_materialInstances;
	bool m_visible = true;
	bool m_castShadow = true;
};