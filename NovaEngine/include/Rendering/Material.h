#pragma once
#include "Prerequisites.h"
#include "Rendering/RenderTypes.h"

// Forward Declarations
class ShaderProgram;
class RasterizerState;
class DepthStencilState;
class SamplerState;

/*
 * @class Material
 * @brief The Material class encapsulates the properties and resources associated with a material used for rendering objects in a 3D scene. It manages the shader program, rasterizer state, depth stencil state, sampler state, material domain, and blend mode that define how an object with this material should be rendered.
 * @details The Material class provides methods for setting and retrieving the shader program, rasterizer state, depth stencil state, sampler state, material domain, and blend mode. It serves as a container for the various properties that influence the rendering of objects using this material, allowing for flexible configuration of rendering behavior based on the material's characteristics.
 */
class 
Material {
public:
	// --- Setters ---
	/*
	 * @brief Sets the shader program to be used for rendering objects with this material.
	 * @details This method assigns a pointer to a ShaderProgram object that defines the vertex and pixel shaders to be used when rendering objects with this material. The shader program encapsulates the GPU code that will be executed during rendering, and it is essential for defining the visual appearance of objects using this material.
	 * @param shader A pointer to the ShaderProgram object to be used for rendering with this material.
	 * @return void
	 */
	void 
	setShader(ShaderProgram* shader) { m_shader = shader; }

	/*
	 * @brief Sets the rasterizer state to be used for rendering objects with this material.
	 * @details This method assigns a pointer to a RasterizerState object that defines the rasterization behavior for rendering objects with this material. The rasterizer state controls how primitives are converted into pixels, including culling mode, fill mode, and other rasterization settings that influence the final rendered output of objects using this material.
	 * @param state A pointer to the RasterizerState object to be used for rendering with this material.
	 * @return void
	 */
	void 
	setRasterizerState(RasterizerState* state) { m_rasterizerState = state; }

	/*
	 * @brief Sets the depth stencil state to be used for rendering objects with this material.
	 * @details This method assigns a pointer to a DepthStencilState object that defines the depth and stencil testing behavior for rendering objects with this material. The depth stencil state controls how depth testing is performed, whether stencil operations are applied, and other related settings that influence the visibility and rendering order of objects using this material.
	 * @param state A pointer to the DepthStencilState object to be used for rendering with this material.
	 * @return void
	 */
	void 
	setDepthStencilState(DepthStencilState* state) { m_depthStencilState = state; }

	/*
	 * @brief Sets the sampler state to be used for rendering objects with this material.
	 * @details This method assigns a pointer to a SamplerState object that defines the texture sampling behavior for rendering objects with this material. The sampler state controls how textures are sampled in shaders, including filtering mode, address mode, and other settings that influence the appearance of textured objects using this material.
	 * @param state A pointer to the SamplerState object to be used for rendering with this material.
	 * @return void
	 */
	void 
	setSamplerState(SamplerState* state) { m_samplerState = state; }

	/*
	 * @brief Sets the material domain for this material.
	 * @details This method assigns a MaterialDomain value that categorizes the material based on its rendering characteristics, such as whether it is opaque, transparent, or belongs to another domain. The material domain can be used to determine how objects with this material should be rendered and how they interact with other objects in the scene.
	 * @param domain The MaterialDomain value to assign to this material.
	 * @return void
	 */
	void 
	setDomain(MaterialDomain domain) { m_domain = domain; }

	/*
	 * @brief Sets the blend mode for this material.
	 * @details This method assigns a BlendMode value that defines how objects with this material should be blended with the background and other objects in the scene. The blend mode can influence the visual appearance of transparent materials and how they interact with lighting and other effects in the rendered scene.
	 * @param blendMode The BlendMode value to assign to this material.
	 * @return void
	 */
	void 
	setBlendMode(BlendMode blendMode) { m_blendMode = blendMode; }

	// --- Getters ---
	/*
	 * @brief Retrieves the shader program associated with this material.
	 * @details This method returns a pointer to the ShaderProgram object that is currently assigned to this material. The shader program defines the vertex and pixel shaders used for rendering objects with this material, and it is essential for determining the visual appearance of those objects in the rendered scene.
	 * @return A pointer to the ShaderProgram object associated with this material.
	 */
	ShaderProgram* 
	getShader() const { return m_shader; }

	/*
	 * @brief Retrieves the rasterizer state associated with this material.
	 * @details This method returns a pointer to the RasterizerState object that is currently assigned to this material. The rasterizer state defines the rasterization behavior for rendering objects with this material, including culling mode, fill mode, and other settings that influence how primitives are converted into pixels during rendering.
	 * @return A pointer to the RasterizerState object associated with this material.
	 */
	RasterizerState* 
	getRasterizerState() const { return m_rasterizerState; }

	/*
	 * @brief Retrieves the depth stencil state associated with this material.
	 * @details This method returns a pointer to the DepthStencilState object that is currently assigned to this material. The depth stencil state defines the depth and stencil testing behavior for rendering objects with this material, including how depth testing is performed and whether stencil operations are applied.
	 * @return A pointer to the DepthStencilState object associated with this material.
	 */
	DepthStencilState* 
	getDepthStencilState() const { return m_depthStencilState; }

	/*
	 * @brief Retrieves the sampler state associated with this material.
	 * @details This method returns a pointer to the SamplerState object that is currently assigned to this material. The sampler state defines the texture sampling behavior for rendering objects with this material, including filtering mode, address mode, and other settings that influence how textures are sampled in shaders.
	 * @return A pointer to the SamplerState object associated with this material.
	 */
	SamplerState* 
	getSamplerState() const { return m_samplerState; }

	/*
	 * @brief Retrieves the material domain associated with this material.
	 * @details This method returns the MaterialDomain value that is currently assigned to this material. The material domain categorizes the material based on its rendering characteristics, such as whether it is opaque, transparent, or belongs to another domain, and can be used to determine how objects with this material should be rendered in the scene.
	 * @return The MaterialDomain value associated with this material.
	 */
	MaterialDomain 
	getDomain() const { return m_domain; }

	/*
	 * @brief Retrieves the blend mode associated with this material.
	 * @details This method returns the BlendMode value that is currently assigned to this material. The blend mode defines how objects with this material should be blended with the background and other objects in the scene, influencing the visual appearance of transparent materials and their interaction with lighting and other effects in the rendered scene.
	 * @return The BlendMode value associated with this material.
	 */
	BlendMode 
	getBlendMode() const { return m_blendMode; }

private:
	
	ShaderProgram* m_shader = nullptr;
	RasterizerState* m_rasterizerState = nullptr;
	DepthStencilState* m_depthStencilState = nullptr;
	SamplerState* m_samplerState = nullptr;
	MaterialDomain m_domain = MaterialDomain::Opaque;
	BlendMode m_blendMode = BlendMode::Opaque;
};