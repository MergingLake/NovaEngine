#pragma once
#include "Prerequisites.h"
//#include "ECS\Component.h"
// Forward declaration
class DeviceContext;
 
/*
  @class MeshComponent
  @brief A component that represents a 3D mesh in the ECS architecture.
	@note The MeshComponent class stores vertex and index data for rendering 3D models.
*/
class
  MeshComponent /*: public Component*/ {
public:
  /*
		@brief Default constructor
  */
  MeshComponent() : m_numVertex(0), m_numIndex(0)/*, Component(ComponentType::MESH)*/ {}

  /*
    @brief Destructor
	*/
  virtual
    ~MeshComponent() = default;

  /*
		@brief Initializes the mesh component.
  */
  void
    init() /*override {}*/;

  /*
    @brief Updates the mesh component.
  */
  void
    update(float deltaTime)/* override {}*/;

  /*
    @brief Renders the mesh component.
  */
  void
    render(DeviceContext& deviceContext) /*override {}*/;

  /*
		@brief Destroys the mesh component and releases associated resources.
  */
  void
    destroy() /*override {}*/;

public:
  /*
		@brief The name of the mesh.
  */
  std::string m_name;

  /*
    @brief The list of vertices in the mesh.
  */
  std::vector<SimpleVertex> m_vertex;

  /*
    @brief The list of indices in the mesh.
  */
  std::vector<unsigned int> m_index;

  /*
    @brief The number of vertices in the mesh.
	*/
  int m_numVertex;

  /*
		@brief The number of indices in the mesh.
	*/
  int m_numIndex;
};