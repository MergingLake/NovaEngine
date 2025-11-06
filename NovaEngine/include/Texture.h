#pragma once
#include "Prerequisites.h"

// Forward declarations
class Device;
class DeviceContext;

/*
	@class Texture
	@enum ExtensionType
  @brief Enumeration for different texture file extensions.
  @note This enum is used to specify the type of texture file being loaded.
*/
class
  Texture {
public:
  /*
    @brief Default constructor
  */
  Texture() = default;

  /*
    @brief Destructor
	*/
  ~Texture() = default;

  /*
    @brief Initializes the texture.
    @details This method loads a texture from a file or creates a texture with specified dimensions and format.
    @param device The device to create the texture on.
    @param textureName The name of the texture file to load.
    @param extensionType The type of texture file being loaded (e.g., DDS, TGA, BMP).
    @return HRESULT indicating success or failure of the operation.
  */
  HRESULT
    init(Device& device,
      const std::string& textureName,
      ExtensionType extensionType);

	/* 
    @brief Initializes a blank texture with specified dimensions and format.
    @details This method creates a blank texture with the given width, height, format, and bind flags.
    @param device The device to create the texture on.
    @param width The width of the texture in pixels.
    @param height The height of the texture in pixels.
    @param Format The format of the texture (e.g., DXGI_FORMAT_R8G8B8A8_UNORM).
    @param BindFlags The bind flags for the texture (e.g., D3D11_BIND_RENDER_TARGET).
    @param sampleCount The number of samples per pixel (default is 1).
    @param qualityLevels The quality level of multisampling (default is 0).
    @return HRESULT indicating success or failure of the operation.
	*/
  HRESULT
    init(Device& device,
      unsigned int width,
      unsigned int height,
      DXGI_FORMAT Format,
      unsigned int BindFlags,
      unsigned int sampleCount = 1,
      unsigned int qualityLevels = 0);

	/* 
    @brief Initializes a texture from an existing texture resource.
    @details This method creates a shader resource view for the specified existing texture resource.
    @param device The device to create the texture on.
    @param textureRef The existing texture resource to create the shader resource view from.
    @param format The format of the texture (e.g., DXGI_FORMAT_R8G8B8A8_UNORM).
		@return HRESULT indicating success or failure of the operation.
	*/
  HRESULT
    init(Device& device, Texture& textureRef, DXGI_FORMAT format);

	/* 
    @brief Updates the texture.
	*/
  void
    update();

	/* 
    @brief Renders the texture by binding it to the pixel shader stage.
    @details This method binds the texture's shader resource view to the pixel shader stage for use in pixel shading.
    @param deviceContext The device context to use for rendering.
    @param StartSlot The first slot to bind the shader resource view to.
		@param NumViews The number of shader resource views to bind.
	*/
  void
    render(DeviceContext& deviceContext, unsigned int StartSlot, unsigned int NumViews);

	/* 
		@brief Destroys the texture and releases associated resources.
	*/
  void
    destroy();

public:
  ID3D11Texture2D* m_texture = nullptr;

  ID3D11ShaderResourceView* m_textureFromImg = nullptr;

  std::string m_textureName;
};