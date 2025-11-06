#include "ModelLoader.h"

bool
ModelLoader::LoadOBJ(const std::string& filename, MeshComponent& outMesh) {

  outMesh.m_vertex.clear();
  outMesh.m_index.clear();

  std::vector<XMFLOAT3> temp_positions;
  std::vector<XMFLOAT2> temp_uvs;
  std::vector<XMFLOAT3> temp_normals;

  std::vector<SimpleVertex> final_vertices;
  std::vector<unsigned int> final_indices;

  std::map<std::string, unsigned int> vertex_map;

  std::string fullPath = filename + ".obj";
  std::ifstream file(fullPath);
  if (!file.is_open()) {
    std::wstring errorMsg = L"ERROR: ModelLoader::LoadOBJ : No se pudo abrir el archivo: " + std::wstring(fullPath.begin(), fullPath.end()) + L"\n";
    OutputDebugStringW(errorMsg.c_str());
    return false;
  }

  std::string line;
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string prefix;
    ss >> prefix;

    if (prefix == "v") {
      XMFLOAT3 pos;
      ss >> pos.x >> pos.y >> pos.z;
      temp_positions.push_back(pos);
    }
    else if (prefix == "vt") {
      XMFLOAT2 uv;
      ss >> uv.x >> uv.y;
      uv.y = 1.0f - uv.y;
      temp_uvs.push_back(uv);
    }
    else if (prefix == "vn") {
      XMFLOAT3 normal;
      ss >> normal.x >> normal.y >> normal.z;
      temp_normals.push_back(normal);
    }
    else if (prefix == "f") {
      std::string face_data[4];
      unsigned int local_indices[4];
      unsigned int vertex_count = 0;

      while (vertex_count < 4 && ss >> face_data[vertex_count]) {
        vertex_count++;
      }

      for (unsigned int i = 0; i < vertex_count; ++i) {
        std::string vertexKey = face_data[i];

        if (vertex_map.find(vertexKey) == vertex_map.end()) {
          std::stringstream v_ss(vertexKey);
          std::string index_str;
          unsigned int v_idx = 0, vt_idx = 0, vn_idx = 0;

          std::getline(v_ss, index_str, '/');
          v_idx = std::stoul(index_str);

          if (std::getline(v_ss, index_str, '/')) {
            if (!index_str.empty()) vt_idx = std::stoul(index_str);
          }
          if (std::getline(v_ss, index_str, '/')) {
            if (!index_str.empty()) vn_idx = std::stoul(index_str);
          }

          SimpleVertex new_vert;
          new_vert.Pos = temp_positions[v_idx - 1];
          new_vert.Tex = (vt_idx > 0) ? temp_uvs[vt_idx - 1] : XMFLOAT2(0, 0);
          new_vert.Normal = (vn_idx > 0) ? temp_normals[vn_idx - 1] : XMFLOAT3(0, 1, 0);

          final_vertices.push_back(new_vert);
          unsigned int new_index = static_cast<unsigned int>(final_vertices.size() - 1);

          vertex_map[vertexKey] = new_index;
          local_indices[i] = new_index;
        }
        else {
          local_indices[i] = vertex_map[vertexKey];
        }
      }

      final_indices.push_back(local_indices[0]);
      final_indices.push_back(local_indices[1]);
      final_indices.push_back(local_indices[2]);

      if (vertex_count == 4) {
        final_indices.push_back(local_indices[0]);
        final_indices.push_back(local_indices[2]);
        final_indices.push_back(local_indices[3]);
      }
    }
  }

  file.close();

  outMesh.m_vertex = final_vertices;
  outMesh.m_index = final_indices;
  outMesh.m_numVertex = static_cast<int>(final_vertices.size());
  outMesh.m_numIndex = static_cast<int>(final_indices.size());

  return true;
}