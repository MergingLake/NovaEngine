#pragma once

#include "Prerequisites.h"
#include "ECS/Component.h"
#include "Rendering/RenderTypes.h"

class DeviceContext;

/**
 * @class LightComponent
 * @brief Componente que representa una fuente de luz en la escena.
 *
 * Este componente almacena información sobre el tipo de luz, color, intensidad,
 * dirección, posición y otros parámetros relevantes para el cálculo de iluminación
 * en el motor de renderizado.
 */
class
	LightComponent : public Component {
public:
	LightComponent()
		: Component(ComponentType::NONE) {
	}

	/*
	* @brief Constructor que inicializa el componente de luz con un tipo específico.
	* @param type Tipo de luz a configurar en el componente.
	*/
	void init() override {}

	/*
	* @brief Actualiza el componente de luz en cada frame.
	* @param deltaTime Tiempo transcurrido desde la última actualización.
	* @param deviceContext Contexto del dispositivo para operaciones gráficas.
	*/
	void update(float deltaTime) override {}

	/*
	* @brief Renderiza la luz en la escena.
	* @param deviceContext Contexto del dispositivo para operaciones gráficas.
	*/
	void render(DeviceContext& deviceContext) override {}

	/*
	* @brief Destruye el componente de luz, liberando recursos si es necesario.
	*/
	void destroy() override {}

	/*
	* @brief Obtiene una referencia a los datos de la luz almacenados en el componente.
	* @return Referencia a la estructura LightData que contiene los parámetros de la luz.
	*/
	LightData& getLightData() { return m_light; }

	/*
	* @brief Obtiene una referencia constante a los datos de la luz almacenados en el componente.
	* @return Referencia constante a la estructura LightData que contiene los parámetros de la luz.
	*/
	const LightData& getLightData() const { return m_light; }

	/*
	* @brief Establece si la luz proyecta sombras.
	* @param value Valor booleano que habilita o deshabilita la proyección de sombras para esta luz.
	* @return @c true si la luz proyecta sombras; @c false en caso contrario.
	*/
	void setCastShadow(bool value) { m_castShadow = value; }

	/*
	* @brief Indica si la luz proyecta sombras.
	* @return @c true si la luz proyecta sombras; @c false en caso contrario.
	*/
	bool canCastShadow() const { return m_castShadow; }

	/*
	 * @brief Crea una copia profunda del LightComponent.
	 */
	EU::TSharedPointer<Component> clone() const override {
		LightComponent* clonedRaw = new LightComponent();

		clonedRaw->getLightData() = this->getLightData();
		clonedRaw->setCastShadow(this->canCastShadow());

		return EU::TSharedPointer<Component>(clonedRaw);
	}

private:
	LightData m_light;
	bool m_castShadow = false;
};