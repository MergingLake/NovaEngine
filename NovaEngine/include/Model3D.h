#pragma once
#include "Prerequisites.h"
#include "IResource.h"
#include "MeshComponent.h"
#include "fbxsdk.h"

/*
* @class Model3D
* @brief A class that represents a 3D model resource, capable of loading and managing 3D model data from files such as OBJ and FBX.
*/
enum
	ModelType {
	OBJ,
	FBX
};

class
	Model3D : public IResource {
public:
	/*
	* @brief Constructor that initializes the Model3D resource with a name and model type, and loads the model data from the specified file.
	* @param name The name of the model resource, typically the file path to the model.
	* @param modelType The type of the model (e.g., OBJ, FBX) to determine the loading method.
	*/
	Model3D(const std::string& name, ModelType modelType)
		: IResource(name), m_modelType(modelType), lSdkManager(nullptr), lScene(nullptr) {
		SetType(ResourceType::Model3D);
		load(name);
	}

	/*
	* @brief Constructor that initializes the Model3D resource with a name and raw vertex and index data for a skybox model.
	* @param name The name of the model resource.
	* @param vertices An array of SkyboxVertex structures representing the vertices of the skybox model.
	* @param indices An array of unsigned integers representing the indices for the skybox model's vertex data.
	*/
	Model3D(const std::string& name,
		const SkyboxVertex vertices[],
		const unsigned int indices[]) : IResource(name) {
		MeshComponent mesh;
		mesh.m_skyVertex.assign(vertices, vertices + 8);
		mesh.m_index.assign(indices, indices + 36);
		mesh.m_numIndex = mesh.m_index.size();
		SetType(ResourceType::Model3D);
		m_meshes.push_back(mesh);
	}

	/*
	* @brief Destructor for the Model3D class, responsible for cleaning up any resources associated with the model.
	*/
	~Model3D() = default;

	/*
	* @brief Loads the model data from the specified file path, using the appropriate loading method based on the model type.
	* @param path The file path to the model to be loaded.
	* @return True if the model was successfully loaded, false otherwise.
	*/
	bool
		load(const std::string& path) override;

	/*
	* @brief Initializes the model resource, creating any necessary GPU resources or performing additional setup after loading the model data.
	* @return True if the initialization was successful, false otherwise.
	*/
	bool
		init() override;

	/*
	* @brief Unloads the model resource, releasing any associated resources and clearing loaded data from memory.
	* @details This method should be called when the model is no longer needed to free up memory and resources. It will release any GPU resources, clear vertex and index data, and reset the state of the Model3D instance.
	*/
	void
		unload() override;

	/*
	* @brief Retrieves the size of the model resource in bytes, which can be used for profiling and memory management purposes.
	* @return The size of the model resource in bytes, including vertex data, index data, and any associated resources.
	* @details The size is calculated based on the number of vertices, indices, and any additional data associated with the model. This information can be useful for understanding the memory footprint of the model and optimizing resource usage in the engine.
	*/
	size_t
		getSizeInBytes() const override;

	/*
	* @brief Retrieves the list of mesh components that make up the model, which can be used for rendering and other operations.
	* @return A constant reference to a vector of MeshComponent instances representing the meshes that compose the model. Each MeshComponent contains vertex and index data for a portion of the model, allowing for rendering and manipulation of the model's geometry.
	* @details The mesh components are typically loaded from the model file and may include multiple meshes if the model consists of multiple parts or materials. This method provides access to the mesh data for use in rendering, collision detection, or other operations that require knowledge of the model's geometry.
	*/
	const std::vector<MeshComponent>&
		GetMeshes() const { return m_meshes; }

	/*
	* @brief Initializes the FBX SDK manager and scene, preparing the Model3D instance to load FBX model data.
	* @return True if the FBX manager and scene were successfully initialized, false otherwise.
	*/
	bool
		InitializeFBXManager();

	/*
	* @brief Loads an FBX model from the specified file path, processing the FBX scene to extract mesh and material data.
	* @param filePath The file path to the FBX model to be loaded.
	* @return A vector of MeshComponent instances representing the meshes extracted from the FBX model. Each MeshComponent contains vertex and index data for a portion of the model, allowing for rendering and manipulation of the model's geometry.
	* @details This method uses the FBX SDK to load the FBX file, traverse the scene graph, and extract mesh data from the nodes. It also processes materials and textures associated with the meshes, storing texture file names for later use. The resulting mesh components can be used for rendering the model in the engine.
	*/
	std::vector<MeshComponent>
		LoadFBXModel(const std::string& filePath);

	/*
	* @brief Recursively processes an FBX node and its children to extract mesh data and populate the Model3D instance with MeshComponent instances.
	* @param node A pointer to the FBX node to be processed. This method will traverse the node's children and extract mesh data from any nodes that contain mesh information, creating MeshComponent instances for each mesh found and adding them to the Model3D instance.
	* @details The method checks if the node contains a mesh, and if so, it processes the mesh data to create a MeshComponent. It then recursively calls itself for each child node, allowing for traversal of the entire FBX scene graph to extract all relevant mesh data.
	*/
	void
		ProcessFBXNode(FbxNode* node);
	/*
	* @brief Processes an FBX mesh to extract vertex and index data, creating a MeshComponent instance that represents the mesh's geometry.
	* @param node A pointer to the FBX node that contains the mesh to be processed. This method will extract vertex positions, normals, texture coordinates, and index data from the mesh, and populate a MeshComponent instance with this information for use in rendering the model.
	* @details The method uses the FBX SDK to access the mesh data, including control points (vertices), polygon indices, and any associated vertex attributes. It creates a MeshComponent instance, fills it with the extracted data, and adds it to the Model3D instance's list of meshes for later use in rendering.
	*/
	void
		ProcessFBXMesh(FbxNode* node);

	/*
	* @brief Processes an FBX material to extract texture file names and other material properties, storing them for later use in rendering the model.
	* @param material A pointer to the FBX material to be processed. This method will extract texture file names from the material's properties, such as diffuse and normal maps, and store them in the Model3D instance for later use when rendering the model with the appropriate textures.
	* @details The method uses the FBX SDK to access the material properties, checking for textures associated with the material and extracting their file names. These texture file names can then be used to load the corresponding texture resources in the engine when rendering the model with its materials.
	*/
	void
		ProcessFBXMaterials(FbxSurfaceMaterial* material);

	/*
	* @brief Retrieves the list of texture file names associated with the model, which can be used for loading texture resources when rendering the model.
	* @return A vector of strings representing the file names of textures associated with the model. These file names are typically extracted from the materials in the FBX model and can be used to load the corresponding texture resources in the engine for rendering the model with its materials.
	* @details The texture file names are stored in the Model3D instance after processing the materials in the FBX model. This method provides access to the list of texture file names for use in loading textures and applying them to the model during rendering.
	*/
	std::vector<std::string>
		GetTextureFileNames() const { return textureFileNames; }
private:
	FbxManager* lSdkManager;
	FbxScene* lScene;
	std::vector<std::string> textureFileNames;
public:
	ModelType m_modelType;
	std::vector<MeshComponent> m_meshes;
};