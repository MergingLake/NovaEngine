 #pragma once
#include "Prerequisites.h"
#include "InputLayout.h"

// Forward declarations
class Device;
class DeviceContext;

/*
	@class ShaderProgram
	@brief A class that encapsulates a shader program consisting of vertex and pixel shaders.
	@note The ShaderProgram class is responsible for loading, compiling, and managing vertex and pixel shaders, as well as their associated input layouts.
*/
class
  ShaderProgram {
public:
  /*
		@brief Default constructor
  */
  ShaderProgram() = default;

  /*
		@brief Destructor
  */
  ~ShaderProgram() = default;

  /*
    @brief Initializes the shader program.
    @details This method loads and compiles the vertex and pixel shaders from the specified file, and creates the input layout.
    @param device The device to create the shaders and input layout on.
    @param fileName The name of the shader file to load.
    @param Layout A vector of D3D11_INPUT_ELEMENT_DESC structures that describe the input-buffer data.
		@return HRESULT indicating success or failure of the operation.
  */
  HRESULT
    init(Device& device,
      const std::string& fileName,
      std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

  /*
		@brief Updates the shader program.
  */
  void
    update();

  /*
		@brief Renders the shader program.
  */
  void
    render(DeviceContext& deviceContext);

  /*
    @brief Renders a specific shader type (vertex or pixel).
    @param deviceContext The device context to use for rendering.
		@param type The type of shader to render (vertex or pixel).
  */
  void
    render(DeviceContext& deviceContext, ShaderType type);

  /*
		@brief Destroys the shader program and releases associated resources.
  */
  void
    destroy();

  /*
    @brief Creates the input layout for the shader program.
    @details This method creates an input layout based on the provided input element descriptions.
    @param device The device to create the input layout on.
		@param Layout A vector of D3D11_INPUT_ELEMENT_DESC structures that describe the input-buffer data.
  */
  HRESULT
    CreateInputLayout(Device& device,
      std::vector<D3D11_INPUT_ELEMENT_DESC> Layout);

  /*
    @brief Creates a shader of the specified type.
    @details This method creates either a vertex shader or a pixel shader based on the provided type.
		@param device The device to create the shader on.
  */
  HRESULT
    CreateShader(Device& device, ShaderType type);
  /*
    @brief Creates a shader of the specified type from a file.
		@details This method loads and compiles the shader from the specified file and creates either a vertex shader or a pixel shader based on the provided type.
  */
  HRESULT
    CreateShader(Device& device, ShaderType type, const std::string& fileName);

  /*
    @brief Compiles a shader from a file.
    @details This method compiles the shader code from the specified file using the given entry point and shader model.
    @param szFileName The name of the shader file to compile.
    @param szEntryPoint The entry point function name in the shader code.
    @param szShaderModel The shader model to use for compilation (e.g., "vs_5_0" for vertex shader, "ps_5_0" for pixel shader).
		@param ppBlobOut A pointer to an ID3DBlob interface that receives the compiled shader bytecode.
  */
  HRESULT
    CompileShaderFromFile(char* szFileName,
      LPCSTR szEntryPoint,
      LPCSTR szShaderModel,
      ID3DBlob** ppBlobOut);

public:
  /*
		@brief Vertex shader managed by the class.
  */
  ID3D11VertexShader* m_VertexShader = nullptr;

  /*
		@brief Pixel shader managed by the class.
  */
  ID3D11PixelShader* m_PixelShader = nullptr;

  /*
		@brief Input layout managed by the class.
  */
  InputLayout m_inputLayout;

private:
  /*
    @brief Shader file name.
	*/
  std::string m_shaderFileName;

  /*
		@brief Compiled vertex shader bytecode.
  */
  ID3DBlob* m_vertexShaderData = nullptr;
 
  /*
		@brief Compiled pixel shader bytecode.
  */
  ID3DBlob* m_pixelShaderData = nullptr;
};