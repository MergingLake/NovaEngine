#include "ImguiInterface.h"
#include "BaseApp.h"
#include <string>

static void DrawVec3Control(const std::string& label, EU::Vector3& values, float resetValue = 0.0f, float columnWidth = 100.0f)
{
  ImGui::PushID(label.c_str());

  ImGui::Columns(2);
  ImGui::SetColumnWidth(0, columnWidth);

  float cursorY = ImGui::GetCursorPosY();
  ImGui::SetCursorPosY(cursorY + ImGui::GetStyle().FramePadding.y);
  ImGui::Text(label.c_str());
  ImGui::NextColumn();
  ImGui::SetCursorPosY(cursorY);

  ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
  ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 4.0f, 0 });

  float lineHeight = ImGui::GetFrameHeight();
  ImVec2 buttonSize = { lineHeight, lineHeight };

  ImVec4 redNormal = ImVec4{ 0.75f, 0.25f, 0.25f, 1.0f };
  ImVec4 redHover = ImVec4{ 0.85f, 0.35f, 0.35f, 1.0f };
  ImVec4 redActive = ImVec4{ 0.65f, 0.15f, 0.15f, 1.0f };

  ImVec4 greenNormal = ImVec4{ 0.25f, 0.65f, 0.35f, 1.0f };
  ImVec4 greenHover = ImVec4{ 0.35f, 0.75f, 0.45f, 1.0f };
  ImVec4 greenActive = ImVec4{ 0.15f, 0.55f, 0.25f, 1.0f };

  ImVec4 blueNormal = ImVec4{ 0.25f, 0.45f, 0.75f, 1.0f };
  ImVec4 blueHover = ImVec4{ 0.35f, 0.55f, 0.85f, 1.0f };
  ImVec4 blueActive = ImVec4{ 0.15f, 0.35f, 0.65f, 1.0f };

  ImGui::PushStyleColor(ImGuiCol_Button, redNormal);
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, redHover);
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, redActive);

  if (ImGui::Button("X", buttonSize)) values.x = resetValue;
  ImGui::PopStyleColor(3);

  ImGui::SameLine();
  float valX = values.x;
  if (ImGui::DragFloat("##X", &valX, 0.1f, 0.0f, 0.0f, "%.2f")) values.x = valX;
  ImGui::PopItemWidth();
  ImGui::SameLine();

  ImGui::PushStyleColor(ImGuiCol_Button, greenNormal);
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, greenHover);
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, greenActive);
  if (ImGui::Button("Y", buttonSize)) values.y = resetValue;
  ImGui::PopStyleColor(3);

  ImGui::SameLine();
  float valY = values.y;
  if (ImGui::DragFloat("##Y", &valY, 0.1f, 0.0f, 0.0f, "%.2f")) values.y = valY;
  ImGui::PopItemWidth();
  ImGui::SameLine();

  ImGui::PushStyleColor(ImGuiCol_Button, blueNormal);
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, blueHover);
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, blueActive);
  if (ImGui::Button("Z", buttonSize)) values.z = resetValue;
  ImGui::PopStyleColor(3);

  ImGui::SameLine();
  float valZ = values.z;
  if (ImGui::DragFloat("##Z", &valZ, 0.1f, 0.0f, 0.0f, "%.2f")) values.z = valZ;
  ImGui::PopItemWidth();

  ImGui::PopStyleVar();
  ImGui::Columns(1);
  ImGui::PopID();
}

ImguiInterface::ImguiInterface() {}
ImguiInterface::~ImguiInterface() {}

void ImguiInterface::init(void* window, ID3D11Device* device, ID3D11DeviceContext* deviceContext) {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;

  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

  ImFontConfig font_cfg;
  font_cfg.OversampleH = 3;
  font_cfg.OversampleV = 3;


  io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\segoeui.ttf", 15.5f, &font_cfg);

  SetModernDarkStyle();

  ImGui_ImplWin32_Init(window);
  ImGui_ImplDX11_Init(device, deviceContext);
}

void ImguiInterface::update(BaseApp* application) {
  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();
  ImGui::NewFrame();

  SetupDockspace();

	DrawMainMenu();

  if (application) {
    DrawHierarchyPanel(application);
    DrawInspectorPanel();
  }
}

void ImguiInterface::render() {
  ImGui::Render();
  ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

  ImGuiIO& io = ImGui::GetIO();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
  }
}

void ImguiInterface::destroy() {
  ImGui_ImplDX11_Shutdown();
  ImGui_ImplWin32_Shutdown();
  ImGui::DestroyContext();
}

void ImguiInterface::SetupDockspace() {
  ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
  window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
  window_flags |= ImGuiWindowFlags_NoBackground;

  const ImGuiViewport* viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->WorkPos);
  ImGui::SetNextWindowSize(viewport->WorkSize);
  ImGui::SetNextWindowViewport(viewport->ID);

  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

  ImGui::Begin("DockSpace Principal", &m_dockspaceOpen, window_flags);

  ImGui::PopStyleVar(3);

  ImGuiIO& io = ImGui::GetIO();
  if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), m_dockspaceFlags | ImGuiDockNodeFlags_PassthruCentralNode);
  }
  ImGui::End();
}

void ImguiInterface::DrawHierarchyPanel(BaseApp* application) {
	if (!m_showHierarchy) return;
  ImGui::Begin("Hierarchy", &m_showHierarchy);

  if (application->m_actors.empty()) {
    ImGui::TextDisabled("The m_actors list is empty.");
    ImGui::End();
    return;
  }

  int index = 0;
  for (auto& sharedActor : application->m_actors) {
    Actor* rawPtr = sharedActor.get();

    ImGui::PushID(index);

    bool isSelected = (m_selectedActor == rawPtr);

    std::string name = rawPtr->getName();
    if (name.empty()) name = "Actor " + std::to_string(index);

    if (ImGui::Selectable(name.c_str(), isSelected)) {
      m_selectedActor = rawPtr;
    }

    if (m_selectedActor == nullptr && index == 0) {
      m_selectedActor = rawPtr;
    }

    if (isSelected) {
      ImGui::SetItemDefaultFocus();
    }

    ImGui::PopID();
    index++;
  }

  ImGui::End();
}

void ImguiInterface::DrawInspectorPanel() {
  if (!m_showInspector) return;

  ImGui::Begin("Inspector", &m_showInspector);

  if (m_selectedActor) {
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));
    std::string name = m_selectedActor->getName();
    strncpy_s(buffer, name.c_str(), sizeof(buffer));

    if (ImGui::InputText("Actor", buffer, sizeof(buffer))) {
      m_selectedActor->setName(std::string(buffer));
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    static int currentTag = 0;
    const char* tagList[] = { "Untagged", "Respawn", "Finish", "Player", "Enemy" };

    static int currentLayer = 0;
    const char* layerList[] = { "Default", "TransparentFX", "Ignore Raycast", "Water", "UI" };

    ImGui::Columns(2, "TagLayerCols", false);

    ImGui::SetNextItemWidth(ImGui::GetColumnWidth() - 40.0f);
    ImGui::Combo("Tag", &currentTag, tagList, IM_ARRAYSIZE(tagList));

    ImGui::NextColumn();

    ImGui::SetNextItemWidth(ImGui::GetColumnWidth() - 48.0f);
    ImGui::Combo("Layer", &currentLayer, layerList, IM_ARRAYSIZE(layerList));

    ImGui::Columns(1);

    ImGui::Spacing();
    ImGui::Separator();

    auto transformComp = m_selectedActor->getComponent<Transform>();
    if (transformComp) {
      if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {

        EU::Vector3 pos = transformComp->getPosition();
        EU::Vector3 rot = transformComp->getRotation();
        EU::Vector3 scale = transformComp->getScale();

        DrawVec3Control("Position", pos, 0.0f);
        DrawVec3Control("Rotation", rot, 0.0f);
        DrawVec3Control("Scale", scale, 1.0f);

        transformComp->setPosition(pos);
        transformComp->setRotation(rot);
        transformComp->setScale(scale);
      }
    }
  }
  else {
    ImGui::TextDisabled("Select an actor from Hierarchy.");
  }

  ImGui::End();
}

void ImguiInterface::DrawMainMenu() {
  if (ImGui::BeginMainMenuBar()) {

    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("Exit")) {
      }
      ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Window")) {
      ImGui::MenuItem("Hierarchy", nullptr, &m_showHierarchy);
      ImGui::MenuItem("Inspector", nullptr, &m_showInspector);

      ImGui::Separator();

      if (ImGui::MenuItem("Reset Layout (Factory Settings)")) {

        m_showHierarchy = true;
        m_showInspector = true;

        ImGui::ClearIniSettings();
      }

      ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
  }
}

void ImguiInterface::SetDarkStyle() {
  ImGui::StyleColorsDark();

  ImGuiStyle& style = ImGui::GetStyle();

  style.WindowRounding = 6.0f;
  style.ChildRounding = 6.0f;
  style.FrameRounding = 6.0f;
  style.PopupRounding = 6.0f;
  style.ScrollbarRounding = 6.0f;
  style.GrabRounding = 6.0f;
  style.TabRounding = 6.0f;

  ImVec4* colors = style.Colors;

  // BACKGROUNDS
  colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.105f, 0.11f, 1.0f);
  colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);

  // HEADERS
  colors[ImGuiCol_Header] = ImVec4(0.2f, 0.205f, 0.21f, 1.0f);
  colors[ImGuiCol_HeaderHovered] = ImVec4(0.3f, 0.305f, 0.31f, 1.0f);
  colors[ImGuiCol_HeaderActive] = ImVec4(0.15f, 0.1505f, 0.151f, 1.0f);

  // BUTTONS
  colors[ImGuiCol_Button] = ImVec4(0.2f, 0.205f, 0.21f, 1.0f);
  colors[ImGuiCol_ButtonHovered] = ImVec4(0.3f, 0.305f, 0.31f, 1.0f);
  colors[ImGuiCol_ButtonActive] = ImVec4(0.15f, 0.1505f, 0.151f, 1.0f);

  // INPUT BOX
  colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.16f, 0.17f, 1.0f);
  colors[ImGuiCol_FrameBgHovered] = ImVec4(0.2f, 0.2f, 0.22f, 1.0f);
  colors[ImGuiCol_FrameBgActive] = ImVec4(0.16f, 0.16f, 0.17f, 1.0f);

  // TABS DOCKING
  colors[ImGuiCol_Tab] = ImVec4(0.15f, 0.1505f, 0.151f, 1.0f);
  colors[ImGuiCol_TabHovered] = ImVec4(0.38f, 0.3805f, 0.381f, 1.0f);
  colors[ImGuiCol_TabActive] = ImVec4(0.28f, 0.2805f, 0.281f, 1.0f);

  // WINDOWS TITLES
  colors[ImGuiCol_TitleBg] = ImVec4(0.15f, 0.1505f, 0.151f, 1.0f);
  colors[ImGuiCol_TitleBgActive] = ImVec4(0.15f, 0.1505f, 0.151f, 1.0f);
  colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.15f, 0.1505f, 0.151f, 1.0f);
}

void ImguiInterface::SetModernDarkStyle() {
  ImGuiStyle& style = ImGui::GetStyle();

  // FORMS
  style.WindowRounding = 8.0f;
  style.ChildRounding = 6.0f;
  style.FrameRounding = 5.0f;
  style.PopupRounding = 6.0f;
  style.ScrollbarRounding = 9.0f;
  style.GrabRounding = 5.0f;
  style.TabRounding = 6.0f;

  style.FramePadding = ImVec2(5.0f, 5.0f);
  style.ItemSpacing = ImVec2(8.0f, 6.0f);

  // COLORS
  ImVec4* colors = style.Colors;

  // BACKGROUND
  colors[ImGuiCol_WindowBg] = ImVec4(0.135f, 0.135f, 0.135f, 1.00f);
  colors[ImGuiCol_ChildBg] = ImVec4(0.135f, 0.135f, 0.135f, 1.00f);
  colors[ImGuiCol_PopupBg] = ImVec4(0.13f, 0.13f, 0.13f, 0.94f);

  // BORDERS
  colors[ImGuiCol_Border] = ImVec4(0.30f, 0.30f, 0.30f, 0.50f);
  colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

  // HEADERS
  colors[ImGuiCol_Header] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
  colors[ImGuiCol_HeaderHovered] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
  colors[ImGuiCol_HeaderActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);

  // INPUTS
  colors[ImGuiCol_FrameBg] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
  colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
  colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);

  // BUTTONS
  colors[ImGuiCol_Button] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
  colors[ImGuiCol_ButtonHovered] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
  colors[ImGuiCol_ButtonActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);

  // TABS
  colors[ImGuiCol_Tab] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
  colors[ImGuiCol_TabHovered] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
  colors[ImGuiCol_TabActive] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
  colors[ImGuiCol_TabUnfocused] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
  colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);

  // Title Bar
  colors[ImGuiCol_TitleBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
  colors[ImGuiCol_TitleBgActive] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
  colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);

  // TEXT
  colors[ImGuiCol_Text] = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
  colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);

  // SCROLLBAR
  colors[ImGuiCol_ScrollbarBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
  colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.45f, 0.45f, 0.45f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);

  colors[ImGuiCol_Separator] = ImVec4(0.30f, 0.30f, 0.30f, 0.50f);
}