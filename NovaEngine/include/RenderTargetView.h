#pragma once
#include "Prerequisites.h"

// Forward declarations
class Device;
class DeviceContext;
class Texture;
class DepthStencilView;

/*
  @class RenderTargetView
  
  @brief A render target view encapsulates a render target buffer resource.
  
  @note A render target view is used in conjunction with a render target buffer to
        control access to resource data.
*/
class
  RenderTargetView {
public:
  /*
    @brief Default constructor
	*/
  RenderTargetView() = default;

  /*
    @brief Destructor
	*/
  ~RenderTargetView() = default;

  /*
    @brief Initializes the render target view.
    
    @details This method creates a render target view for the specified texture resource.
    
    @param device The device to create the render target view on.
    
    @param backBuffer The texture resource to bind to the render target view.
    
    @param format The format of the render target view.
    
		@return HRESULT indicating success or failure of the operation.
	*/
  HRESULT
    init(Device& device, Texture& backBuffer, DXGI_FORMAT Format);

	/* 
    @brief Initializes the render target view with specific view dimension.
    
    @details This method creates a render target view for the specified texture resource with a given view dimension.
    
    @param device The device to create the render target view on.
    
    @param inTex The texture resource to bind to the render target view.
    
    @param ViewDimension The dimension of the render target view (e.g., 2D, 3D, Cube).
    
		@param Format The format of the render target view.
		
    @return HRESULT indicating success or failure of the operation.
	*/
  HRESULT
    init(Device& device,
      Texture& inTex,
      D3D11_RTV_DIMENSION ViewDimension,
      DXGI_FORMAT Format);

	/* 
    @brief Updates the render target view.
	*/
  void
    update();

	/* 
    @brief Renders the render target view with depth stencil view and clear color.
    
    @details This method sets the render target view and depth stencil view for rendering, and clears them with the specified color.
    
    @param deviceContext The device context to use for rendering.
    
    @param depthStencilView The depth stencil view to bind.
    
    @param numViews The number of render target views to bind.
    
    @param ClearColor An array of four floating-point values that define the color to clear the render target view to.
	*/
  void
    render(DeviceContext& deviceContext,
      DepthStencilView& depthStencilView,
      unsigned int numViews,
      const float ClearColor[4]);

	/* 
    @brief Renders the render target view with specified number of views.
    
    @details This method sets the render target view for rendering without a depth stencil view.
    
    @param deviceContext The device context to use for rendering.
    
		@param numViews The number of render target views to bind.
	*/
  void
    render(DeviceContext& deviceContext,
      unsigned int numViews);

	/* 
		@brief Destroys the render target view and releases associated resources.
	*/
  void
    destroy();
private:
  ID3D11RenderTargetView* m_renderTargetView = nullptr;
};