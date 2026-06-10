#pragma once
#include "Prerequisites.h"
#include "Window.h"
#include "Device.h"
#include "DeviceContext.h"
#include "SwapChain.h"
#include "Texture.h"
#include "RenderTargetView.h"
#include "DepthStencilView.h"
#include "Viewport.h"
#include "ShaderProgram.h"
#include "MeshComponent.h"
#include "Buffer.h"
#include "SamplerState.h"
#include "Model3D.h"
#include "ECS/Actor.h"
#include "EngineUtilities\GUI\UserInterface.h"
#include "SceneGraph\SceneGraph.h"
#include "EngineUtilities/Utilities/Camera.h"
#include "EngineUtilities/Utilities/Skybox.h"
#include "EngineUtilities\Utilities\LayoutBuilder.h"
#include "EngineUtilities/Utilities/EditorViewportPass.h"
#include "ECS/LightComponent.h"
#include "ECS/MeshRendererComponent.h"
#include "Rendering/Material.h"
#include "Rendering/MaterialInstance.h"
#include "Rendering/Mesh.h"
#include "Rendering/ForwardRenderer.h"
#include "Rendering/RenderScene.h"
#include <string>

extern IMGUI_IMPL_API
LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

/*
	@class BaseApp
	@brief The BaseApp class serves as the foundational application framework for a DirectX 11 application.
	@note This class encapsulates the core components and functionalities required to initialize, run, and manage a DirectX 11 application, including window creation, device and context management, rendering loop, and resource handling.
*/
class
	BaseApp {
public:
	/* 
		@brief Constructor
		@param hInst The instance handle of the application.
		@param nCmdShow The command show parameter that specifies how the window is to be shown.
	*/
	BaseApp() = default;
	
	/* 
		@brief Destructor
	*/
	~BaseApp() { destroy(); }

	HRESULT
		awake();

	/*
		@brief Runs the application.
		@param hInst The instance handle of the application.
		@param nCmdShow The command show parameter that specifies how the window is to be shown.
		@return An integer representing the exit code of the application.
	*/
	int
		run(HINSTANCE hInst, int nCmdShow);

	/*
		@brief Initializes the application.
		@return HRESULT indicating success or failure of the operation.
	*/
	HRESULT
		init();

	/*
		@brief Updates the application state.
		@param deltaTime The time elapsed since the last update, in seconds.
	*/
	void
		update(float deltaTime);

	/*
		@brief Renders the application.
	*/
	void
		render();

	/*
		@brief Destroys the application and releases associated resources.
	*/
	void
		destroy();

	/*
	* @brief Handles window resizing events, updating the swap chain and related resources accordingly.
	* @param newW The new width of the window after resizing.
	* @param newH The new height of the window after resizing.
	* @details This method should be called whenever the window is resized to ensure that the swap chain and related resources (such as render target views and depth stencil views) are updated to match the new window dimensions. It typically involves resizing the swap chain buffers, recreating render target views, and updating the viewport to ensure that rendering continues correctly with the new window size.
	*/
	void
		onResize(UINT newW, UINT newH);

	/*
		@brief Handles resizing of the editor viewport, updating the necessary resources and states to accommodate the new viewport dimensions.
		@details This method should be called whenever the editor viewport is resized to ensure that any resources or states related to the viewport (such as render targets, viewports, or projection matrices) are updated accordingly. It may involve resizing render targets, updating viewports, and adjusting any relevant projection matrices to maintain correct rendering within the new viewport dimensions.
	*/
	void 
		handleEditorViewportResize();

	/*
		@brief Saves the current scene to a file at the specified path.
		@param path The file path where the scene should be saved.
		@return true if the scene was successfully saved, false otherwise.
	*/
	bool 
		saveScene(const std::string& path);

	/* 
		@brief Loads a scene from a file at the specified path.
		@param path The file path from which to load the scene.
		@return true if the scene was successfully loaded, false otherwise.
	*/
	bool 
		loadScene(const std::string& path);

	/* 
		@brief Retrieves the default file path for saving and loading scenes.
		@return A string representing the default file path for scene files.
	*/
	std::string 
		getDefaultScenePath() const;

private:
	/*
		@brief Window procedure for handling window messages.
		@param hWnd The handle to the window.
		@param message The message identifier.
		@param wParam Additional message information (varies by message).
		@param lParam Additional message information (varies by message).
		@return LRESULT indicating the result of the message processing.
	*/
	static LRESULT CALLBACK
		WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	Window                              m_window;
	Device															m_device;
	DeviceContext												m_deviceContext;
	SwapChain														m_swapChain;
	Texture															m_backBuffer;
	RenderTargetView										m_renderTargetView;
	Texture															m_depthStencil;
	DepthStencilView										m_depthStencilView;
	Viewport														m_viewport;
	ShaderProgram												m_shaderProgram;
	//Buffer															m_cbNeverChanges;
	//Buffer															m_cbChangeOnResize;
	bool m_d3dReady = false;
	Buffer m_constantBuffer;
	CBMain m_constantBufferStruct;

	// Textures
	Texture m_AlbedoSRV;
	Texture m_MetallicSRV;
	Texture m_RoughnessSRV;
	Texture m_AOSRV;
	Texture m_NormalSRV;

	Texture m_EmissiveSRV;

	Texture m_gameboyAlbedoSRV;
	Texture m_gameboyNormalSRV;
	Texture m_gameboyMetallicSRV;
	Texture m_gameboyRoughnessSRV;
	Texture m_gameboyAOSRV;

	Camera															m_camera;

	SceneGraph														m_sceneGraph;
	std::vector<EU::TSharedPointer<Actor>> m_actors;
	EU::TSharedPointer<Actor> m_gameboy;

	EU::TSharedPointer<Actor> m_sciFiToad;

	EU::TSharedPointer<Actor> m_directionalLightActor;

	Model3D*                               m_model;

	Model3D* m_gameboyModel;

	//CBChangeOnResize										cbChangesOnResize;
	//CBNeverChanges											cbNeverChanges;

	GUI																					m_gui;

	bool m_guiInitialized = false;

	EU::Vector3 m_cameraPos;

	Skybox m_skybox;
	Texture															m_skyboxTex;
	RasterizerState m_defaultRasterizer;
	DepthStencilState m_defaultDepthStencil;

	SamplerState m_defaultSampler;
	Mesh m_sciFiToadRenderMesh;
	Mesh m_gameboyRenderMesh;
	Material m_pbrMaterial;
	Material m_transparentPbrMaterial;
	MaterialInstance m_sciFiToadMaterial;
	MaterialInstance m_gameboyMaterial;

	EditorViewportPass m_editorViewportPass;
	ForwardRenderer m_forwardRenderer;
	RenderScene m_renderScene;
	bool m_editorViewportResizePending = false;
	unsigned int m_pendingViewportWidth = 1;
	unsigned int m_pendingViewportHeight = 1;

	unsigned int m_lastRequestedViewportWidth = 1;
	unsigned int m_lastRequestedViewportHeight = 1;
	int m_viewportResizeStableFrames = 0;
};