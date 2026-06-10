#pragma once
#include "Prerequisites.h"

// Forward Declarations
class Mesh;
class MaterialInstance;

/*
 * @brief MaterialDomain enumeration defines the different categories of materials based on their rendering characteristics.
 * @details The MaterialDomain enumeration includes values such as Opaque, Masked, and Transparent, which categorize materials based on how they should be rendered in the scene. Opaque materials are fully solid and write to the depth buffer, masked materials are solid but have cutout holes (e.g., chainlink fence) and use Alpha-to-Coverage or clip(), while transparent materials are partially see-through and require back-to-front sorting for correct rendering.
 * @enum MaterialDomain
 * @value Opaque Fully solid. Writes to depth buffer.
 * @value Masked Solid but with cutout holes (e.g., chainlink fence). Uses Alpha-to-Coverage or clip().
 * @value Transparent Partially see-through. Requires back-to-front sorting.
 */
enum class 
MaterialDomain {
	Opaque = 0,    ///< Fully solid. Writes to depth buffer.
	Masked,        ///< Solid but with cutout holes (e.g., chainlink fence). Uses Alpha-to-Coverage or clip().
	Transparent    ///< Partially see-through. Requires back-to-front sorting.
};

/*
 * @brief BlendMode enumeration defines the different blending modes that can be applied to materials for rendering transparent objects in a 3D scene.
 * @details The BlendMode enumeration includes values such as Opaque, Alpha, Additive, and PremultipliedAlpha, which specify how the colors of transparent materials should be blended with the background and other objects in the scene. Opaque mode overwrites existing pixels, Alpha mode uses standard transparency blending based on the alpha value, Additive mode adds the source and destination colors together (useful for effects like fire or magic), and PremultipliedAlpha mode assumes that the RGB values are pre-multiplied by the alpha value for more accurate blending results.
 * @enum BlendMode
 * @value Opaque Overwrites existing pixel (Src * 1 + Dest * 0)
 * @value Alpha Standard transparency (Src * Alpha + Dest * (1 - Alpha))
 * @value Additive Used for fire/magic (Src * 1 + Dest * 1)
 * @value PremultipliedAlpha Advanced blending where RGB is pre-multiplied by Alpha.
 */
enum class 
BlendMode {
	Opaque = 0,             ///< Overwrites existing pixel (Src * 1 + Dest * 0)
	Alpha,                  ///< Standard transparency (Src * Alpha + Dest * (1 - Alpha))
	Additive,               ///< Used for fire/magic (Src * 1 + Dest * 1)
	PremultipliedAlpha      ///< Advanced blending where RGB is pre-multiplied by Alpha.
};

/*
 * @brief RenderPassType enumeration defines the different types of render passes that can be performed in a rendering pipeline for a 3D scene.
 * @details The RenderPassType enumeration includes values such as Shadow, Opaque, Skybox, Transparent, and Editor, which categorize the different stages of rendering based on the type of objects being rendered and their specific requirements. The Shadow pass is used for drawing to the depth-only shadow map, the Opaque pass is for drawing solid geometry, the Skybox pass is for drawing the background environment, the Transparent pass is for drawing glass or water with transparency, and the Editor pass is for drawing gizmos, grid, and UI elements in an editor interface.
 * @enum RenderPassType
 * @value Shadow Drawing to the depth-only shadow map.
 * @value Opaque Drawing solid geometry.
 * @value Skybox Drawing the background environment.
 * @value Transparent Drawing glass/water.
 * @value Editor Drawing gizmos, grid, and UI elements.
 */
enum class 
RenderPassType {
	Shadow = 0,    ///< Drawing to the depth-only shadow map.
	Opaque,        ///< Drawing solid geometry.
	Skybox,        ///< Drawing the background environment.
	Transparent,   ///< Drawing glass/water.
	Editor         ///< Drawing gizmos, grid, and UI elements.
};

/*
 * @brief LightType enumeration defines the different types of light sources that can be used in a 3D scene for rendering and lighting calculations.
 * @details The LightType enumeration includes values such as Directional, Point, and Spot, which categorize light sources based on their behavior and how they emit light. Directional lights emit infinite parallel rays (like the Sun), point lights emit light in all directions from a single point (like a lightbulb), and spotlights emit a cone of light in a specific direction (like a flashlight). Each light type has unique properties that influence how it interacts with objects in the scene and contributes to the overall lighting and shading effects.
 * @enum LightType
 * @value Directional Infinite parallel rays (like the Sun).
 * @value Point Emits light in all directions from a point (like a lightbulb).
 * @value Spot Emits a cone of light (like a flashlight).
 */
enum class 
LightType {
	Directional = 0, ///< Infinite parallel rays (like the Sun).
	Point,           ///< Emits light in all directions from a point (like a lightbulb).
	Spot             ///< Emits a cone of light (like a flashlight).
};

constexpr int kMaxSceneLights = 8; ///< Maximum number of lights supported in the scene. This constant can be used to define array sizes and limits for light data in the rendering pipeline.

/*
 * @struct LightData
 * @brief The LightData structure represents the properties of a light source in a 3D scene, including its type, color, intensity, direction, range, position, and spot angle. This structure is used to define the characteristics of light sources that contribute to the lighting and shading effects in the rendered scene.
 * @details The LightData structure includes a LightType enumeration to specify the type of light (Directional, Point, Spot), an EU::Vector3 for the color of the light, a float for the intensity of the light, an EU::Vector3 for the direction of directional lights or spotlights, a float for the range of point lights or spotlights, an EU::Vector3 for the position of point lights or spotlights, and a float for the spot angle of spotlights. This structure allows for flexible representation of different types of light sources and their properties in the rendering pipeline.
 */
struct 
LightData {
	LightType type = LightType::Directional;
	EU::Vector3 color = EU::Vector3(1.0f, 1.0f, 1.0f);
	float intensity = 1.0f;

	EU::Vector3 direction = EU::Vector3(0.0f, -1.0f, 0.0f);
	float range = 0.0f;

	EU::Vector3 position = EU::Vector3(0.0f, 0.0f, 0.0f);
	float spotAngle = 0.0f;
};

/*
 * @struct MaterialParams
 * @brief The MaterialParams structure encapsulates the various parameters that define the visual properties of a material in a 3D scene, including base color, metallicity, roughness, ambient occlusion, normal map scale, emissive strength, and alpha cutoff. These parameters are used in shading calculations to determine how the material interacts with light and how it appears when rendered.
 * @details The MaterialParams structure includes an XMFLOAT4 for the base color of the material (including alpha), a float for the metallic property that defines how metallic the surface is, a float for the roughness that defines how rough or smooth the surface is, a float for ambient occlusion that adds shadowing effects in crevices, a float for normal map scale that controls the intensity of normal mapping effects, a float for emissive strength that defines how much light the material emits, and a float for alpha cutoff that determines the threshold for alpha testing in masked materials. This structure allows for comprehensive representation of material properties used in physically based rendering (PBR) workflows.
 */
struct 
MaterialParams {
	XMFLOAT4 baseColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	float metallic = 1.0f;
	float roughness = 1.0f;
	float ao = 1.0f;
	float normalScale = 1.0f;
	float emissiveStrength = 1.0f;
	float alphaCutoff = 0.5f;
};

//======================================================================================
// CONSTANT BUFFER STRUCTURES
// Context: These structs are copied directly into GPU memory. DirectX 11 enforces strict 
// 16-byte (float4) alignment rules for HLSL Constant Buffers. 
// Why the 'pad' variables exist: If a struct doesn't naturally end on a 16-byte boundary, 
// the GPU will silently misalign the data, causing graphical glitches. The 'pad' floats 
// force the C++ struct to match the HLSL memory layout perfectly.
//======================================================================================

/*
 * @struct CBPerFrame
 * @brief The CBPerFrame structure represents the constant buffer data that is updated once per frame and contains information about the camera view, projection, light view-projection matrix, camera position, light direction, and light color. This structure is used to pass per-frame data to shaders for rendering operations in a 3D scene.
 * @details The CBPerFrame structure includes XMFLOAT4X4 matrices for the camera view, projection, and light view-projection transformations, an EU::Vector3 for the camera position with padding to ensure 16-byte alignment, an EU::Vector3 for the light direction with padding for alignment, and an EU::Vector3 for the light color with padding for alignment. This structure allows for efficient updating of per-frame data that influences the rendering of objects in the scene based on the current camera and lighting conditions.
 */
struct 
CBPerFrame {
	XMFLOAT4X4 View{};
	XMFLOAT4X4 Projection{};
	XMFLOAT4X4 LightViewProjection{};

	EU::Vector3 CameraPos{};
	float pad0 = 0.0f; // Pads CameraPos (12 bytes) to 16 bytes.

	EU::Vector3 LightDir = EU::Vector3(0.0f, -1.0f, 0.0f);
	float pad1 = 0.0f; // Pads LightDir (12 bytes) to 16 bytes.

	EU::Vector3 LightColor = EU::Vector3(1.0f, 1.0f, 1.0f);
	float pad2 = 0.0f; // Pads LightColor (12 bytes) to 16 bytes.

	EU::Vector3 LightPosition = EU::Vector3(0.0f, 3.0f, 0.0f);
	int LightType = 0; // 4 bytes to align to 16 bytes. (Directional=0, Point=1, Spot=2)

	XMFLOAT4 LightPositionsRanges[kMaxSceneLights]{}; // x,y,z = position, w = range. Array of vec4 to fit 8 lights (32 bytes).
	XMFLOAT4 LightColorsTypes[kMaxSceneLights]{}; // x,y,z = color, w = type. Array of vec4 to fit 8 lights (32 bytes).
	XMFLOAT4 LightDirectionsIntensities[kMaxSceneLights]{}; // x,y,z = direction, w = intensity. Array of vec4 to fit 8 lights (32 bytes).

	int LightCount = 0; // 4 bytes to align to 16 bytes.
	XMFLOAT3 pad3 = XMFLOAT3(0.0f, 0.0f, 0.0f); // Pads LightCount (4 bytes) to 16 bytes.
};

/*
 * @struct CBPerObject
 * @brief The CBPerObject structure represents the constant buffer data that is updated for each object being rendered and contains the world transformation matrix. This structure is used to pass per-object data to shaders for rendering operations in a 3D scene.
 * @details The CBPerObject structure includes an XMFLOAT4X4 matrix for the world transformation of the object. This matrix is used in vertex shader calculations to transform the object's vertices from local space to world space, allowing for correct positioning and orientation of the object in the rendered scene. The structure is designed to be efficiently updated for each object during rendering, ensuring that each object's unique transformation is correctly applied.
 */
struct 
CBPerObject {
	XMFLOAT4X4 World{}; // 64 bytes (exactly 4x 16-byte chunks). No padding needed.
};

/*
 * @struct CBPerMaterial
 * @brief The CBPerMaterial structure represents the constant buffer data that is updated for each material and contains parameters such as base color, metallicity, roughness, ambient occlusion, normal map scale, emissive strength, and alpha cutoff. This structure is used to pass per-material data to shaders for rendering operations in a 3D scene.
 * @details The CBPerMaterial structure includes an XMFLOAT4 for the base color of the material (including alpha), floats for metallicity, roughness, ambient occlusion, normal map scale, emissive strength, and alpha cutoff. The structure also includes padding floats to ensure that the total size of the struct is a multiple of 16 bytes, which is required for proper alignment in HLSL constant buffers. This structure allows for efficient updating of per-material data that influences the appearance of objects using that material in the rendered scene.
 */
struct 
CBPerMaterial {
	XMFLOAT4 BaseColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f); // 16 bytes

	// Next 6 floats = 24 bytes. 
	float Metallic = 1.0f;
	float Roughness = 1.0f;
	float AO = 1.0f;
	float NormalScale = 1.0f;
	float EmissiveStrength = 1.0f;
	float AlphaCutoff = 0.0f;

	// Padding to push the total struct size to the next multiple of 16 bytes.
	// 16 + 24 = 40 bytes. We need 48 bytes (16 * 3). So we add 8 bytes (2 floats).
	// Note: The code currently has 6 pad floats (24 bytes). This might be over-padding, 
	// but it is safe as long as it matches the HLSL struct identically.
	float pad0 = 0.0f;
	float pad1 = 0.0f;
	float pad2 = 0.0f;
	float pad3 = 0.0f;
	float pad4 = 0.0f;
	float pad5 = 0.0f;
};

/*
 * @struct RenderObject
 * @brief The RenderObject structure represents an individual object in a 3D scene that can be rendered, containing references to its geometry (mesh), material instance, world transformation, and rendering properties such as shadow casting and transparency. This structure is used to organize the data needed for rendering each object in the scene.
 * @details The RenderObject structure includes a pointer to a Mesh that defines the geometry of the object, a pointer to a MaterialInstance that defines the material properties for rendering, a vector of MaterialInstance pointers for cases where multiple materials are used for different submeshes, an XMMATRIX for the world transformation of the object, a boolean indicating whether the object casts shadows, a boolean indicating whether the object is transparent, and a float for pre-calculated distance to the camera used for sorting transparent objects. This structure allows for efficient management of renderable objects in the scene and their associated data for rendering operations.
 */
struct 
RenderObject {
	Mesh* mesh = nullptr;                               ///< The geometry to draw.
	MaterialInstance* materialInstance = nullptr;       ///< Legacy/Single material pointer.
	std::vector<MaterialInstance*> materialInstances;   ///< Array mapping materials to Submeshes.
	XMMATRIX world = XMMatrixIdentity();                ///< Its position in the world.
	bool castShadow = true;                             ///< Does it block light?
	bool transparent = false;                           ///< Should it go to the Transparent queue?
	float distanceToCamera = 0.0f;                      ///< Pre-calculated distance used for back-to-front sorting.
};