#pragma once
#include "Prerequisites.h"
#include "ECS/Component.h"

class DeviceContext;
class Entity;

/*
	@class HierarchyComponent
	@brief A component that manages the hierarchical relationships between entities in a scene graph.
	@note The HierarchyComponent class is responsible for maintaining parent-child relationships between entities, allowing for hierarchical transformations and rendering in a scene graph structure.
*/
class HierarchyComponent : public Component {
public:
	/* 
		@brief Default constructor that initializes the component type to HIERARCHY.
	*/
	HierarchyComponent() : Component(ComponentType::HIERARCHY) {}
	/* 
		@brief Destructor
	*/
	~HierarchyComponent() = default;

	/* 
		@brief Initializes the hierarchy component.
		@details This method can be used to set up any necessary data structures or state for managing the hierarchy of entities. In this implementation, it simply initializes the parent pointer and clears the list of children.
	*/
	void
		init() override {}

	/* 
		@brief Updates the hierarchy component.
		@details This method can be used to perform any necessary updates to the hierarchy of entities, such as recalculating world transformations based on parent-child relationships. In this implementation, it does not perform any specific updates, but it can be extended in the future to include such functionality.
		@param deltaTime The time elapsed since the last update, which can be used for time-based animations or movements if needed.
	*/
	void
		update(float) override {}

	/* 
		@brief Renders the hierarchy component.
		@details This method can be used to perform any necessary rendering related to the hierarchy of entities, such as visualizing parent-child relationships or rendering debug information. In this implementation, it does not perform any specific rendering, but it can be extended in the future to include such functionality.
		@param deviceContext The device context to use for rendering, which can be used to issue draw calls or set rendering states if needed.
	*/
	void
		render(DeviceContext& deviceContext) override {}

	/* 
		@brief Destroys the hierarchy component and releases associated resources.
		@details This method should be called when the hierarchy component is no longer needed to clean up any resources and ensure proper memory management. In this implementation, it clears the list of children and resets the parent pointer to nullptr.
	*/
	void
		destroy() override {
		m_children.clear();
		m_parent = nullptr;
	}

	/* 
		@brief Sets the parent entity for this hierarchy component.
		@details This method establishes a parent-child relationship between this entity and the specified parent entity. It updates the parent pointer and can also be used to manage the list of children in the parent entity if needed.
		@param parent A pointer to the entity that will be set as the parent of this entity.
	*/
	// API SceneGraph
	void
		setParent(Entity* parent) {
		m_parent = parent;
	}

	/* 
		@brief Checks if this entity is a root entity in the scene graph.
		@details This method returns true if this entity does not have a parent, indicating that it is a root entity in the scene graph. Root entities are typically the top-level entities that do not have any parent-child relationships above them.
		@return true if this entity is a root entity, false otherwise.
	*/
	bool 
		isRoot() const {
		return m_parent == nullptr;
	}

	/* 
		@brief Checks if this entity has any child entities.
		@details This method returns true if the list of child entities is not empty, indicating that this entity has one or more child entities in the scene graph. Child entities are typically those that are attached to a parent entity and may inherit transformations or other properties from their parent.
		@return true if this entity has child entities, false otherwise.
	*/
	bool 
		hasChildren() const {
		return !m_children.empty();
	}

	/* 
		@brief Adds a child entity to this hierarchy component.
		@details This method establishes a parent-child relationship between this entity and the specified child entity. It updates the list of children and can also be used to set the parent pointer in the child entity if needed.
		@param child A pointer to the entity that will be added as a child of this entity.
	*/
	void
		addChild(Entity* child) {
		if (!child) {
			return;
		}

		if (std::find(m_children.begin(), m_children.end(), child) != m_children.end()) {
			return;
		}
		m_children.push_back(child);
	}

	/* 
		@brief Removes a child entity from this hierarchy component.
		@details This method removes the parent-child relationship between this entity and the specified child entity. It updates the list of children and can also be used to reset the parent pointer in the child entity if needed.
		@param child A pointer to the entity that will be removed as a child of this entity.
	*/
	void
		removeChild(Entity* child) {
		if (!child) return;

		m_children.erase(
			std::remove(m_children.begin(), m_children.end(), child),
			m_children.end()
		);
	}

public:
	Entity* m_parent = nullptr;
	std::vector<Entity*> m_children;
};