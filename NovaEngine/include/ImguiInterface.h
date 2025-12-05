#pragma once
#include "Prerequisites.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "imgui_internal.h"
#include "ECS/Actor.h"
#include "ECS/Transform.h" 
#include "ECS/Entity.h"

class Actor;
class BaseApp;

/*
  @class ImguiInterface
  @brief A class that manages the ImGui interface for the application.
  @note The ImguiInterface class is responsible for initializing, updating, rendering, and destroying the ImGui interface,
				as well as drawing various panels and menus within the interface.
*/
class 
  ImguiInterface {
public:
  /*
		@brief Constructor
  */
  ImguiInterface();

  /*
    @brief Destructor
	*/
  ~ImguiInterface();

  /*
    @brief Initializes the ImGui interface.
    @param window A pointer to the application window.
    @param device A pointer to the Direct3D 11 device.
		@param deviceContext A pointer to the Direct3D 11 device context.
  */
  void
    init(void* window, ID3D11Device* device, ID3D11DeviceContext* deviceContext);

  /*
    @brief Updates the ImGui interface.
		@param application A pointer to the BaseApp application instance.
  */
  void
    update(BaseApp* application);

  /*
		@brief Renders the ImGui interface.
  */
  void
    render();
  /*
		@brief Destroys the ImGui interface.
  */
  void
    destroy();

private:
  /*
		@brief Sets up the docking space for the ImGui interface.
  */
  void
    SetupDockspace();

  /*
		@brief Draws the hierarchy panel in the ImGui interface.
  */
  void
    DrawHierarchyPanel(BaseApp* application);

  /*
		@brief Draws the inspector panel in the ImGui interface.
  */
  void
    DrawInspectorPanel();

  /*
		@brief Draws the main menu bar in the ImGui interface.
  */
  void 
    DrawMainMenu();

  /*
		@brief Sets the dark style for the ImGui interface.
  */
  void 
    SetDarkStyle();

  /*
		@brief Sets a modern dark style for the ImGui interface.
  */
  void
		SetModernDarkStyle();

private:
  Actor* m_selectedActor = nullptr;

	bool m_showHierarchy = true;
	bool m_showInspector = true;

  bool m_dockspaceOpen = true;
  bool m_optFullscreen_persistant = true;
  ImGuiDockNodeFlags m_dockspaceFlags = ImGuiDockNodeFlags_None;
};