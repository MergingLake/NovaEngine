#pragma once
#include "Prerequisites.h"
#include "Rendering/RenderTypes.h"

// Forward Declaration
class Skybox;

/*
 * @struct RenderObject
 * @brief The RenderObject structure represents an individual object in the render scene, containing a reference to its mesh and material instance. It serves as a container for the geometry and material information needed to render the object in the scene.
 * @details The RenderObject structure includes a pointer to a Mesh object that defines the geometry of the object and a pointer to a MaterialInstance that specifies the material properties and textures to be used when rendering this object. This structure is used within the RenderScene to organize and manage the objects that need to be rendered, allowing for efficient rendering operations based on their associated meshes and materials.
 */
class 
RenderScene {
public:
	/* 
	 * @brief Clears the render scene by removing all objects and lights, and resetting the skybox reference.
	 * @details This method clears the render scene by emptying the vectors of opaque and transparent objects, as well as the vector of directional lights. It also resets the pointer to the skybox to nullptr. This is typically called at the beginning of each frame to prepare the scene for new objects and lighting information to be added for rendering.
	 * @return void
	 */
	void
	clear();

public:
	std::vector<RenderObject> opaqueObjects;
	std::vector<RenderObject> transparentObjects;
	std::vector<LightData> directionalLights;
	Skybox* skybox = nullptr;
};