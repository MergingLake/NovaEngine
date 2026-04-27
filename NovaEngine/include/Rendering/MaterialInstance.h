#pragma once
#include "Prerequisites.h"
#include "Rendering/RenderTypes.h"

// Forward Declarations
class Material;
class DeviceContext;
class Texture;

/*
 * @class MaterialInstance
 * @brief The MaterialInstance class represents an instance of a material with specific textures and parameters that can be applied to objects in a 3D scene. It manages the association between a Material and its corresponding textures (albedo, normal, metallic, roughness, ambient occlusion, emissive) as well as any additional material parameters that may influence the rendering of objects using this material instance.
 * @details The MaterialInstance class provides methods for setting and retrieving the associated Material, textures, and material parameters. It also includes a method for binding the textures to the appropriate shader stages during rendering operations. This class serves as a container for the specific configuration of a material instance, allowing for flexible assignment of materials to objects in the scene with different texture sets and parameter values.
 */
class 
MaterialInstance {
public:
	// --- Setters ---
	/*
	 * @brief Sets the Material associated with this MaterialInstance.
	 * @details This method assigns a pointer to a Material object that defines the properties and resources for rendering objects with this material instance. The Material object encapsulates the shader program, rasterizer state, depth stencil state, sampler state, material domain, and blend mode that influence how objects using this material instance will be rendered in the scene.
	 * @param material A pointer to the Material object to be associated with this MaterialInstance.
	 * @return void
	 */
	void 
	setMaterial(Material* material) { m_material = material; }

	/*
	 * @brief Sets the albedo texture for this MaterialInstance.
	 * @details This method assigns a pointer to a Texture object that represents the albedo (diffuse) texture for this material instance. The albedo texture defines the base color of objects using this material instance and is typically sampled in the pixel shader to determine the final color output for rendered objects.
	 * @param texture A pointer to the Texture object to be used as the albedo texture for this MaterialInstance.
	 * @return void
	 */
	void 
	setAlbedo(Texture* texture) { m_albedo = texture; }

	/*
	 * @brief Sets the normal texture for this MaterialInstance.
	 * @details This method assigns a pointer to a Texture object that represents the normal map for this material instance. The normal texture is used to add surface detail and lighting effects to objects using this material instance by perturbing the surface normals in the pixel shader, allowing for more realistic rendering of surfaces without increasing geometric complexity.
	 * @param texture A pointer to the Texture object to be used as the normal texture for this MaterialInstance.
	 * @return void
	 */
	void 
	setNormal(Texture* texture) { m_normal = texture; }

	/*
	 * @brief Sets the metallic texture for this MaterialInstance.
	 * @details This method assigns a pointer to a Texture object that represents the metallic map for this material instance. The metallic texture is used in physically based rendering (PBR) workflows to define which parts of the surface are metallic and which are non-metallic, influencing how the surface interacts with light and contributes to reflections and highlights in the rendered scene.
	 * @param texture A pointer to the Texture object to be used as the metallic texture for this MaterialInstance.
	 * @return void
	 */
	void 
	setMetallic(Texture* texture) { m_metallic = texture; }

	/*
	 * @brief Sets the roughness texture for this MaterialInstance.
	 * @details This method assigns a pointer to a Texture object that represents the roughness map for this material instance. The roughness texture is used in physically based rendering (PBR) workflows to define the microsurface roughness of the material, influencing how light scatters on the surface and contributing to the appearance of reflections and highlights in the rendered scene.
	 * @param texture A pointer to the Texture object to be used as the roughness texture for this MaterialInstance.
	 * @return void
	 */
	void 
	setRoughness(Texture* texture) { m_roughness = texture; }

	/*
	 * @brief Sets the ambient occlusion (AO) texture for this MaterialInstance.
	 * @details This method assigns a pointer to a Texture object that represents the ambient occlusion (AO) map for this material instance. The AO texture is used to add shadowing effects to objects using this material instance by simulating the occlusion of ambient light in crevices and areas where surfaces are close together, enhancing the overall realism of the rendered scene.
	 * @param texture A pointer to the Texture object to be used as the ambient occlusion texture for this MaterialInstance.
	 * @return void
	 */
	void 
	setAO(Texture* texture) { m_ao = texture; }

	/*
	 * @brief Sets the emissive texture for this MaterialInstance.
	 * @details This method assigns a pointer to a Texture object that represents the emissive map for this material instance. The emissive texture is used to define areas of the surface that emit light, allowing objects using this material instance to appear self-illuminated in the rendered scene, which can be useful for effects such as glowing materials or light sources.
	 * @param texture A pointer to the Texture object to be used as the emissive texture for this MaterialInstance.
	 * @return void
	 */
	void 
	setEmissive(Texture* texture) { m_emissive = texture; }

	// --- Getters ---
	/*
	 * @brief Retrieves the Material associated with this MaterialInstance.
	 * @details This method returns a pointer to the Material object that is currently assigned to this MaterialInstance. The Material object defines the properties and resources for rendering objects with this material instance, including the shader program, rasterizer state, depth stencil state, sampler state, material domain, and blend mode.
	 * @return A pointer to the Material object associated with this MaterialInstance.
	 */
	Material* 
	getMaterial() const { return m_material; }

	/*
	 * @brief Retrieves the albedo texture for this MaterialInstance.
	 * @details This method returns a pointer to the Texture object that is currently assigned as the albedo (diffuse) texture for this material instance. The albedo texture defines the base color of objects using this material instance and is typically sampled in the pixel shader to determine the final color output for rendered objects.
	 * @return A pointer to the Texture object used as the albedo texture for this MaterialInstance.
	 */
	Texture* 
	getAlbedo() const { return m_albedo; }

	/*
	 * @brief Retrieves the normal texture for this MaterialInstance.
	 * @details This method returns a pointer to the Texture object that is currently assigned as the normal map for this material instance. The normal texture is used to add surface detail and lighting effects to objects using this material instance by perturbing the surface normals in the pixel shader, allowing for more realistic rendering of surfaces without increasing geometric complexity.
	 * @return A pointer to the Texture object used as the normal texture for this MaterialInstance.
	 */
	Texture* 
	getNormal() const { return m_normal; }

	/*
	 * @brief Retrieves the metallic texture for this MaterialInstance.
	 * @details This method returns a pointer to the Texture object that is currently assigned as the metallic map for this material instance. The metallic texture is used in physically based rendering (PBR) workflows to define which parts of the surface are metallic and which are non-metallic, influencing how the surface interacts with light and contributes to reflections and highlights in the rendered scene.
	 * @return A pointer to the Texture object used as the metallic texture for this MaterialInstance.
	 */
	Texture* 
	getMetallic() const { return m_metallic; }

	/*
	 * @brief Retrieves the roughness texture for this MaterialInstance.
	 * @details This method returns a pointer to the Texture object that is currently assigned as the roughness map for this material instance. The roughness texture is used in physically based rendering (PBR) workflows to define the microsurface roughness of the material, influencing how light scatters on the surface and contributing to the appearance of reflections and highlights in the rendered scene.
	 * @return A pointer to the Texture object used as the roughness texture for this MaterialInstance.
	 */
	Texture* 
	getRoughness() const { return m_roughness; }

	/*
	 * @brief Retrieves the ambient occlusion (AO) texture for this MaterialInstance.
	 * @details This method returns a pointer to the Texture object that is currently assigned as the ambient occlusion (AO) map for this material instance. The AO texture is used to add shadowing effects to objects using this material instance by simulating the occlusion of ambient light in crevices and areas where surfaces are close together, enhancing the overall realism of the rendered scene.
	 * @return A pointer to the Texture object used as the ambient occlusion texture for this MaterialInstance.
	 */
	Texture* 
	getAO() const { return m_ao; }

	/*
	 * @brief Retrieves the emissive texture for this MaterialInstance.
	 * @details This method returns a pointer to the Texture object that is currently assigned as the emissive map for this material instance. The emissive texture is used to define areas of the surface that emit light, allowing objects using this material instance to appear self-illuminated in the rendered scene, which can be useful for effects such as glowing materials or light sources.
	 * @return A pointer to the Texture object used as the emissive texture for this MaterialInstance.
	 */
	Texture* 
	getEmissive() const { return m_emissive; }

	/*
	 * @brief Retrieves the material parameters for this MaterialInstance.
	 * @details This method returns a reference to the MaterialParams structure that contains additional parameters for this material instance. The material parameters may include values such as color, roughness, metallicity, or any other relevant properties that influence the rendering of objects using this material instance. The returned reference allows for both reading and modifying the material parameters as needed.
	 * @return A reference to the MaterialParams structure containing the material parameters for this MaterialInstance.
	 */
	MaterialParams& 
	getParams() { return m_params; }

	/*
	 * @brief Retrieves the material parameters for this MaterialInstance (const version).
	 * @details This method returns a const reference to the MaterialParams structure that contains additional parameters for this material instance. The material parameters may include values such as color, roughness, metallicity, or any other relevant properties that influence the rendering of objects using this material instance. The returned const reference allows for reading the material parameters without modifying them.
	 * @return A const reference to the MaterialParams structure containing the material parameters for this MaterialInstance.
	 */
	const MaterialParams& 
	getParams() const { return m_params; }

	/*
	 * @brief Binds the textures of this MaterialInstance to the appropriate shader stages for rendering.
	 * @details This method takes a reference to a DeviceContext and binds the textures associated with this MaterialInstance (albedo, normal, metallic, roughness, ambient occlusion, emissive) to the appropriate shader stages (e.g., pixel shader) for rendering operations. The method ensures that the textures are correctly set up for sampling in the shader programs used for rendering objects with this material instance, allowing for the visual effects defined by the textures to be applied during rendering.
	 * @param deviceContext The device context to use for binding the textures during rendering operations.
	 * @return void
	 */
	void 
	bindTextures(DeviceContext& deviceContext) const;

private:
	Material* m_material = nullptr;      
	Texture* m_albedo = nullptr;
	Texture* m_normal = nullptr;
	Texture* m_metallic = nullptr;
	Texture* m_roughness = nullptr;
	Texture* m_ao = nullptr;
	Texture* m_emissive = nullptr;
	MaterialParams m_params;             
};