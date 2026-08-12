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
#include "EngineUtilities/GUI/UserInterface.h"
#include "SceneGraph\SceneGraph.h"
#include "EngineUtilities\Utilities\Camera.h"
#include "EngineUtilities\Utilities\Skybox.h"
#include "EngineUtilities\Utilities\LayoutBuilder.h"
#include "EngineUtilities/Utilities/EditorViewportPass.h"
#include "ECS/LightComponent.h"
#include "ECS/MeshRendererComponent.h"
#include "ECS/LuaScriptComponent.h"
#include "ECS/RigidbodyComponent.h"
#include "ECS/BoxColliderComponent.h"
#include "Rendering/Material.h"
#include "Rendering/MaterialInstance.h"
#include "Rendering/Mesh.h"
#include "Rendering/RenderPipeline.h"
#include "Rendering/RenderScene.h"
#include "SceneGraph/HierarchyComponent.h"
#include <string>

extern IMGUI_IMPL_API
LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

/**
 * @class BaseApp
 * @brief The core application class that initializes and runs the engine.
 * @author Ricardo Rabell
 * @date 2025-10-29
 *
 * BaseApp is responsible for owning and managing the lifecycle of all primary
 * graphics objects (Device, DeviceContext, SwapChain, etc.), handling the
 * main message loop, and orchestrating the per-frame update and render calls.
 * It serves as the central hub for the entire application.
 */
class
BaseApp {
public:
	/**
	 * @brief Constructor.
	 * @param hInst Handle to the application instance.
	 * @param nCmdShow Command show parameter for the main window.
	 */
	BaseApp() = default;

	/**
	 * @brief Destructor.
	 * Automatically calls the destroy() method to ensure proper cleanup.
	 */
	~BaseApp() { destroy(); }

	/**
	* @brief Initializes subsystems that must be ready before main initialization.
	* Typically used for early resource allocation or configuration.
	* @return HRESULT S_OK if successful, otherwise an error code.
	*/
	HRESULT
	awake();

	/**
	 * @brief The main entry point and message loop of the application.
	 * This function initializes the application (via init()) and then enters
	 * the Win32 message loop, processing OS messages and triggering
	 * update() and render() calls each frame.
	 * @param hInst Handle to the application instance.
	 * @param nCmdShow Command show parameter for the main window.
	 * @return int The exit code of the application.
	 */
	int
	run(HINSTANCE hInst, int nCmdShow);

	/**
	 * @brief Initializes all application and graphics systems.
	 * This includes creating the window, initializing the D3D11 device and
	 * swap chain, creating render targets, compiling shaders, and setting
	 * up initial scene geometry and buffers.
	 * @return HRESULT S_OK if all initializations are successful.
	 */
	HRESULT
	init();

	/**
	 * @brief Updates the application logic once per frame.
	 * @param deltaTime The time elapsed since the last frame.
	 */
	void
	update(float deltaTime);

	/**
	 * @brief Renders a single frame.
	 * This function binds all necessary pipeline states (shaders, buffers,
	 * render targets) and issues the final draw calls for the scene.
	 */
	void
	render();

	/**
	 * @brief Cleans up and releases all allocated resources.
	 * This ensures all COM objects (Device, SwapChain, Buffers, etc.)
	 * are properly released and the window is destroyed.
	 */
	void
	destroy();

  /**
  * @brief Handles window resize events and updates all dependent resources.
  *
  * This function is called whenever the application window is resized.
  * It is responsible for resizing the swap chain buffers, recreating the render target
  * and depth-stencil views, and updating the viewport to match the new window dimensions.
  * All graphics resources that depend on the window size should be updated here to ensure
  * correct rendering after a resize event.
  *
  * @param newW The new width of the window in pixels.
  * @param newH The new height of the window in pixels.
  */
	void
		onResize(unsigned int newW, unsigned int newH);

	void 
		handleEditorViewportResize();

	bool 
		saveScene(const std::string& path);

	bool 
		loadScene(const std::string& path);

	std::string 
		getDefaultScenePath() const;

	EngineState 
		getEngineState() const { return m_engineState; }

	void 
		startPlayMode();

	void 
		stopPlayMode();

	void 
		togglePauseMode();

	void 
		initScripting();

private:
	EU::TSharedPointer<Actor>
		createLightActor(const std::string& name = std::string());

	/**
	 * @brief The static window procedure for handling Win32 messages.
	 * @param hWnd The handle to the window receiving the message.
	 * @param message The message identifier.
	 * @param wParam Additional message-specific information.
	 * @param lParam Additional message-specific information.
	 */
	static LRESULT CALLBACK
	wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	//--------------------------------------------------------------------------------------
	// Global Variables
	//--------------------------------------------------------------------------------------
	Window m_window;
	Device m_device;
	DeviceContext m_deviceContext;
	SwapChain m_swapChain;
	Texture m_backBuffer;
	RenderTargetView m_renderTargetView;
	Texture m_depthStencil;
	DepthStencilView m_depthStencilView;
	Viewport m_viewport;
	ShaderProgram m_shaderProgram;
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

	Texture m_sciFiToadAlbedoSRV;
	Texture m_sciFiToadNormalSRV;
	Texture m_sciFiToadMetallicSRV;
	Texture m_sciFiToadRoughnessSRV;
	Texture m_sciFiToadAOSRV;
	Texture m_sciFiToadGlassAlbedoSRV;
	Texture m_sciFiToadGlassNormalSRV;
	Texture m_sciFiToadGlassRoughnessSRV;
	Texture m_sciFiToadHeadAlbedoSRV;
	Texture m_sciFiToadHeadNormalSRV;
	Texture m_sciFiToadHeadRoughnessSRV;

	Camera m_camera;

	SceneGraph m_sceneGraph;
	std::vector<EU::TSharedPointer<Actor>> m_actors;

	EU::TSharedPointer<Actor> m_gameboy;
	EU::TSharedPointer<Actor> m_sciFiToad;
	EU::TSharedPointer<Actor> m_directionalLightActor;

	Model3D* m_model = nullptr;

	Model3D* m_gameboyModel = nullptr;

	Model3D* m_sciFiToadModel = nullptr;

	/** @brief CPU-side struct for the 'ChangeOnResize' constant buffer. */
	//CBChangeOnResize cbChangesOnResize;

	/** @brief CPU-side struct for the 'NeverChanges' constant buffer. */
	//CBNeverChanges cbNeverChanges;

	/**
	* @brief The user interface manager for the application.
	* Handles UI rendering, input, and interaction logic.
	*/
	GUI m_gui;

	bool m_guiInitialized = false;

  /**
   * @brief The current position of the camera in world space.
   */
  EU::Vector3 m_cameraPos;

  /**
  * @brief The skybox manager responsible for rendering the environment background.
  */
  Skybox m_skybox;

  /**
  * @brief The texture resource used for the skybox environment.
  */
  Texture m_skyboxTex;

	Texture m_lightIconTexture;

  /**
	* @brief The default rasterizer state used for rendering.
  */
  RasterizerState m_defaultRasterizer;

  /**
	* @brief The default depth-stencil state used for depth testing.
  */
  DepthStencilState m_defaultDepthStencil;

	SamplerState m_defaultSampler;
	Mesh m_sciFiToadRenderMesh;
	Mesh m_gameboyRenderMesh;
	Material m_pbrMaterial;
	Material m_transparentPbrMaterial;
	Material m_gameboyPbrMaterial;
	Material m_sciFiToadPbrMaterial;
	Material m_sciFiToadGlassPbrMaterial;
	Material m_sciFiToadHeadPbrMaterial;

	MaterialInstance m_gameboyMaterial;
	MaterialInstance m_sciFiToadMaterial;
	MaterialInstance m_sciFiToadGlassMaterial;
	MaterialInstance m_sciFiToadHeadMaterial;

	EditorViewportPass m_editorViewportPass;
	RenderPipeline m_renderPipeline;
	RenderScene m_renderScene;
	bool m_editorViewportResizePending = false;
	unsigned int m_pendingViewportWidth = 1;
	unsigned int m_pendingViewportHeight = 1;

	unsigned int m_lastRequestedViewportWidth = 1;
	unsigned int m_lastRequestedViewportHeight = 1;
	int m_viewportResizeStableFrames = 0;

	// Portapapeles para copiar y pegar entidades
	EU::TSharedPointer<Actor> m_clipboardActor;

	EngineState m_engineState = EngineState::EDITOR;
	sol::state m_luaState;
};