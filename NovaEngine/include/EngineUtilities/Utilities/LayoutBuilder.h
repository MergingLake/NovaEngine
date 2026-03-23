#pragma once
#include "Prerequisites.h"

/*
* @class LayoutBuilder
* @brief builder to create input layouts for vertex buffers in a more convenient way.
* The LayoutBuilder class provides a convenient interface for constructing input layouts for vertex buffers in Direct3D 11. It allows you to define the layout of vertex data by specifying the semantic name, format, and other parameters for each element in the layout. The builder pattern is used to enable a fluent interface for adding elements to the layout, making it easier to create complex input layouts without having to manually construct D3D11_INPUT_ELEMENT_DESC structures.
*/
class 
LayoutBuilder
{
public:
  /*
	* @brief Adds a new element to the input layout.
	* @param semantic The semantic name of the element (e.g., "POSITION", "TEXCOORD").
	* @param format The DXGI_FORMAT of the element (e.g., DXGI_FORMAT_R32G32B32_FLOAT).
	* @param semanticIndex The index of the semantic (default is 0).
	* @param inputSlot The input slot for the element (default is 0).
	* @param alignedByteOffset The byte offset of the element in the vertex structure (default is D3D11_APPEND_ALIGNED_ELEMENT).
	* @param slotClass The input classification for the element (default is D3D11_INPUT_PER_VERTEX_DATA).
	* @param instanceStepRate The number of instances to draw using the same per-instance data before advancing to the next element (default is 0).
	* @return A reference to the LayoutBuilder instance, allowing for method chaining.
  */
  LayoutBuilder& 
  Add(const char* semantic,
      DXGI_FORMAT format,
      UINT semanticIndex = 0,
      UINT inputSlot = 0,
      UINT alignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT,
      D3D11_INPUT_CLASSIFICATION slotClass = D3D11_INPUT_PER_VERTEX_DATA,
      UINT instanceStepRate = 0) {
    D3D11_INPUT_ELEMENT_DESC d{};
    d.SemanticName = semantic;
    d.SemanticIndex = semanticIndex;
    d.Format = format;
    d.InputSlot = inputSlot;
    d.AlignedByteOffset = alignedByteOffset;
    d.InputSlotClass = slotClass;
    d.InstanceDataStepRate = instanceStepRate;
    m_elems.push_back(d);
    return *this;
  }

  /*
	* @brief Adds a new element to the input layout for instancing.
	* @param semantic The semantic name of the element (e.g., "INSTANCE_TRANSFORM").
	* @param format The DXGI_FORMAT of the element (e.g., DXGI_FORMAT_R32G32B32A32_FLOAT).
	* @param semanticIndex The index of the semantic (default is 0).
	* @param inputSlot The input slot for the element (default is 1, as instancing data typically uses a different slot than vertex data).
	* @param alignedByteOffset The byte offset of the element in the instance data structure (default is D3D11_APPEND_ALIGNED_ELEMENT).
	* @param instanceStepRate The number of instances to draw using the same per-instance data before advancing to the next element (default is 1, meaning the data will advance for each instance).
	* @return A reference to the LayoutBuilder instance, allowing for method chaining.
  */
  LayoutBuilder& 
  AddInstance(const char* semantic,
              DXGI_FORMAT format,
              UINT semanticIndex = 0,
              UINT inputSlot = 1,
              UINT alignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT,
              UINT instanceStepRate = 1) {
    return Add(semantic, format, semanticIndex, inputSlot, alignedByteOffset,
      D3D11_INPUT_PER_INSTANCE_DATA, instanceStepRate);
  }

  /*
	* @brief Retrieves the constructed input layout as a vector of D3D11_INPUT_ELEMENT_DESC structures.
	* @return A constant reference to a vector containing the D3D11_INPUT_ELEMENT_DESC structures that define the input layout. Each element in the vector corresponds to an element added to the layout using the Add or AddInstance methods.
  */
  const std::vector<D3D11_INPUT_ELEMENT_DESC>& Get() const { return m_elems; }
  /*
	* @brief Retrieves the number of elements in the input layout.
	* @return The number of elements currently defined in the input layout, which corresponds to the number of times the Add or AddInstance methods have been called to add elements to the layout.
  */
  UINT Count() const { return (UINT)m_elems.size(); }

private:
  std::vector<D3D11_INPUT_ELEMENT_DESC> m_elems;
};