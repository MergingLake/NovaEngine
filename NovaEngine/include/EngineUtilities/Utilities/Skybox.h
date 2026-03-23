#pragma once
#include "Prerequisites.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Buffer.h"
#include "SamplerState.h"
#include "Model3D.h"
#include "RasterizerState.h"
#include "DepthStencilState.h"
#include "EngineUtilities\Utilities\Camera.h"
#include "ECS\Actor.h"

class Device;
class DeviceContext;

/*
* @class Skybox
* @brief A class that represents a skybox in a 3D scene, responsible for rendering a cube with a cubemap texture to create the illusion of a distant environment.
*/
class
	Skybox {
public:
	/*
	* @brief Default constructor for the Skybox class.
	*/
	Skybox() = default;
	/*
	* @brief Destructor for the Skybox class, responsible for cleaning up any resources associated with the skybox.
	*/
	~Skybox() = default;

	/*
	* @brief Initializes the skybox with the specified device, device context, and cubemap texture.
	* @param device The device to create resources on.
	* @param deviceContext The device context to use for resource initialization.
	* @param cubemap The texture to use as the cubemap for the skybox.
	* @return HRESULT indicating success or failure of the initialization process.
	*/
	HRESULT
		init(Device& device, DeviceContext* deviceContext, Texture& cubemap);

	/*
	* @brief Updates the skybox based on the camera's position and orientation.
	* @param deviceContext The device context to use for updating resources.
	* @param camera The camera whose position and orientation will be used to update the skybox's view matrix.
	* @details This method should be called each frame to ensure that the skybox is rendered correctly based on the camera's perspective. It typically involves updating the constant buffer with the appropriate view and projection matrices derived from the camera's position and orientation, allowing the skybox to appear stationary in the background while the camera moves through the scene.
	*/
	void
		update(DeviceContext& deviceContext, Camera& camera);

	/*
	* @brief Renders the skybox using the provided device context.
	* @param deviceContext The device context to use for rendering the skybox.
	* @details This method binds the necessary shaders, textures, and states to render the skybox. It typically involves setting the vertex buffer for a cube model, binding the cubemap texture, and issuing a draw call to render the skybox geometry. The skybox should be rendered with depth testing configured to ensure it appears behind all other geometry in the scene, creating the illusion of a distant environment surrounding the camera.
	*/
	void
		render(DeviceContext& deviceContext);
	
	/*
	* @brief Destroys the skybox and releases any associated resources.
	* @details This method should be called when the skybox is no longer needed to free up memory and resources. It will release any GPU resources, clear any loaded data, and reset the state of the Skybox instance.
	*/
	void
		destroy() {}

private:
	ShaderProgram m_shaderProgram;
	Buffer m_constantBuffer;
	SamplerState m_samplerState;
	RasterizerState m_rasterizerState;
	DepthStencilState m_depthStencilState;
	Texture m_skyboxTexture;
	Model3D* m_cubeModel = nullptr;
	EU::TSharedPointer<Actor> m_skybox;

};