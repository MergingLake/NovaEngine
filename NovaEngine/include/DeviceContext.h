#pragma once
#include "Prerequisites.h"

/*
  @class DeviceContext

  @brief A wrapper class for the ID3D11DeviceContext interface.
	
  @note The DeviceContext class is responsible for managing the device context and issuing rendering commands.
*/
class
  DeviceContext {
public:
  /* 
    @brief Default constructor
	*/
  DeviceContext() = default;
  /* 
		@brief Destructor
	*/
  ~DeviceContext() = default;

  /* 
    @brief Initializes the device context.
	*/
  void
    init();

  /*
    @brief Updates the device context.
  */
  void
    update();
  
  /*
    @brief Renders the device context.
  */
  void
    render();

  /*
		@brief Destroys the device context and releases associated resources.
  */
  void
    destroy();

  /*
    @brief Sets the viewports for the rasterizer stage.
		
    @details This method sets the viewports that define the portion of the render target to draw to.
    
    @param NumViewports The number of viewports to set.
		
    @param pViewports A pointer to an array of D3D11_VIEWPORT structures that define the viewports.
	*/
  void
    RSSetViewports(unsigned int NumViewports, const D3D11_VIEWPORT* pViewports);

  /*
		@brief Binds an array of shader resource views to the pixel shader stage.
		
    @details This method binds an array of shader resource views to the pixel shader stage for use in pixel shading.
		
    @param StartSlot The first slot to bind the shader resource views to.
		
    @param NumViews The number of shader resource views to bind.
		
    @return ppShaderResourceViews A pointer to an array of shader resource view interfaces to bind.
  */
  void
    PSSetShaderResources(unsigned int StartSlot,
      unsigned int NumViews,
      ID3D11ShaderResourceView* const* ppShaderResourceViews);

  /*
		@brief Sets the input layout for the input-assembler stage.
		
    @details This method sets the input layout that describes the format of the vertex data.
    
    @param pInputLayout A pointer to the input layout interface to set.
	*/
  void
    IASetInputLayout(ID3D11InputLayout* pInputLayout);

  /*
		@brief Sets the vertex shader for the vertex shader stage.
    
    @details This method sets the vertex shader to be used for vertex shading.
    
    @param pVertexShader A pointer to the vertex shader interface to set.
    
    @param ppClassInstances An array of class-instance interfaces for dynamic linkage. This parameter can be NULL.
    
    @param NumClassInstances The number of class instances in the ppClassInstances array.
	*/
  void
    VSSetShader(ID3D11VertexShader* pVertexShader,
      ID3D11ClassInstance* const* ppClassInstances,
      unsigned int NumClassInstances);

	/*
    @brief Sets the pixel shader for the pixel shader stage.
  
    @details This method sets the pixel shader to be used for pixel shading.
  
    @param pPixelShader A pointer to the pixel shader interface to set.
  
    @param ppClassInstances An array of class-instance interfaces for dynamic linkage. This parameter can be NULL.
  
    @param NumClassInstances The number of class instances in the ppClassInstances array.
  */
  void
    PSSetShader(ID3D11PixelShader* pPixelShader,
      ID3D11ClassInstance* const* ppClassInstances,
      unsigned int NumClassInstances);

  /*
    @brief Updates a subresource with new data.
    
    @details This method updates a subresource of a resource with new data from system memory.
    
    @param pDstResource A pointer to the destination resource to update.
    
    @param DstSubresource The index of the destination subresource to update.
    
    @param pDstBox A pointer to a D3D11_BOX structure that defines the portion of the destination subresource to update. This parameter can be NULL.
    
    @param pSrcData A pointer to the source data in system memory.
    
    @param SrcRowPitch The size of one row of the source data, in bytes.
    
		@param SrcDepthPitch The size of one depth slice of the source data, in bytes.
	*/
  void
    UpdateSubresource(ID3D11Resource* pDstResource,
      unsigned int DstSubresource,
      const D3D11_BOX* pDstBox,
      const void* pSrcData,
      unsigned int SrcRowPitch,
      unsigned int SrcDepthPitch);

  /*
    @brief Binds an array of vertex buffers to the input-assembler stage.
    
    @details This method binds an array of vertex buffers to the input-assembler stage for use in rendering.
    
    @param StartSlot The first slot to bind the vertex buffers to.
    
    @param NumBuffers The number of vertex buffers to bind.
    
    @param ppVertexBuffers A pointer to an array of vertex buffer interfaces to bind.
    
    @param pStrides A pointer to an array of stride values, in bytes, for each vertex buffer.
    
    @param pOffsets A pointer to an array of offset values, in bytes, for each vertex buffer.
	*/
  void
    IASetVertexBuffers(unsigned int StartSlot,
      unsigned int NumBuffers,
      ID3D11Buffer* const* ppVertexBuffers,
      const unsigned int* pStrides,
      const unsigned int* pOffsets);

  /*
    @brief Sets the index buffer for the input-assembler stage.

		@details This method sets the index buffer that defines the order in which vertices are processed.

    @param pIndexBuffer A pointer to the index buffer interface to set.
    
    @param Format The format of the index data in the index buffer.
		
    @param Offset The offset, in bytes, from the start of the index buffer to the first index to use.
  */
  void
    IASetIndexBuffer(ID3D11Buffer* pIndexBuffer,
      DXGI_FORMAT Format,
      unsigned int Offset);

	/*
    @brief Sets the sampler states for the pixel shader stage.

		@details This method sets the sampler states that define how textures are sampled in the pixel shader stage.

    @param StartSlot The first slot to bind the sampler states to.
    
    @param NumSamplers The number of sampler states to bind.
    
		@param ppSamplers A pointer to an array of sampler state interfaces to bind.
  */
  void
    PSSetSamplers(unsigned int StartSlot,
      unsigned int NumSamplers,
      ID3D11SamplerState* const* ppSamplers);

  /*
    @brief Sets the rasterizer state for the rasterizer stage.
    
    @details This method sets the rasterizer state that defines how primitives are rasterized.
    
		@param pRasterizerState A pointer to the rasterizer state interface to set.
	*/
  void
    RSSetState(ID3D11RasterizerState* pRasterizerState);

	/*
    @brief Sets the blend state for the output-merger stage.

		@details This method sets the blend state that defines how pixel colors are blended with render target colors.

    @param pBlendState A pointer to the blend state interface to set.
    
    @param BlendFactor An array of four floating-point values that define the blend factor. This parameter can be NULL.
    
		@param SampleMask A 32-bit unsigned integer that defines a sample mask.
	*/
  void
    OMSetBlendState(ID3D11BlendState* pBlendState,
      const float BlendFactor[4],
      unsigned int SampleMask);

	/*
    @brief Sets the render targets and depth stencil view for the output-merger stage.
    
    @details This method binds an array of render target views and a depth stencil view to the output-merger stage for rendering.
    
    @param NumViews The number of render target views to bind.
    
    @param ppRenderTargetViews A pointer to an array of render target view interfaces to bind.
    
		@param pDepthStencilView A pointer to the depth stencil view interface to bind. This parameter can be NULL.
  */
  void
    OMSetRenderTargets(unsigned int NumViews,
      ID3D11RenderTargetView* const* ppRenderTargetViews,
      ID3D11DepthStencilView* pDepthStencilView);

  /*
    @brief Sets the primitive topology for the input-assembler stage.
    
    @details This method sets the primitive topology that defines how vertex data is interpreted as geometric primitives.
    
		@param Topology The primitive topology to set.
  */
  void
    IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology);

  /*
    @brief Clears a render target view.

		@details This method clears the specified render target view to a specified color.

    @param pRenderTargetView A pointer to the render target view interface to clear.
    
		@param ColorRGBA An array of four floating-point values that define the color to clear the render target view to.
  */
  void
    ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView,
      const float ColorRGBA[4]);

	/* 
		@brief Clears a depth stencil view.

    @details This method clears the specified depth stencil view to a specified depth and stencil value.
    
    @param pDepthStencilView A pointer to the depth stencil view interface to clear.
    
    @param ClearFlags Flags that specify which parts of the depth stencil view to clear. This parameter can be a combination of D3D11_CLEAR_DEPTH and D3D11_CLEAR_STENCIL.
    
    @param Depth The depth value to clear the depth buffer to. This value is clamped to the range 0.0 to 1.0.
    
    @param Stencil The stencil value to clear the stencil buffer to.
	*/
  void
    ClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView,
      unsigned int ClearFlags,
      float Depth,
      UINT8 Stencil);

  /*
    @brief Binds an array of constant buffers to the vertex shader stage.
    
    @details This method binds an array of constant buffers to the vertex shader stage for use in vertex shading.
    
    @param StartSlot The first slot to bind the constant buffers to.
    
    @param NumBuffers The number of constant buffers to bind.
    
		@param ppConstantBuffers A pointer to an array of constant buffer interfaces to bind.
	*/
  void
    VSSetConstantBuffers(unsigned int StartSlot,
      unsigned int NumBuffers,
      ID3D11Buffer* const* ppConstantBuffers);

	/* 
		@brief Binds an array of constant buffers to the pixel shader stage.

    @details This method binds an array of constant buffers to the pixel shader stage for use in pixel shading.
    
    @param StartSlot The first slot to bind the constant buffers to.
    
		@param NumBuffers The number of constant buffers to bind.
		
    @param ppConstantBuffers A pointer to an array of constant buffer interfaces to bind.
	*/
  void
    PSSetConstantBuffers(unsigned int StartSlot,
      unsigned int NumBuffers,
      ID3D11Buffer* const* ppConstantBuffers);

	/*
    @brief Draws indexed geometry.

		@details This method issues a draw call to render indexed geometry using the currently bound resources and state.

    @param IndexCount The number of indices to draw.
    
    @param StartIndexLocation The location of the first index to use from the index buffer.
    
		@param BaseVertexLocation A value added to each index before reading a vertex from the vertex buffer.
  */
  void
    DrawIndexed(unsigned int IndexCount,
      unsigned int StartIndexLocation,
      int BaseVertexLocation);
public:
  ID3D11DeviceContext* m_deviceContext = nullptr;
};