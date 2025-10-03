#pragma once
#include "Prerequisites.h"

// Forward declarations
class Device;
class DeviceContext;
class Window;
class Texture;

/*
  @class SwapChain
  
  @brief A swap chain manages the buffers that are used for rendering and presenting images to the display.
  
  @note The SwapChain class is responsible for creating and managing the swap chain and its associated resources.
*/
class
  SwapChain {
public:
  /* 
    @brief Default constructor
	*/
  SwapChain() = default;

  /*
		@brief Destructor
	*/
  ~SwapChain() = default;

  /*
    @brief Initializes the swap chain.
    
    @details This method creates a swap chain for the specified window and back buffer texture.
    
    @param device The device to create the swap chain on.
    
    @param deviceContext The device context associated with the device.
    
    @param backBuffer The texture resource to use as the back buffer for the swap chain.
    
    @param window The window to associate the swap chain with.
    
    @return HRESULT indicating success or failure of the operation.
	*/
  HRESULT
    init(Device& device,
      DeviceContext& deviceContext,
      Texture& backBuffer,
      Window window);

	/* 
    @brief Updates the swap chain.
	*/
  void
    update();

	/* 
		@brief Renders the swap chain.
	*/
  void
    render();

	/* 
    @brief Destroys the swap chain and releases associated resources.
	*/
  void
    destroy();

	/* 
    @brief Presents the swap chain's back buffer to the display.
    
		@details This method presents the contents of the swap chain's back buffer to the display, making it visible to the user.
	*/
  void
    present();

public:
  IDXGISwapChain* m_swapChain = nullptr;

  D3D_DRIVER_TYPE m_driverType = D3D_DRIVER_TYPE_NULL;

private:
  D3D_FEATURE_LEVEL m_featureLevel = D3D_FEATURE_LEVEL_11_0;

  unsigned int m_sampleCount;

  unsigned int m_qualityLevels;

  IDXGIDevice* m_dxgiDevice = nullptr;

  IDXGIAdapter* m_dxgiAdapter = nullptr;

  IDXGIFactory* m_dxgiFactory = nullptr;
};