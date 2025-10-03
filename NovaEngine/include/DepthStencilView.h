#pragma once
#include "Prerequisites.h"

// Forward declarations
class Device;
class DeviceContext;
class Texture;

/*
  @class DepthStencilView
	
  @brief A depth stencil view encapsulates a depth stencil buffer resource.
  
  @note A depth stencil view is used in conjunction with a depth stencil buffer to
				control access to resource data.
*/
class
  DepthStencilView {
public:
  /*
		@brief Default constructor
  */
  DepthStencilView() = default;

	/*
    @brief Destructor
  */
  ~DepthStencilView() = default;

  /*
    @brief Initializes the depth stencil view.
		
    @details This method creates a depth stencil view for the specified texture resource.
    
    @param device The device to create the depth stencil view on.
    
    @param depthStencil The texture resource to bind to the depth stencil view.
    
    @param format The format of the depth stencil view.
    
    @return HRESULT indicating success or failure of the operation.
	*/
  HRESULT
    init(Device& device, Texture& depthStencil, DXGI_FORMAT format);

  /*
    @brief Updates the depth stencil view.
  */
  void
    update() {};

	/*
		@brief Renders the depth stencil view.
	*/
	void
		render(DeviceContext& deviceContext);

  /*
    @brief Destroys the depth stencil view and releases associated resources.
	*/
  void
    destroy();

public:
  ID3D11DepthStencilView* m_depthStencilView = nullptr;
};