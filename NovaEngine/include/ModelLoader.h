#pragma once
#include "Prerequisites.h"
#include "fbxsdk.h"
#include "MeshComponent.h"
#include <string>
#include <fstream>
#include <sstream>
#include <map>

/*
  @class ModelLoader
  @brief A class responsible for loading 3D model files.
  @note The ModelLoader class can parse various model formats and populate a MeshComponent with the loaded geometry.
*/
class ModelLoader {
public:
  /*
    @brief Default constructor
	*/
  ModelLoader() = default;
  
  /*
    @brief Destructor
	*/
  ~ModelLoader() = default;

  /*
    @brief Loads a .obj model file and fills a MeshComponent reference.
    This function parses the vertex positions (v), texture coordinates (vt),
    normals (vn), and faces (f). It handles quad triangulation
    and correct vertex indexing for D3D11.
    @param filename  Path to the .obj file (e.g., "Models/car.obj").
    @param outMesh   The MeshComponent instance to be filled with the data.
    @return @c true if the loading was successful, @c false on error (e.g., file not found).
  */
  bool
    LoadOBJ(const std::string& filename, MeshComponent& outMesh);

private:
  FbxManager* lSdkManager;
	FbxScene* lScene;
  std::vector<std::string> textureFileNames;
public:
  std::string modelName;
	//std::vector<MeshComponent> meshes;
};