#pragma once
#include "Prerequisites.h"
#include "Texture.h"
#include "RenderTargetView.h"
#include "DepthStencilView.h"

// Forward declarations
class Device;
class DeviceContext;

/*
 * @class EditorViewportPass
 * @brief The EditorViewportPass class encapsulates the resources and operations required for rendering the editor viewport in a graphics application. It manages a render target view, depth stencil view, and associated textures to facilitate rendering to an off-screen buffer that can be displayed in the editor interface.
 * @details The EditorViewportPass class provides methods for initializing resources, resizing the viewport, beginning the rendering process, clearing depth information, setting the viewport, and swapping resources with another instance. It also includes methods for retrieving the shader resource view (SRV) of the color texture and checking the validity of the resources.
 */
class 
EditorViewportPass {
public:
	/*
	 * @brief Default constructor
	 * @details Initializes an instance of the EditorViewportPass class with default values. The constructor does not perform any resource allocation or initialization, and it is the responsibility of the caller to call the init method to set up the necessary resources for rendering.
	 */
	EditorViewportPass() = default;

	/*
	 * @brief Destructor
	 * @details Cleans up any resources allocated by the EditorViewportPass instance. The destructor does not perform any specific cleanup operations, as it is assumed that the caller will call the destroy method to release resources before the instance is destroyed.
	 */
	~EditorViewportPass() = default;

	/*
	 * @brief Initializes the editor viewport pass.
	 * @details This method sets up the necessary resources for rendering the editor viewport, including creating textures, render target views, and depth stencil views. It takes a reference to a Device object for resource creation and the desired width and height of the viewport. The method returns an HRESULT indicating success or failure of the initialization process.
	 * @param device The device to create resources on.
	 * @param width The width of the editor viewport.
	 * @param height The height of the editor viewport.
	 * @return HRESULT indicating success or failure of the operation.
	 */
	HRESULT
	init(Device& device, unsigned int width, unsigned int height);

	/*
	 * @brief Resizes the editor viewport.
	 * @details This method updates the resources associated with the editor viewport to accommodate a new width and height. It takes a reference to a Device object for resource creation and the new dimensions of the viewport. The method returns an HRESULT indicating success or failure of the resizing process.
	 * @param device The device to create resources on.
	 * @param width The new width of the editor viewport.
	 * @param height The new height of the editor viewport.
	 * @return HRESULT indicating success or failure of the operation.
	 */
	HRESULT
	resize(Device& device, unsigned int width, unsigned int height);

	/*
	 * @brief Begins the rendering process for the editor viewport.
	 * @details This method sets up the necessary state for rendering to the editor viewport, including clearing the render target view with a specified clear color. It takes a reference to a DeviceContext object for rendering operations and an array of four floating-point values that define the color to clear the render target view to.
	 * @param deviceContext The device context to use for rendering.
	 * @param clearColor An array of four floating-point values that define the color to clear the render target view to.
	 */
	void
	begin(DeviceContext& deviceContext, const float clearColor[4]);

	/*
	 * @brief Swaps the resources of this EditorViewportPass instance with another instance.
	 * @details This method exchanges the internal resources (textures, render target views, depth stencil views) of this instance with those of another EditorViewportPass instance. This can be useful for efficiently switching between different viewport configurations without the overhead of creating and destroying resources.
	 * @param other The other EditorViewportPass instance to swap resources with.
	 */
	void
	swap(EditorViewportPass& other);

	/*
	 * @brief Clears the depth information of the editor viewport.
	 * @details This method clears the depth stencil view associated with the editor viewport, resetting the depth information for subsequent rendering operations. It takes a reference to a DeviceContext object for rendering operations.
	 * @param deviceContext The device context to use for rendering.
	 */
	void
	clearDepth(DeviceContext& deviceContext);

	/*
	 * @brief Sets the viewport for rendering to the editor viewport.
	 * @details This method configures the viewport settings for rendering to the editor viewport, ensuring that rendering operations are directed to the correct area of the render target. It takes a reference to a DeviceContext object for rendering operations.
	 * @param deviceContext The device context to use for rendering.
	 */
	void
	setViewport(DeviceContext& deviceContext);

	/*
	 * @brief Destroys the resources associated with the editor viewport pass.
	 * @details This method releases any resources allocated by the EditorViewportPass instance, including textures, render target views, and depth stencil views. It is important to call this method before destroying an instance of EditorViewportPass to ensure that resources are properly released and to prevent memory leaks.
	 */
	void
	destroy();

	/*
	 * @brief Retrieves the shader resource view (SRV) of the color texture.
	 * @details This method returns a pointer to the shader resource view (SRV) associated with the color texture used in the editor viewport. The SRV can be used for sampling the color texture in shader programs, allowing for effects such as post-processing or displaying the rendered viewport in the editor interface.
	 * @return A pointer to the ID3D11ShaderResourceView representing the SRV of the color texture.
	 */
	ID3D11ShaderResourceView* 
	getSRV() const { return m_colorSRV.m_textureFromImg; }

	/*
	 * @brief Retrieves the width of the editor viewport.
	 * @details This method returns the current width of the editor viewport, which is determined by the dimensions of the render target texture. The width can be used for various calculations related to rendering and layout within the editor interface.
	 * @return The width of the editor viewport in pixels.
	 */
	unsigned int 
	getWidth() const { return m_width; }

	/*
	 * @brief Retrieves the height of the editor viewport.
	 * @details This method returns the current height of the editor viewport, which is determined by the dimensions of the render target texture. The height can be used for various calculations related to rendering and layout within the editor interface.
	 * @return The height of the editor viewport in pixels.
	 */
	unsigned int 
	getHeight() const { return m_height; }

	/*
	 * @brief Checks the validity of the resources associated with the editor viewport pass.
	 * @details This method verifies that the necessary resources for rendering the editor viewport are properly initialized and valid. It checks that the color texture, shader resource view, and depth texture are all non-nullptr, indicating that they have been successfully created and are ready for use in rendering operations.
	 * @return true if all resources are valid; false otherwise.
	 */
	bool
	isValid() const {
		return m_colorTexture.m_texture != nullptr &&
					 m_colorSRV.m_textureFromImg != nullptr &&
					 m_depthTexture.m_texture != nullptr;
	}

private:
	/*
	 * @brief Creates the resources required for rendering the editor viewport.
	 * @details This method is responsible for creating the textures, render target views, and depth stencil views needed for rendering to the editor viewport. It takes a reference to a Device object for resource creation and the desired width and height of the viewport. The method returns an HRESULT indicating success or failure of the resource creation process.
	 * @param device The device to create resources on.
	 * @param width The width of the editor viewport.
	 * @param height The height of the editor viewport.
	 * @return HRESULT indicating success or failure of the operation.
	 */
	HRESULT
	createResources(Device& device, unsigned int width, unsigned int height);

private:
	Texture m_colorTexture;
	Texture m_colorSRV;
	RenderTargetView m_rtv;
	Texture m_depthTexture;
	DepthStencilView m_dsv;

	unsigned int m_width = 1;
	unsigned int m_height = 1;
};