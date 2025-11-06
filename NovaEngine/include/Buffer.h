#pragma once
#include "Prerequisites.h"
#include "MeshComponent.h"

class Device;
class DeviceContext;

/*
  @class Buffer
  @brief A wrapper class for the ID3D11Buffer interface.
  @note The Buffer class is responsible for creating, updating, and managing Direct3D buffer resources.
*/
class
  Buffer {
public:
  /*
		@brief Default constructor
  */
  Buffer() = default;

  /*
    @brief Destructor
	*/
  ~Buffer() = default;

  /*
    @brief Initializes the buffer with mesh data.
    @details This method creates a buffer and populates it with vertex data from the specified mesh component.
    @param device The device to create the buffer on.
    @param mesh The mesh component containing the vertex data.
    @param bindFlag The bind flags for the buffer (e.g., D3D11_BIND_VERTEX_BUFFER).
		@return HRESULT indicating success or failure of the operation.
  */
  HRESULT
    init(Device& device, const MeshComponent& mesh, unsigned int bindFlag);

  /*
    @brief Initializes the buffer with a specified byte width.
    @details This method creates a buffer with the given byte width and bind flags.
    @param device The device to create the buffer on.
		@param ByteWidth The size of the buffer in bytes.
  */
  HRESULT
    init(Device& device, unsigned int ByteWidth);

  /*
    @brief Updates the buffer with new data.
    @details This method updates the buffer with new data from system memory.
    @param deviceContext The device context to use for the update.
    @param pDstResource A pointer to the destination resource to update.
    @param DstSubresource The index of the destination subresource to update.
    @param pDstBox A pointer to a D3D11_BOX structure that defines the portion of the destination subresource to update. This parameter can be NULL.
    @param pSrcData A pointer to the source data in system memory.
    @param SrcRowPitch The size of one row of the source data, in bytes.
		@param SrcDepthPitch The size of one depth slice of the source data, in bytes.
  */
  void
    update(DeviceContext& deviceContext,
      ID3D11Resource* pDstResource,
      unsigned int    DstSubresource,
      const D3D11_BOX* pDstBox,
      const void* pSrcData,
      unsigned int    SrcRowPitch,
      unsigned int    SrcDepthPitch);

  /*
    @brief Renders the buffer by binding it to the input-assembler stage.
    @details This method binds the buffer to the input-assembler stage for use in rendering.
    @param deviceContext The device context to use for rendering.
    @param StartSlot The first slot to bind the buffer to.
    @param NumBuffers The number of buffers to bind.
    @param setPixelShader A boolean indicating whether to set the pixel shader (default is false).
		@param format The format of the index data if binding as an index buffer (default is DXGI_FORMAT_UNKNOWN).
  */
  void
    render(DeviceContext& deviceContext,
      unsigned int   StartSlot,
      unsigned int   NumBuffers,
      bool           setPixelShader = false,
      DXGI_FORMAT    format = DXGI_FORMAT_UNKNOWN);

  /*
		@brief Destroys the buffer and releases associated resources.
  */
  void
    destroy();

  /*
    @brief Creates the buffer with the specified description and initial data.
    @details This method creates a buffer based on the provided buffer description and optional initial data.
    @param device The device to create the buffer on.
    @param desc A reference to a D3D11_BUFFER_DESC structure that describes the buffer to be created.
		@param initData A pointer to a D3D11_SUBRESOURCE_DATA structure that describes the initial data for the buffer. This parameter can be NULL.
  */
  HRESULT
    createBuffer(Device& device,
      D3D11_BUFFER_DESC& desc,
      D3D11_SUBRESOURCE_DATA* initData);

private:
  /*
    @brief Buffer de D3D11 administrado por la clase.
  */
  ID3D11Buffer* m_buffer = nullptr;

  /*
		@brief Stride del buffer (tamaño de cada elemento en bytes).
  */
  unsigned int m_stride = 0;

	/*
    @brief Offset del buffer (desplazamiento en bytes).
  */
  unsigned int m_offset = 0;
  /*
		@brief Bind flag del buffer (indica cómo se utilizará el buffer).
  */
  unsigned int m_bindFlag = 0;
};