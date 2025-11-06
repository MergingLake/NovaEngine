#pragma once
#include "Prerequisites.h"

/*
	@class Device
	@brief A wrapper class for the ID3D11Device interface.
	@note The Device class is responsible for creating and managing Direct3D resources.
*/
class
Device {
public:
	/*
		@brief Default constructor
	*/
	Device() = default;

	/*
		@brief Destructor
	*/
	~Device() = default;

	/*
		@brief Initializes the device.
	*/
	void
		init();

	/*
		@brief Updates the device.
	*/
	void
		update();

	/*
		@brief Renders the device.
	*/
	void
		render();

	/*
		@brief Destroys the device and releases associated resources.
	*/
	void
		destroy();

	/*
		@brief Creates a render target view.
		@details A render target view binds a resource to the output-merger stage of the pipeline.
		@param pResource A pointer to the resource to create the render target view for.
		@param pDesc A pointer to a D3D11_RENDER_TARGET_VIEW_DESC structure that describes the render target view to be created. This parameter can be NULL.
		@param ppRTView A pointer to a variable that receives the address of the created render target view interface.
		@return HRESULT indicating success or failure of the operation.
	*/
	HRESULT
		CreateRenderTargetView(ID3D11Resource* pResource,
			const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
			ID3D11RenderTargetView** ppRTView);
	/*
		@brief Creates a 2D texture.
		@details A 2D texture is a resource that contains a 2D array of texels.
		@param pDesc A pointer to a D3D11_TEXTURE2D_DESC structure that describes the texture to be created.
		@param pInitialData A pointer to an array of D3D11_SUBRESOURCE_DATA structures that describe the initial data for each subresource. This parameter can be NULL.
		@param ppTexture2D A pointer to a variable that receives the address of the created texture interface.
		@return HRESULT indicating success or failure of the operation.
	*/
	HRESULT
		CreateTexture2D(const D3D11_TEXTURE2D_DESC* pDesc,
			const D3D11_SUBRESOURCE_DATA* pInitialData,
			ID3D11Texture2D** ppTexture2D);

	/*
		@brief Creates a depth stencil view.
		@details A depth stencil view binds a resource to the output-merger stage of the pipeline for depth-stencil operations.
		@param pResource A pointer to the resource to create the depth stencil view for.
		@param pDesc A pointer to a D3D11_DEPTH_STENCIL_VIEW_DESC structure that describes the depth stencil view to be created. This parameter can be NULL.
		@param ppDepthStencilView A pointer to a variable that receives the address of the created depth stencil view interface.
		@return HRESULT indicating success or failure of the operation.
	*/
	HRESULT
		CreateDepthStencilView(ID3D11Resource* pResource,
			const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
			ID3D11DepthStencilView** ppDepthStencilView);

	/*
		@brief Creates a vertex shader.
		@param pShaderBytecode A pointer to the compiled shader bytecode.
		@param BytecodeLength The size of the compiled shader bytecode, in bytes.
		@param pClassLinkage A pointer to an ID3D11ClassLinkage interface for linking class instances. This parameter can be NULL.
		@param ppVertexShader A pointer to a variable that receives the address of the created vertex shader interface.
		@return HRESULT indicating success or failure of the operation.
	*/
	HRESULT
		CreateVertexShader(const void* pShaderBytecode,
			unsigned int BytecodeLength,
			ID3D11ClassLinkage* pClassLinkage,
			ID3D11VertexShader** ppVertexShader);
	/*
		@brief Creates an input layout object to describe the input-buffer data for the input-assembler stage.
		@param pInputElementDescs A pointer to an array of D3D11_INPUT_ELEMENT_DESC structures that describe the input-buffer data.
		@param NumElements The number of elements in the pInputElementDescs array.
		@param pShaderBytecodeWithInputSignature A pointer to the compiled shader bytecode that contains the input signature.
		@param BytecodeLength The size of the compiled shader bytecode, in bytes.
		@param ppInputLayout A pointer to a variable that receives the address of the created input layout interface.
		@return HRESULT indicating success or failure of the operation.
	*/
	HRESULT
		CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
			unsigned int NumElements,
			const void* pShaderBytecodeWithInputSignature,
			unsigned int BytecodeLength,
			ID3D11InputLayout** ppInputLayout);

	/*
		@brief Creates a pixel shader.
		@details A pixel shader is a type of shader that processes pixel data.
		@param pShaderBytecode A pointer to the compiled shader bytecode.
		@param BytecodeLength The size of the compiled shader bytecode, in bytes.
		@param pClassLinkage A pointer to an ID3D11ClassLinkage interface for linking class instances. This parameter can be NULL.
		@param ppPixelShader A pointer to a variable that receives the address of the created pixel shader interface.
		@return HRESULT indicating success or failure of the operation.
	*/
	HRESULT
		CreatePixelShader(const void* pShaderBytecode,
			unsigned int BytecodeLength,
			ID3D11ClassLinkage* pClassLinkage,
			ID3D11PixelShader** ppPixelShader);

	/*
		@brief Creates a buffer resource.
		@details A buffer resource is a type of resource that holds data in a linear array.
		@param pDesc A pointer to a D3D11_BUFFER_DESC structure that describes the buffer to be created.
		@param pInitialData A pointer to a D3D11_SUBRESOURCE_DATA structure that describes the initial data for the buffer. This parameter can be NULL.
		@param ppBuffer A pointer to a variable that receives the address of the created buffer interface.
		@return HRESULT indicating success or failure of the operation.
	*/
	HRESULT
		CreateBuffer(const D3D11_BUFFER_DESC* pDesc,
			const D3D11_SUBRESOURCE_DATA* pInitialData,
			ID3D11Buffer** ppBuffer);

	/*
		@brief Creates a shader resource view.
		@details A shader resource view binds a resource to the shader stages of the pipeline.
		@param pResource A pointer to the resource to create the shader resource view for.
		@param pDesc A pointer to a D3D11_SHADER_RESOURCE_VIEW_DESC structure that describes the shader resource view to be created. This parameter can be NULL.
		@param ppSRView A pointer to a variable that receives the address of the created shader resource view interface.
		@return HRESULT indicating success or failure of the operation.
	*/
	HRESULT
		CreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc,
			ID3D11SamplerState** ppSamplerState);

public:
	ID3D11Device* m_device = nullptr;
};