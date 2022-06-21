#pragma once
#include <Windows.h>

// Extra Config
#define MENU_KB VK_TAB
#define UNINJECT_KB VK_DELETE

// DirectX
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

// Imgui
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"

#include "Vector.h"

// Settings
#include "Settings.h"
USettings UserSettings;


// Functions
#include "WorldToScreen.h"

// Hook/Drawing
#include "DirectX.h"
#include "Hook.h"
#include "Drawing.h"

// Offsets
#include "csgo.hpp"
using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

// Global Varibals
int RecoilCrosshairX = windowWidth / 2;
int RecoilCrosshairY = windowWidth / 2;
LPDIRECT3DDEVICE9 DXDEVICE;
DWORD Global_GameModule;
DWORD Global_EngineModule;



// Classes
#include "Engine.h"
#include "localPlayer.h"
#include "Entity.h"

// Modules
#include "bhop.h"
#include "Triggerbot.h"
#include "Recoil.h"
