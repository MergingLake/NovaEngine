#pragma once
#include "Prerequisites.h"
#include "ImGuizmo.h"

class Viewport;
class Window;
class Device;
class DeviceContext;
class Actor;

/* 
  @class GUI
  @brief A class that manages the graphical user interface (GUI) of the application.
  @note The GUI class is responsible for initializing, updating, rendering, and destroying the GUI elements of the application. It includes methods for creating toolbars, handling user interactions, and displaying various GUI components such as inspectors and outliners.
*/
class GUI {
public:
	/* 
		@brief Default constructor
  */
  GUI() = default;
	/* 
		@brief Destructor
  */ 
  ~GUI() = default;

  /* 
    @brief Initializes the GUI.
    @details This method sets up any necessary resources or state for the GUI. It should be called before using any other methods of the GUI class.
	*/
  void
    awake();

  /* 
    @brief Initializes the GUI with the necessary context.
    @details This method sets up the GUI with references to the window, device, and device context, allowing it to create and manage GUI elements that interact with these components.
    @param window The window to associate the GUI with.
    @param device The device to use for creating GUI resources.
    @param deviceContext The device context to use for rendering the GUI.
	*/
  void
    init(Window& window, Device& device, DeviceContext& deviceContext);

  /* 
    @brief Updates the GUI.
    @details This method should be called once per frame to update the state of the GUI elements, handle user interactions, and prepare for rendering. It takes references to the viewport and window to allow for any necessary updates based on their states.
    @param viewport The viewport to use for any necessary updates related to the GUI.
		@param window The window to use for any necessary updates related to the GUI.
	*/
  void
    update(Viewport& viewport, Window& window);

  /* 
    @brief Renders the GUI.
    @details This method should be called once per frame after the update method to render the GUI elements on the screen. It takes references to the viewport and window to allow for any necessary rendering based on their states.
		@param viewport The viewport to use for rendering the GUI.
  */
  void
    render();

  /* 
    @brief Destroys the GUI and releases associated resources.
    @details This method should be called when the GUI is no longer needed to clean up any resources and ensure proper memory management.
	*/
  void
    destroy();

  /* 
    @brief Creates a toolbar for the GUI.
		@details This method sets up a toolbar with various buttons and controls for interacting with the application. It can include functionality such as opening files, saving, undo/redo, and other common actions.
	*/
  void
    ToolBar();

  /* 
    @brief Closes the application.
		@details This method can be called to trigger the closing of the application, such as when the user clicks an "Exit" button in the toolbar. It can set a flag to show a confirmation popup before actually closing the application.
	*/
  void
    closeApp();

  /* 
		@brief Displays a confirmation popup for exiting the application.
		@details This method can be called to show a popup dialog asking the user to confirm if they want to exit the application. It can be triggered by the closeApp method and should handle the user's response to either proceed with closing or cancel the action.
	*/
  void
    toolTipData();

  /* 
    @brief Applies a liquid style to the GUI elements.
    @details This method can be called to set a specific style for the GUI elements, such as a liquid or glossy appearance. It takes parameters for opacity and accent color to customize the look of the GUI.
    @param opacity A floating-point value between 0 and 1 that determines the transparency of the GUI elements.
		@param accent An ImVec4 color value that specifies the accent color to use in the liquid style.
	*/
  void
    appleLiquidStyle(float opacity /*0..1f*/, ImVec4 accent /*=#0A84FF*/);

  /* 
    @brief Creates a control for editing a 3D vector (vec3) in the GUI.
    @details This method sets up a control with three input fields for editing the x, y, and z components of a 3D vector. It can include functionality for resetting the values to a default state and adjusting the layout of the control.
    @param label A string label to display next to the control.
    @param values A pointer to an array of three floating-point values representing the x, y, and z components of the vector.
		@param resetValues A floating-point value that can be used to reset the vector components to a default state (default is 0.0f).
		@param columnWidth A floating-point value that specifies the width of the label column in the control (default is 100.0f).
	*/
  void
    vec3Control(const std::string& label,
      float* values,
      float resetValues = 0.0f,
      float columnWidth = 100.0f,
      bool displayAsDegrees = false);

  /* 
    @brief Displays an inspector panel for a given actor in the GUI.
    @details This method can be called to show an inspector panel that displays the properties and components of a specific actor. It allows the user to view and edit the details of the actor, such as its transform, materials, and other components.
		@param actor A shared pointer to the actor for which to display the inspector panel.
	*/
  void
    inspectorGeneral(EU::TSharedPointer<Actor> actor);

  /* 
    @brief Displays a container for the inspector panel of a given actor in the GUI.
		@details This method can be called to set up a container or layout for the inspector panel of a specific actor. It can be used to organize the various sections and controls within the inspector, such as separating the transform properties from the material properties.
		@param actor A shared pointer to the actor for which to display the inspector container.
	*/
  void
    inspectorContainer(EU::TSharedPointer<Actor> actor);

  /* 
    @brief Displays an outliner panel that lists all actors in the scene in the GUI.
		@details This method can be called to show an outliner panel that provides a hierarchical view of all actors in the scene. It allows the user to select and manage actors, such as renaming them, changing their order in the hierarchy, or toggling their visibility.
		@param actors A vector of shared pointers to the actors in the scene to be displayed in the outliner.
	*/
  void
    outliner(const std::vector<EU::TSharedPointer<Actor>>& actors);

  /* 
		@brief Displays a transform editing panel for a given actor in the GUI.
		@details This method can be called to show a panel that allows the user to edit the transform properties of a specific actor, such as its position, rotation, and scale. It can include controls for adjusting these properties and visualizing the changes in the scene.
		@param view The view matrix to use for visualizing the transform changes.
		@param projection The projection matrix to use for visualizing the transform changes.
		@param actor A shared pointer to the actor for which to display the transform editing panel.
	*/
  void
    editTransform(Camera& cam, Window& window, EU::TSharedPointer<Actor> actor);

  /* 
		@brief Displays a toolbar for gizmo controls in the GUI.
		@details This method can be called to set up a toolbar that provides controls for manipulating gizmos in the scene, such as translation, rotation, and scaling gizmos. It allows the user to switch between different gizmo modes and adjust their settings.
  */
  void
    drawGizmoToolbar();

  /*
		@brief Converts an XMMATRIX to a float array suitable for use with ImGuizmo.
		@details This method takes an XMMATRIX and stores its values in a float array in the format expected by ImGuizmo for manipulation. It uses an intermediate XMFLOAT4X4 to store the matrix values before copying them to the destination float array.
		@param mat The XMMATRIX to convert.
		@param dest A pointer to a float array with at least 16 elements where the converted matrix values will be stored.
  */
  void ToFloatArray(const XMMATRIX& mat, float* dest) {
    XMFLOAT4X4 temp;
    XMStoreFloat4x4(&temp, mat);
    memcpy(dest, &temp, sizeof(float) * 16);
  }

  /* 
    @brief Draws the top ribbon of the studio interface.
    @details This method can be called to render the top ribbon of the studio interface, which typically includes menu options, toolbars, and other controls for managing the application. It should be called during the GUI rendering phase to ensure that it is displayed correctly on the screen.
	*/
  void
    drawStudioTopRibbon();

  /* 
    @brief Draws the viewport panel in the GUI.
    @details This method can be called to render the viewport panel, which displays the rendered scene from the camera's perspective. It takes a shader resource view (SRV) of the viewport texture to display it within the panel.
		@param viewportSRV A pointer to an ID3D11ShaderResourceView representing the texture of the viewport to be displayed in the panel.
	*/
  void
    drawViewportPanel(ID3D11ShaderResourceView* viewportSRV);

	/* 
    @brief Draws a debug panel for rendering information in the GUI.
    @details This method can be called to render a debug panel that displays various rendering-related information, such as the pre-shadow map, the final viewport output, and the shadow map. It takes shader resource views (SRVs) for each of these textures to display them within the panel for debugging purposes.
    @param preShadowSRV A pointer to an ID3D11ShaderResourceView representing the pre-shadow map texture to be displayed in the debug panel.
    @param finalViewportSRV A pointer to an ID3D11ShaderResourceView representing the final viewport output texture to be displayed in the debug panel.
		@param shadowMapSRV A pointer to an ID3D11ShaderResourceView representing the shadow map texture to be displayed in the debug panel.
	*/
  void
    drawRenderDebugPanel(ID3D11ShaderResourceView* preShadowSRV,
      ID3D11ShaderResourceView* finalViewportSRV,
      ID3D11ShaderResourceView* shadowMapSRV);

	/* 
    @brief Draws the dockspace for the editor interface in the GUI.
		@details This method can be called to set up and render the dockspace for the editor interface, which allows for flexible arrangement of panels and windows within the editor. It should be called during the GUI rendering phase to ensure that it is displayed correctly on the screen and allows for docking and undocking of panels as needed.
  */
  void
    drawEditorDockspace();

  /**
   * @brief Consume de forma atomica la solicitud de guardado emitida desde la UI.
   * @return `true` una sola vez por peticion de guardado.
   */
  bool
    consumeSaveSceneRequest() {
    const bool requested = m_requestSaveScene;
    m_requestSaveScene = false;
    return requested;
  }

private:
  bool checkboxValue = true;
  bool checkboxValue2 = false;
  std::vector<const char*> m_objectsNames;
  std::vector<const char*> m_tooltips;

  bool show_exit_popup = false; // Variable de estado para el popup

  bool m_requestSaveScene = false;
  ImDrawList* m_viewportDrawList = nullptr;
  bool m_viewportActive = false;

public:
  bool m_isUsingGizmo = false;
  int selectedActorIndex = -1;

  ImVec2 m_viewportPos = ImVec2(0.0f, 0.0f);
  ImVec2 m_viewportSize = ImVec2(0.0f, 0.0f);
  bool m_viewportHovered = false;
  bool m_viewportFocused = false;
};
