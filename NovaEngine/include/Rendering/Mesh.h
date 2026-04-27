#pragma once
#include "Prerequisites.h"
#include "Buffer.h"

/*
 * @struct Submesh
 * @brief The Submesh structure represents a portion of a mesh that can be rendered with a specific material. It contains GPU buffers for vertex and index data, as well as information about the number of indices to draw, the starting index in the index buffer, and the material slot that maps to a specific MaterialInstance on the Actor.
 * @details The Submesh structure is used to define the geometry and material association for a specific part of a mesh, allowing for efficient rendering of complex objects with multiple materials. Each Submesh can be rendered independently using its vertex and index buffers, and the material slot can be used to determine which MaterialInstance to use when rendering this submesh in the scene.
 */
struct 
Submesh {
	Buffer vertexBuffer;          ///< GPU buffer holding vertices for this specific part.
	Buffer indexBuffer;           ///< GPU buffer holding the connection order of the vertices.
	unsigned int indexCount = 0;  ///< Number of indices to draw.
	unsigned int startIndex = 0;  ///< Offset into the index buffer.
	unsigned int materialSlot = 0;///< Maps this geometry to a specific MaterialInstance array index on the Actor.
};

/*
 * @class Mesh
 * @brief The Mesh class represents a 3D mesh composed of multiple submeshes, each with its own vertex and index buffers and material association. It provides methods for accessing the submeshes and destroying the resources associated with the mesh.
 * @details The Mesh class serves as a container for the geometry data of a 3D object, allowing for efficient rendering of complex objects with multiple materials. It manages a collection of Submesh instances, each representing a portion of the mesh that can be rendered independently. The destroy method is responsible for releasing the GPU resources associated with each submesh, ensuring proper cleanup when the mesh is no longer needed.
 */
class 
Mesh {
public:
	/*
	 * @brief Retrieves the vector of Submesh instances that make up this Mesh.
	 * @details This method returns a reference to the vector of Submesh instances that define the geometry and material associations for this mesh. Each Submesh contains GPU buffers for vertex and index data, as well as information about how to render that portion of the mesh. The returned reference allows for both reading and modifying the submeshes as needed.
	 * @return A reference to the vector of Submesh instances that make up this Mesh.
	 */
	std::vector<Submesh>&
	getSubmeshes() { return m_submeshes; }

	/*
	 * @brief Retrieves the vector of Submesh instances that make up this Mesh (const version).
	 * @details This method returns a const reference to the vector of Submesh instances that define the geometry and material associations for this mesh. Each Submesh contains GPU buffers for vertex and index data, as well as information about how to render that portion of the mesh. The returned const reference allows for read-only access to the submeshes, ensuring that they cannot be modified through this method.
	 * @return A const reference to the vector of Submesh instances that make up this Mesh.
	 */
	const std::vector<Submesh>&
	getSubmeshes() const { return m_submeshes; }

	/*
	 * @brief Destroys the resources associated with this Mesh.
	 * @details This method iterates through each Submesh in the mesh and calls the destroy method on the vertex and index buffers to release the GPU resources. After destroying the buffers for all submeshes, it clears the vector of submeshes to remove all references to the destroyed resources. It is important to call this method before destroying an instance of Mesh to ensure that all GPU resources are properly released and to prevent memory leaks.
	 * @return void
	 */
	void
	destroy() {
		for (Submesh& submesh : m_submeshes) {
			submesh.vertexBuffer.destroy();
			submesh.indexBuffer.destroy();
		}

		m_submeshes.clear();
	}

private:
	std::vector<Submesh> m_submeshes;
};