#pragma once
// Libraries STD
#include <string>
#include <sstream>
#include <vector>
#include <windows.h>
#include <xnamath.h>
#include <thread>
#include <memory>
#include <unordered_map>
#include <type_traits>
#include <array>
#include <algorithm>
#include <cmath>

// Libraries DirectX
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include "Resource.h"
#include "resource.h"

// Third Party Libraries
#include "EngineUtilities/Vectors/Vector2.h"
#include "EngineUtilities/Vectors/Vector3.h"
#include "EngineUtilities\Memory\TSharedPointer.h"
#include "EngineUtilities\Memory\TWeakPointer.h"
#include "EngineUtilities\Memory\TStaticPtr.h"
#include "EngineUtilities\Memory\TUniquePtr.h"

#include "imgui.h"
#include <imgui_internal.h>
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include <sol/sol.hpp>

// MACROS
#define SAFE_RELEASE(x) if(x != nullptr) x->Release(); x = nullptr;

#define MESSAGE( classObj, method, state )   \
{                                            \
   std::wostringstream os_;                  \
   os_ << classObj << "::" << method << " : " << "[CREATION OF RESOURCE " << ": " << state << "] \n"; \
   OutputDebugStringW( os_.str().c_str() );  \
}

#define ERROR(classObj, method, errorMSG)                     \
{                                                             \
    try {                                                     \
        std::wostringstream os_;                              \
        os_ << L"ERROR : " << classObj << L"::" << method     \
            << L" : " << errorMSG << L"\n";                   \
        OutputDebugStringW(os_.str().c_str());                \
    } catch (...) {                                           \
        OutputDebugStringW(L"Failed to log error message.\n");\
    }                                                         \
}

//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
struct SimpleVertex
{
  EU::Vector3 Position;
  EU::Vector3 Normal;
  EU::Vector3 Tangent;
  EU::Vector3 Bitangent;
  EU::Vector2 TextureCoordinate;
};

struct
  SkyboxVertex {
  float x, y, z;
};

struct CBNeverChanges
{
  XMMATRIX mView;
};

struct CBSkybox
{
  XMMATRIX mviewProj;
};

struct CBChangeOnResize
{
  XMMATRIX mProjection;
};

// Constant buffer used in the vertex and pixel shaders.  Align to
// 16?bytes as required by Direct3D constant buffers.
struct CBMain
{
  //XMFLOAT4X4 World;
  XMFLOAT4X4 View;
  XMFLOAT4X4 Projection;
  EU::Vector3 CameraPos;
  float pad0;
  EU::Vector3 LightDir;
  float pad1;
  EU::Vector3 LightColor;
  float pad2;
};

struct CBChangesEveryFrame
{
  XMMATRIX mWorld;
  XMFLOAT4 vMeshColor;
};

struct EngineStats {
  float fps = 0.0f;
  float frameTime = 0.0f;
  int drawCalls = 0;
};
// Declaramos que existe una variable global llamada g_Stats
extern EngineStats g_Stats;

enum ExtensionType {
  DDS = 0,
  PNG = 1,
  JPG = 2
};

enum ShaderType {
  VERTEX_SHADER = 0,
  PIXEL_SHADER = 1
};

/**
 * @enum ComponentType
 * @brief Tipos de componentes disponibles en el juego.
 */
enum
  ComponentType {
  NONE = 0,     ///< Tipo de componente no especificado.
  TRANSFORM = 1,///< Componente de transformación.
  MESH = 2,     ///< Componente de malla.
  MATERIAL = 3,  ///< Componente de material.
  HIERARCHY = 4, ///< Componente de jerarquía.
  SCRIPT = 5,    ///< Componente de lógica/comportamiento.
  RIGIDBODY = 6,     ///< Componente de simulación física
  BOX_COLLIDER = 7   ///< Componente de colisión
};

enum class EngineState {
  EDITOR = 0,
  PLAY = 1,
  PAUSED = 2
};