#pragma once
#include "Prerequisites.h"

class Entity;
class DeviceContext;

/*
	@class SceneGraph
	@brief A class that manages a hierarchical structure of entities in a scene.
	@note The SceneGraph class is responsible for managing the relationships between entities, updating their states, and rendering them in the correct order based on their hierarchy.
*/
class
	SceneGraph {
public:
	/* 
		@brief Default constructor
	*/
	SceneGraph() = default;
	/* 
		@brief Destructor
	*/
	~SceneGraph() = default;
	
	/* 
		@brief Initializes the scene graph.
	*/
	void
		init();

	/* 
		@brief Adds an entity to the scene graph.
		@details This method registers an entity in the scene graph, allowing it to be managed and rendered as part of the scene.
		@param e A pointer to the entity to add to the scene graph.
	*/
	void
		addEntity(Entity* e);  // registra en el grafo

	/*
		@brief Removes an entity from the scene graph.
		@details This method unregisters an entity from the scene graph, removing it from management and rendering.
		@param e A pointer to the entity to remove from the scene graph.
	*/
	void
		removeEntity(Entity* e);

	/* 
		@brief Checks if a given entity is an ancestor of another entity in the scene graph.
		@details This method traverses the hierarchy of entities to determine if the possibleAncestor is an ancestor of the node.
		@param possibleAncestor A pointer to the entity that may be an ancestor.
		@param node A pointer to the entity that may be a descendant.
		@return true if possibleAncestor is an ancestor of node, false otherwise.
	*/
	bool
		isAncestor(Entity* possibleAncestor, Entity* node) const;

	/* 
		@brief Attaches a child entity to a parent entity in the scene graph.
		@details This method establishes a parent-child relationship between two entities, allowing the child to inherit transformations and be rendered as part of the parent's hierarchy.
		@param child A pointer to the entity that will become the child.
		@param parent A pointer to the entity that will become the parent.
		@return true if the attachment was successful, false if it failed (e.g., due to invalid entities or circular relationships).
	*/
	bool
		attach(Entity* child, Entity* parent);

	/* 
		@brief Detaches a child entity from its parent in the scene graph.
		@details This method removes the parent-child relationship between an entity and its parent, allowing the child to become a root entity in the scene graph.
		@param child A pointer to the entity that will be detached from its parent.
		@return true if the detachment was successful, false if it failed (e.g., if the child was not attached to any parent).
	*/
	bool
		detach(Entity* child);

	/* 
		@brief Updates the scene graph.
		@details This method traverses the hierarchy of entities in the scene graph and updates their states based on their transformations and relationships. It should be called once per frame to ensure that all entities are updated correctly.
		@param deltaTime The time elapsed since the last update, used for time-based animations and movements.
		@param deviceContext The device context to use for any necessary rendering or resource updates during the update process.
	*/
	void
		update(float deltaTime, DeviceContext& deviceContext);
	
	/* 
		@brief Renders the scene graph.
		@details This method traverses the hierarchy of entities in the scene graph and renders them in the correct order based on their transformations and relationships. It should be called once per frame after the update method to ensure that all entities are rendered correctly.
		@param deviceContext The device context to use for rendering the entities in the scene graph.
	*/
	void
		render(DeviceContext& deviceContext);
	/* 
		@brief Destroys the scene graph and releases associated resources.
		@details This method should be called when the scene graph is no longer needed to clean up any resources and ensure proper memory management.
	*/
	void
		destroy();

private:
	/* 
		@brief Recursively updates the world transformations of entities in the scene graph.
		@details This method is called internally by the update method to traverse the hierarchy of entities and update their world transformations based on their local transformations and their parent's world transformations.
		@param node A pointer to the current entity being updated.
		@param parentWorld The world transformation matrix of the parent entity, used to calculate the world transformation of the current entity.
	*/
	void
		updateWorldRecursive(Entity* node, const XMMATRIX& parentWorld);

	/* 
		@brief Recursively renders entities in the scene graph.
		@details This method is called internally by the render method to traverse the hierarchy of entities and render them in the correct order based on their transformations and relationships.
		@param node A pointer to the current entity being rendered.
		@param deviceContext The device context to use for rendering the current entity.
	*/
	bool
		isRoot(Entity* e) const;

	/* 
		@brief Checks if a given entity is registered in the scene graph.
		@details This method checks if the specified entity is part of the scene graph's list of entities, which indicates that it is being managed and rendered as part of the scene.
		@param e A pointer to the entity to check for registration.
		@return true if the entity is registered in the scene graph, false otherwise.
	*/
	bool
		isRegistered(Entity* e) const;

private:
	//std::vector<EU::TSharedPointer<Entity>> m_entities;
public:
	std::vector<Entity*> m_entities;
};