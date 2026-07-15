#pragma once

#include "Prerequisites.h"

class Device;
class DeviceContext;
class Camera;
class RenderScene;
class EditorViewportPass;

enum class
	RendererType {
	Forward = 0,
	Deferred
};

class
	ISceneRenderer {
public:
	/* 
	 * @brief Default constructor for the ISceneRenderer interface.
	 */
	virtual ~ISceneRenderer() = default;

	/* 
	 * @brief Initializes the scene renderer with the specified device.
	 * @param device The device to initialize the scene renderer with.
	 * @return HRESULT indicating success or failure of the initialization process.
	 */
	virtual HRESULT
		init(Device& device) = 0;

	/* 
	 * @brief Updates the scene renderer.
	 * @param device The device to use for updating the scene renderer.
	 */
	virtual void
		resize(Device& device, unsigned int width, unsigned int height) = 0;

	/* 
	 * @brief Renders the scene using the provided device context, camera, render scene, and viewport pass.
	 * @param deviceContext The device context to use for rendering.
	 * @param camera The camera to use for rendering the scene.
	 * @param scene The render scene containing the objects to be rendered.
	 * @param viewportPass The editor viewport pass that may contain additional information for rendering.
	 */
	virtual void
		render(DeviceContext& deviceContext,
			const Camera& camera,
			RenderScene& scene,
			EditorViewportPass& viewportPass) = 0;

	/* 
	 * @brief Destroys the scene renderer and releases any associated resources.
	 */
	virtual void
		destroy() = 0;

	/* 
	 * @brief Gets the render type of the scene renderer (forward or deferred).
	 * @return The render type of the scene renderer.
	 */
	virtual ID3D11ShaderResourceView*
		getShadowMapSRV() const { return nullptr; }

	/* 
	 * @brief Gets the shader resource view for the pre-shadow pass, if applicable.
	 * @return A pointer to the shader resource view for the pre-shadow pass, or nullptr if not applicable.
	 */
	virtual ID3D11ShaderResourceView*
		getPreShadowSRV() const { return nullptr; }

	/* 
	 * @brief Gets the shader resource view for the G-buffer albedo and metallic information, if applicable.
	 * @return A pointer to the shader resource view for the G-buffer albedo and metallic information, or nullptr if not applicable.
	 */
	virtual ID3D11ShaderResourceView*
		getGBufferAlbedoMetallicSRV() const { return nullptr; }

	/* 
	 * @brief Gets the shader resource view for the G-buffer normal and roughness information, if applicable.
	 * @return A pointer to the shader resource view for the G-buffer normal and roughness information, or nullptr if not applicable.
	 */
	virtual ID3D11ShaderResourceView*
		getGBufferNormalRoughnessSRV() const { return nullptr; }

	/* 
	 * @brief Gets the shader resource view for the G-buffer world space ambient occlusion information, if applicable.
	 * @return A pointer to the shader resource view for the G-buffer world space ambient occlusion information, or nullptr if not applicable.
	 */
	virtual ID3D11ShaderResourceView*
		getGBufferWorldAoSRV() const { return nullptr; }

	/* 
	 * @brief Gets the shader resource view for the G-buffer emissive and alpha information, if applicable.
	 * @return A pointer to the shader resource view for the G-buffer emissive and alpha information, or nullptr if not applicable.
	 */
	virtual ID3D11ShaderResourceView*
		getGBufferEmissiveAlphaSRV() const { return nullptr; }

	/* 
	 * @brief Gets the shader resource view for the final rendered scene, if applicable.
	 * @return A pointer to the shader resource view for the final rendered scene, or nullptr if not applicable.
	 */
	virtual void
		setShadowFactorDebugEnabled(bool enabled) { (void)enabled; }

	/* 
	 * @brief Enables or disables debug visualization for the shadow factor, which can help in diagnosing issues with shadow rendering.
	 * @param enabled A boolean value indicating whether to enable (true) or disable (false) shadow factor debug visualization.
	 */
	virtual void
		setDeferredDebugViewMode(int mode) { (void)mode; }

	/* 
	 * @brief Sets the debug view mode for deferred rendering, which can be used to visualize different aspects of the G-buffer or lighting calculations for debugging purposes.
	 * @param mode An integer value representing the debug view mode to set. The specific modes available may depend on the implementation of the scene renderer and could include options such as visualizing albedo, normals, depth, or other G-buffer components.
	 */
	virtual const char*
		getDebugName() const = 0;
};