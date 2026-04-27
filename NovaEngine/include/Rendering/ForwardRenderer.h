#pragma once
#include "Prerequisites.h"
#include "Buffer.h"
#include "DepthStencilState.h"
#include "DepthStencilView.h"
#include "RasterizerState.h"
#include "Rendering/RenderScene.h"
#include "Rendering/RenderTypes.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "EngineUtilities/Utilities/EditorViewportPass.h"

// Forward Declarations
class Device;
class DeviceContext;
class Camera;
class Material;

/*
 * @class ForwardRenderer
 * @brief The ForwardRenderer class implements a forward rendering pipeline for rendering 3D scenes. It manages the necessary resources, such as constant buffers, pipeline states, and shadow mapping resources, to perform rendering operations. The class provides methods for initializing resources, resizing the viewport, updating per-frame data, and rendering the scene. It also includes functionality for rendering shadow maps and handling different render passes (opaque, transparent, skybox).
 */
class 
ForwardRenderer {
public:
	/*
	 * @brief Default constructor
	 * @details Initializes an instance of the ForwardRenderer class with default values. The constructor does not perform any resource allocation or initialization, and it is the responsibility of the caller to call the init method to set up the necessary resources for rendering.
	 */
	HRESULT
	init(Device& device);

	/*
	 * @brief Resizes the renderer's resources to accommodate a new viewport size.
	 * @details This method updates the resources associated with the renderer, such as render target views and depth stencil views, to accommodate a new width and height for the viewport. It takes a reference to a Device object for resource creation and the new dimensions of the viewport. The method returns an HRESULT indicating success or failure of the resizing process.
	 * @param device The device to create resources on.
	 * @param width The new width of the viewport.
	 * @param height The new height of the viewport.
	 * @return HRESULT indicating success or failure of the operation.
	 */
	void
	resize(Device& device, unsigned int width, unsigned int height);

	/*
	 * @brief Updates per-frame data for the renderer.
	 * @details This method updates the constant buffers and other per-frame data required for rendering the scene. It takes references to a Camera object, a RenderScene object, and a DeviceContext for rendering operations. The method is responsible for updating the necessary data structures to ensure that the renderer has the correct information for rendering the current frame, including camera matrices, lighting information, and any other relevant per-frame data.
	 * @param camera The camera object containing view and projection matrices.
	 * @param scene The render scene containing the objects and lighting information for the current frame.
	 * @param deviceContext The device context to use for rendering operations.
	 * @return void
	 */
	void
	updatePerFrame(const Camera& camera, 
								 const RenderScene& scene, 
								 DeviceContext& deviceContext);

	/*
	 * @brief Renders the scene using the forward rendering pipeline.
	 * @details This method performs the rendering operations for the scene, including rendering shadow maps, opaque objects, transparent objects, and the skybox. It takes references to a DeviceContext for rendering operations, a Camera object for view and projection matrices, a RenderScene containing the objects and lighting information, and an EditorViewportPass for rendering to the editor viewport. The method is responsible for orchestrating the different render passes and ensuring that the scene is rendered correctly with shadows and proper blending.
	 * @param deviceContext The device context to use for rendering operations.
	 * @param camera The camera object containing view and projection matrices.
	 * @param scene The render scene containing the objects and lighting information for the current frame.
	 * @param viewportPass The editor viewport pass for rendering to the editor interface.
	 * @return void
	 */
	void
	render(DeviceContext& deviceContext,
				 const Camera& camera,
				 RenderScene& scene,
				 EditorViewportPass& viewportPass);

	/*
	 * @brief Destroys the resources associated with the renderer.
	 * @details This method releases any resources allocated by the ForwardRenderer instance, including constant buffers, pipeline states, shadow mapping resources, and any other resources used for rendering. It is important to call this method before destroying an instance of ForwardRenderer to ensure that resources are properly released and to prevent memory leaks.
	 * @return void
	 */
	void
	destroy();

	/*
	 * @brief Retrieves the shader resource view (SRV) of the shadow map.
	 * @details This method returns a pointer to the shader resource view (SRV) associated with the shadow map depth texture. The SRV can be used for sampling the shadow map in shader programs, allowing for shadow mapping effects in the rendered scene.
	 * @return A pointer to the ID3D11ShaderResourceView representing the SRV of the shadow map depth texture.
	 */
	ID3D11ShaderResourceView* 
	getShadowMapSRV() const { return m_shadowDepthSRV.m_textureFromImg; }

	/*
	 * @brief Retrieves the shader resource view (SRV) of the pre-shadow debug pass.
	 * @details This method returns a pointer to the shader resource view (SRV) associated with the pre-shadow debug pass. The SRV can be used for sampling the rendered output of the pre-shadow debug pass in shader programs, allowing for visualization or debugging of shadow mapping results in the editor interface.
	 * @return A pointer to the ID3D11ShaderResourceView representing the SRV of the pre-shadow debug pass.
	 */
	ID3D11ShaderResourceView* 
	getPreShadowSRV() const { return m_preShadowDebugPass.getSRV(); }

private:
	/*
	 * @brief Builds the render queues for opaque and transparent objects based on the current scene and camera.
	 * @details This method processes the objects in the RenderScene and categorizes them into opaque and transparent render queues. The categorization is based on the material properties of the objects, such as whether they have transparency or not. The method also sorts the opaque objects front-to-back and the transparent objects back-to-front to ensure correct rendering order for blending and depth testing.
	 * @param scene The render scene containing the objects and lighting information for the current frame.
	 * @param camera The camera object containing view and projection matrices, which may be used for sorting objects based on their distance from the camera.
	 * @return void
	 */
	void 
	buildQueues(RenderScene& scene, const Camera& camera);

	/*
	 * @brief Renders the pre-shadow debug pass for visualizing shadow mapping results.
	 * @details This method performs the rendering operations for the pre-shadow debug pass, which is used to visualize the results of shadow mapping in the editor interface. It takes a reference to a DeviceContext for rendering operations and a RenderScene containing the objects and lighting information for the current frame. The method is responsible for rendering the necessary geometry and applying the appropriate shaders to visualize the shadow mapping results, such as depth maps or shadow casters.
	 * @param deviceContext The device context to use for rendering operations.
	 * @param scene The render scene containing the objects and lighting information for the current frame.
	 * @return void
	 */
	void 
	renderPreShadowDebugPass(DeviceContext& deviceContext, RenderScene& scene);

	/*
	 * @brief Renders the shadow pass for generating shadow maps.
	 * @details This method performs the rendering operations for the shadow pass, which is responsible for generating shadow maps based on the light sources and shadow casters in the scene. It takes a reference to a DeviceContext for rendering operations and renders the necessary geometry from the perspective of the light sources to create depth textures that can be used for shadow mapping in subsequent render passes.
	 * @param deviceContext The device context to use for rendering operations.
	 * @return void
	 */
	void 
	renderShadowPass(DeviceContext& deviceContext);

	/*
	 * @brief Renders the opaque pass for rendering solid objects in the scene.
	 * @details This method performs the rendering operations for the opaque pass, which is responsible for rendering solid objects that do not have transparency. It takes a reference to a DeviceContext for rendering operations and renders the objects in the opaque render queue using appropriate shaders and pipeline states to ensure correct depth testing and rendering order.
	 * @param deviceContext The device context to use for rendering operations.
	 * @return void
	 */
	void 
	renderOpaquePass(DeviceContext& deviceContext);

	/*
	 * @brief Renders the transparent pass for rendering objects with transparency in the scene.
	 * @details This method performs the rendering operations for the transparent pass, which is responsible for rendering objects that have transparency, such as glass or water. It takes a reference to a DeviceContext for rendering operations and renders the objects in the transparent render queue using appropriate shaders and pipeline states to ensure correct blending and rendering order (back-to-front).
	 * @param deviceContext The device context to use for rendering operations.
	 * @return void
	 */
	void 
	renderTransparentPass(DeviceContext& deviceContext);

	/*
	 * @brief Renders the skybox pass for rendering the skybox environment in the scene.
	 * @details This method performs the rendering operations for the skybox pass, which is responsible for rendering the skybox environment that surrounds the scene. It takes a reference to a DeviceContext for rendering operations and a RenderScene containing the skybox information. The method renders a cube or sphere with the appropriate shaders and textures to create the illusion of a distant environment, such as a sky or horizon.
	 * @param deviceContext The device context to use for rendering operations.
	 * @param scene The render scene containing the skybox information for the current frame.
	 * @return void
	 */
	void 
	renderSkyboxPass(DeviceContext& deviceContext, RenderScene& scene);

	/*
	 * @brief Renders a specific object in the scene based on the current render pass type.
	 * @details This method performs the rendering operations for a specific RenderObject based on the provided RenderPassType. It takes a reference to a DeviceContext for rendering operations, a RenderObject containing the geometry and material information for the object to be rendered, and a RenderPassType indicating whether the object should be rendered in the opaque pass, transparent pass, or any other relevant pass. The method is responsible for setting up the appropriate shaders, pipeline states, and resources to render the object correctly based on its material properties and the current render pass.
	 * @param
	 */
	void 
	renderObject(DeviceContext& deviceContext, 
							 const RenderObject& object, 
							 RenderPassType passType);

	/*
	 * @brief Renders a specific object in the scene for shadow mapping purposes.
	 * @details This method performs the rendering operations for a specific RenderObject during the shadow pass, which is responsible for generating shadow maps. It takes a reference to a DeviceContext for rendering operations and a RenderObject containing the geometry information for the object to be rendered as a shadow caster. The method is responsible for setting up the appropriate shaders, pipeline states, and resources to render the object from the perspective of the light sources, contributing to the generation of depth textures used for shadow mapping in subsequent render passes.
	 * @param deviceContext The device context to use for rendering operations.
	 * @param object The RenderObject containing the geometry information for the object to be rendered as a shadow caster.
	 * @return void
	 */
	void 
	renderShadowObject(DeviceContext& deviceContext, const RenderObject& object);

	/*
	 * @brief Creates the resources necessary for shadow mapping, including depth textures, shader resource views, and depth stencil views.
	 * @details This method initializes the resources required for shadow mapping, such as creating a depth texture to store the shadow map, creating a shader resource view (SRV) for sampling the shadow map in shaders, and creating a depth stencil view (DSV) for rendering to the shadow map. It also initializes any shaders or pipeline states specific to shadow mapping. The method takes a reference to a Device object for resource creation and returns an HRESULT indicating success or failure of the operation.
	 * @param device The device to create resources on.
	 * @return HRESULT indicating success or failure of the operation.
	 */
	HRESULT 
	createShadowResources(Device& device);

	/*
	 * @brief Updates the light matrices for shadow mapping based on the current camera and scene information.
	 * @details This method calculates and updates the light view and projection matrices used for shadow mapping based on the current camera position, orientation, and the positions of the light sources in the scene. It takes references to a Camera object and a RenderScene containing the lighting information for the current frame. The method is responsible for ensuring that the light matrices are correctly updated to capture the relevant shadow casters in the scene and to produce accurate shadow maps for rendering.
	 * @param camera The camera object containing view and projection matrices, which may be used for calculating light matrices based on the camera's position and orientation.
	 * @param scene The render scene containing the lighting information for the current frame, which may be used for determining the positions of light sources and shadow casters.
	 * @return void
	 */
	void 
	updateLightMatrices(const Camera& camera, const RenderScene& scene);

	/*
	 * @brief Creates the blend states necessary for rendering transparent objects with different blending modes.
	 * @details This method initializes the blend states used for rendering transparent objects in the scene, such as alpha blending, additive blending, and premultiplied alpha blending. It takes a reference to a Device object for resource creation and returns an HRESULT indicating success or failure of the operation. The method is responsible for setting up the appropriate blend state descriptions and creating the corresponding blend state objects that can be used during rendering to achieve the desired blending effects for transparent materials.
	 * @param device The device to create resources on.
	 * @return HRESULT indicating success or failure of the operation.
	 */
	HRESULT 
	createBlendStates(Device& device);

	/*
	 * @brief Resolves the appropriate blend state for a given material based on its properties.
	 * @details This method determines which blend state to use for rendering a material based on its properties, such as whether it has transparency, the type of blending it requires, and any other relevant factors. It takes a pointer to a Material object and returns a pointer to the corresponding ID3D11BlendState that should be used for rendering objects with that material. The method is responsible for ensuring that the correct blend state is selected to achieve the desired visual effects for transparent materials in the scene.
	 * @param material A pointer to the Material object for which to resolve the blend state.
	 * @return A pointer to the ID3D11BlendState representing the appropriate blend state for the given material.
	 */
	ID3D11BlendState* 
	resolveBlendState(const Material* material) const;

private:
	// --- Constant Buffers to feed the Shaders ---
	Buffer m_perFrameBuffer;
	Buffer m_perObjectBuffer;
	Buffer m_perMaterialBuffer;

	// --- Pipeline States ---
	DepthStencilState m_transparentDepthStencil;
	ID3D11BlendState* m_alphaBlendState = nullptr;
	ID3D11BlendState* m_opaqueBlendState = nullptr;
	ID3D11BlendState* m_additiveBlendState = nullptr;
	ID3D11BlendState* m_premultipliedBlendState = nullptr;
	float m_blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	// --- Shadow Mapping Specific Resources ---
	Texture m_shadowDepthTexture;
	Texture m_shadowDepthSRV;
	DepthStencilView m_shadowDSV;
	ShaderProgram m_shadowShader;
	RasterizerState m_shadowRasterizer;
	unsigned int m_shadowMapSize = 2048;
	EditorViewportPass m_preShadowDebugPass;
	bool m_applyShadows = true;


	// --- CPU-side data structures for the Constant Buffers updates ---
	CBPerFrame m_cbPerFrame{};
	CBPerObject m_cbPerObject{};
	CBPerMaterial m_cbPerMaterial{};

	// --- Render Queues ---
	std::vector<const RenderObject*> m_opaqueQueue;
	std::vector<const RenderObject*> m_transparentQueue;
};