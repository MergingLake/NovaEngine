#pragma once
#include "Prerequisites.h"
#include "EngineUtilities/Vectors/Vector3.h"
#include "Component.h"

/*
 * @class Transform
 * @brief Componente que representa la posición, rotación y escala de una entidad en el espacio 3D.
 * El componente Transform es fundamental para cualquier entidad que deba ser posicionada, rotada o escalada en la escena. Proporciona métodos para actualizar su estado y calcular la matriz de transformación final que se utilizará en el renderizado.
 */
class
  Transform : public Component {
public:
  /*
	* @brief Constructor por defecto que inicializa el componente Transform con valores predeterminados.
	* La posición se inicializa en el origen (0, 0, 0), la rotación se inicializa sin rotación (0, 0, 0) y la escala se inicializa a 1 (sin escalado). La matriz de transformación se inicializa como la matriz identidad.
  */
  Transform() : position(),
    rotation(),
    scale(),
    matrix(),
    Component(ComponentType::TRANSFORM) {
  }

  /*
	* @brief Inicializa el componente Transform con valores predeterminados.
  */
  void
    init() {
    scale.one();
    matrix = XMMatrixIdentity();
  }

  /*
	* @brief Actualiza el componente Transform calculando la matriz de transformación final.
	* Este método debe ser llamado cada vez que se modifiquen la posición, rotación o escala para asegurar que la matriz de transformación esté actualizada. La matriz se compone aplicando primero la escala, luego la rotación y finalmente la traslación.
	* @param deltaTime El tiempo transcurrido desde la última actualización, que puede ser utilizado para animaciones o cambios dependientes del tiempo (aunque en este caso no se utiliza directamente).
  */
  void
    update(float deltaTime) override {
    // Aplicar escala
    XMMATRIX scaleMatrix = XMMatrixScaling(scale.x, scale.y, scale.z);
    // Aplicar rotacion
    XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
    // Aplicar traslacion
    XMMATRIX translationMatrix = XMMatrixTranslation(position.x, position.y, position.z);

    // Componer la matriz final en el orden: scale -> rotation -> translation
    matrix = scaleMatrix * rotationMatrix * translationMatrix;
  }

  /*
	* @brief Renderiza el componente Transform.
	* En el caso del componente Transform, no se realiza ninguna operación de renderizado directa, ya que su función principal es proporcionar la matriz de transformación para otros componentes que sí realizan renderizado. Sin embargo, este método puede ser utilizado para depuración o visualización de gizmos en el editor.
	* @param deviceContext Contexto del dispositivo para operaciones gráficas, que podría ser utilizado para renderizar gizmos o visualizaciones relacionadas con el transform.
  */
  void
    render(DeviceContext& deviceContext) override {}

	/*
	* @brief Destruye el componente Transform y libera cualquier recurso asociado.
	* En el caso del componente Transform, no se utilizan recursos dinámicos que requieran liberación, por lo que este método no realiza ninguna operación específica. Sin embargo, es importante implementarlo para cumplir con la interfaz de Component y permitir una posible extensión futura donde se puedan agregar recursos asociados al transform.
  */
  void
    destroy() {}
  
  /*
	* @brief Métodos de acceso a los datos de posición
	* Retorna la posición actual del objeto
	* @return La posición actual del objeto como un vector 3D.
  */
  const EU::Vector3&
    getPosition() const { return position; }

  /*
	* @brief Establece una nueva posición para el objeto.
	* @param newPos La nueva posición a asignar al objeto, representada como un vector 3D.
  */
  void
    setPosition(const EU::Vector3& newPos) { position = newPos; }

  /*
	* @brief Métodos de acceso a los datos de rotación
	* Retorna la rotación actual del objeto
	* @return La rotación actual del objeto como un vector 3D, donde cada componente representa la rotación en grados alrededor de los ejes X, Y y Z respectivamente.
  */
  const EU::Vector3&
    getRotation() const { return rotation; }

  /*
	* @brief Establece una nueva rotación para el objeto.
	* @param newRot La nueva rotación a asignar al objeto, representada como un vector 3D, donde cada componente representa la rotación en grados alrededor de los ejes X, Y y Z respectivamente.
  */
  void
    setRotation(const EU::Vector3& newRot) { rotation = newRot; }

  /*
	* @brief Métodos de acceso a los datos de escala
	* Retorna la escala actual del objeto
	* @return La escala actual del objeto como un vector 3D, donde cada componente representa la escala en los ejes X, Y y Z respectivamente.
  */
  const EU::Vector3&
    getScale() const { return scale; }

  /*
	* @brief Establece una nueva escala para el objeto.
	* @param newScale La nueva escala a asignar al objeto, representada como un vector 3D, donde cada componente representa la escala en los ejes X, Y y Z respectivamente. Un valor de 1 significa sin escalado, valores mayores que 1 aumentan el tamaño y valores menores que 1 lo reducen.
  */
  void
    setScale(const EU::Vector3& newScale) { scale = newScale; }

  /*
	* @brief Establece la posición, rotación y escala del objeto en una sola llamada.
	* @param newPos La nueva posición a asignar al objeto, representada como un vector 3D.
	* @param newRot La nueva rotación a asignar al objeto, representada como un vector 3D, donde cada componente representa la rotación en grados alrededor de los ejes X, Y y Z respectivamente.
	* @param newSca La nueva escala a asignar al objeto, representada como un vector 3D, donde cada componente representa la escala en los ejes X, Y y Z respectivamente. Un valor de 1 significa sin escalado, valores mayores que 1 aumentan el tamaño y valores menores que 1 lo reducen.
  */
  void
    setTransform(const EU::Vector3& newPos,
      const EU::Vector3& newRot,
      const EU::Vector3& newSca) {
    position = newPos;
    rotation = newRot;
    scale = newSca;
  }

  /*
	* @brief Aplica una traslación incremental a la posición actual del objeto.
	* Este método suma el vector de traslación proporcionado a la posición actual, permitiendo mover el objeto en el espacio sin necesidad de establecer una posición absoluta.
	* @param translation El vector de traslación a aplicar, representado como un vector 3D. Cada componente del vector se suma a la posición actual en los ejes X, Y y Z respectivamente.
  */
  void
    translate(const EU::Vector3& translation);

private:
  EU::Vector3 position;  // Posición del objeto
  EU::Vector3 rotation;  // Rotación del objeto
  EU::Vector3 scale;     // Escala del objeto

public:
  XMMATRIX matrix;    // Matriz de transformación
};