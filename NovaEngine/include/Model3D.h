#pragma once
#include "Prerequisites.h"
#include "IResource.h"
#include "MeshComponent.h"
#include "fbxsdk.h"

enum
	ModelType {
	OBJ,
	FBX
};

/* 
	@class Model3D
	@brief A class that represents a 3D model resource.
	@note The Model3D class is responsible for loading and managing 3D model data, including meshes and materials.
*/
class
	Model3D : public IResource {
public:
	/* 
		@brief Constructor
		@param name The name of the model resource.
		@param modelType The type of the model (e.g., OBJ, FBX).
	*/
	Model3D(const std::string& name, ModelType modelType)
		: IResource(name), m_modelType(modelType), lSdkManager(nullptr), lScene(nullptr) {
		SetType(ResourceType::Model3D);
		load(name);
	}

	/* 
		@brief Destructor
	*/
	~Model3D() = default;

	/*
		@brief Loads the model from the specified path.
		@param path The file path to load the model from.
		@return True if the model was loaded successfully, false otherwise.
	*/
	bool
		load(const std::string& path) override;

	/*
		@brief Initializes the model resource.
		@return True if initialization was successful, false otherwise.
	*/
	bool
		init() override;

	/*
		@brief Unloads the model resource and releases associated resources.
	*/
	void
		unload() override;

	/*
		@brief Gets the size of the model resource in bytes.
		@return The size of the model resource in bytes.
	*/
	size_t
		getSizeInBytes() const override;

	/*
		@brief Gets the meshes of the model.
		@return A constant reference to the vector of mesh components.
	*/
	const std::vector<MeshComponent>&
		GetMeshes() const { return m_meshes; }

	/*
		@brief FBX MODEL LOADER INITIALIZATION
	*/
	/* FBX MODEL LOADER*/
	bool
		InitializeFBXManager();

	/*
		@brief Loads an FBX model from the specified file path.
		@param filePath The file path to load the FBX model from.
		@return A vector of mesh components representing the loaded model.
	*/
	std::vector<MeshComponent>
		LoadFBXModel(const std::string& filePath);

	/*
		@brief Processes an FBX node and extracts mesh and material data.
		@param node The FBX node to process.
	*/
	void
		ProcessFBXNode(FbxNode* node);

	/*
		@brief Processes an FBX mesh and extracts vertex and index data.
		@param node The FBX node containing the mesh to process.
	*/
	void
		ProcessFBXMesh(FbxNode* node);

	/*
		@brief Processes FBX materials and extracts texture file names.
		@param material The FBX surface material to process.
	*/
	void
		ProcessFBXMaterials(FbxSurfaceMaterial* material);

	/*
		@brief Gets the texture file names used in the model.
		@return A vector of strings containing the texture file names.
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