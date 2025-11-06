#pragma once
#include "Prerequisites.h"

// Forward declarations
class Window;
class DeviceContext;

/*
  @class Viewport
  @brief A wrapper class for the D3D11_VIEWPORT structure.
	@note The Viewport class is responsible for managing the viewport settings for rendering.
*/
class
  Viewport {
public:
  /*
		@brief Default constructor
  */
  Viewport() = default;

  /*
		@brief Destructor
  */
  ~Viewport() = default;

  /*
    @brief Initializes the viewport using a window's dimensions.
    @details This method sets up the viewport based on the dimensions of the specified window.
    @param window The window to derive the viewport dimensions from.
		@return HRESULT indicating success or failure of the operation.
  */
  HRESULT
    init(const Window& window);

  /*
    @brief Initializes the viewport with specified width and height.
    @details This method sets up the viewport with the given width and height.
    @param width The width of the viewport in pixels.
		@param height The height of the viewport in pixels.
  */
  HRESULT
    init(unsigned int width, unsigned int height);

  /*
		@brief Updates the viewport.
		@details This method can be used to modify the viewport settings if needed.
  */
  void
    update();

  /*
		@brief Renders the viewport.
		@param deviceContext The device context to set the viewport on.
		@details This method sets the viewport for the rasterizer stage of the pipeline.
  */
  void
    render(DeviceContext& deviceContext);

  /*
		@brief Destroys the viewport and releases associated resources.
		@details This method cleans up any resources associated with the viewport.
  */
  void
    destroy() {}

public:
  D3D11_VIEWPORT m_viewport;
};