#pragma once
#include "Prerequisites.h"

class Device;
class DeviceContext;

/*
  @class InputLayout
  @brief A wrapper class for the ID3D11InputLayout interface.
  @note The InputLayout class is responsible for creating and managing Direct3D input layout resources.
*/
class
  InputLayout {
public:
  /*
		@brief Default constructor
  */
  InputLayout() = default;

  /*
		@brief Destructor
	*/
  ~InputLayout() = default;

  /*
    @brief Initializes the input layout.
    @details This method creates an input layout for the specified vertex shader and input element descriptions.
    @param device The device to create the input layout on.
    @param Layout A vector of D3D11_INPUT_ELEMENT_DESC structures that describe the input-buffer data.
    @param VertexShaderData A pointer to the compiled vertex shader bytecode that contains the input signature.
    @return HRESULT indicating success or failure of the operation.
	*/
  HRESULT
    init(Device& device,
      std::vector<D3D11_INPUT_ELEMENT_DESC>& Layout,
      ID3DBlob* VertexShaderData);

  /*
		@brief Updates the input layout.
  */
  void
    update();
  
  /*
    @brief Renders the input layout.
  */
  void
    render(DeviceContext& deviceContext);

  /*
		@brief Destroys the input layout and releases associated resources.
  */
  void
    destroy();

public:
  ID3D11InputLayout* m_inputLayout = nullptr;
};