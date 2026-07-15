#pragma once
#include "Prerequisites.h"
#include "ECS/Component.h"

// Forward declarations
class DeviceContext;

class
	MeshComponent : public Component {
public:
	/**
	 * @brief Default constructor. Initializes vertex and index counts to zero.
	 */
	MeshComponent() : m_numVertex(0), m_numIndex(0), Component(ComponentType::MESH) {}

	/**
	 * @brief Virtual destructor.
	 */
	virtual
		~MeshComponent() = default;

	/**
	 * @brief Initializes the mesh component.
	 * @note Can be used to load mesh data from a file (e.g., .obj, .fbx)
	 * or to procedurally generate geometry.
	 */
	void
		init() override {};

	/**
	 * @brief Per-frame update logic for the mesh.
	 * @note Useful for CPU-side procedural mesh manipulation or animation.
	 * @param deltaTime Time elapsed since the last frame.
	 */
	void
		update(float deltaTime) override {};

	/**
	 * @brief Issues the final draw call for this mesh.
	 * @note This method assumes that the associated Vertex and Index buffers
	 * have already been bound to the pipeline by another system. It simply
	 * calls DrawIndexed using the stored index count.
	 * @param deviceContext The device context to issue the draw command.
	 */
	void
		render(DeviceContext& deviceContext) override {};

	/**
	 * @brief Clears the CPU-side vertex and index data.
	 */
	void
		destroy() override {};

	/**
	 * @brief Crea una copia profunda de la data del MeshComponent.
	 */
	EU::TSharedPointer<Component> clone() const override {
		MeshComponent* clonedRaw = new MeshComponent();

		clonedRaw->m_name = this->m_name;
		clonedRaw->m_localTransform = this->m_localTransform;
		clonedRaw->m_vertex = this->m_vertex;
		clonedRaw->m_skyVertex = this->m_skyVertex;
		clonedRaw->m_index = this->m_index;
		clonedRaw->m_numVertex = this->m_numVertex;
		clonedRaw->m_numIndex = this->m_numIndex;

		return EU::TSharedPointer<Component>(clonedRaw);
	}

public:
	std::string m_name;
	XMFLOAT4X4 m_localTransform = XMFLOAT4X4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
	std::vector<SimpleVertex> m_vertex;
	std::vector<SkyboxVertex> m_skyVertex;
	std::vector<unsigned int> m_index;
	int m_numVertex;
	int m_numIndex;
};