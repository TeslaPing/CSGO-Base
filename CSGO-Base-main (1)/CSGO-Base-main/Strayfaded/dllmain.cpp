#include "include.h"


void* d3d9Device[119];
BYTE EndSceneBytes[7]{ 0 };
tEndScene oEndScene = nullptr;
LPDIRECT3DDEVICE9 pDevice = nullptr;
WNDPROC oWndProc;

Engine E;
LocalPlayer PlayerController;
Entity EntityController;

void InitImGui(LPDIRECT3DDEVICE9 pDevice)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX9_Init(pDevice);
}

bool init = false;
bool ShowMenu = true;
HRESULT APIENTRY hkEndScene(LPDIRECT3DDEVICE9 o_pDevice)
{   
    if (GetAsyncKeyState(MENU_KB) & 1)
    {
        ShowMenu = !ShowMenu;

    }
    if (!pDevice)
    {
        pDevice = o_pDevice;
    }
    if (!init)
    {
        DXDEVICE = pDevice;
        InitImGui(pDevice);
        init = true;
    }

    if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Insert)))
        ShowMenu = !ShowMenu;

    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    
    ImGui::Begin("Tesla Cheat", &ShowMenu);
    ImGui::Checkbox("Bhop", &UserSettings.EnableBhop);
    ImGui::Checkbox("Triggerbot", &UserSettings.EnableTriggerbot);
    ImGui::Separator();
    ImGui::Checkbox("Recoil Control", &UserSettings.EnableRecoilControl);
    if (UserSettings.EnableRecoilControl)
    {
        ImGui::SliderFloat("Amount", &UserSettings.RecoilControlAmount, 0.0f, 1.0f);
    }
    ImGui::Separator();

    ImGui::Checkbox("Enable Recoil Crosshair", &UserSettings.EnableRecoilCrosshair);
    if (UserSettings.EnableRecoilCrosshair)
    {
        ImGui::SliderInt("Crosshair Thickness", &UserSettings.RecoilCrosshairThickness, 1, 10);
        ImGui::Checkbox("Draw Circle", &UserSettings.RecoilCrosshairCircle);
        ImGui::Checkbox("Draw Trace", &UserSettings.RecoilCrosshairLine);
        if (!UserSettings.RecoilCrosshairLine)
        {
            ImGui::SliderInt("Crosshair Lenght", &UserSettings.RecoilCrosshairLength, 1, 50);
        }
        ImGui::ColorEdit4("Crosshair Color", (float*)(&UserSettings.RecoilCrosshairColor));
    }

    ImGui::Separator();

    ImGui::Checkbox("Enable Visuals", &UserSettings.EnableVisuals);
    if (UserSettings.EnableVisuals)
    {
        ImGui::Checkbox("Draw Tracers", &UserSettings.EnableTracers);
        if (UserSettings.EnableTracers)
        {
            ImGui::Checkbox("Friendly Tracer", &UserSettings.TraceTeammates);
            ImGui::ColorEdit4("Enemy Color", (float*)(&UserSettings.EnemyTracerColor));
                if (&UserSettings.TraceTeammates)
                {
                    ImGui::ColorEdit4("Team Color", (float*)(&UserSettings.FriendlyTracerColor));
                }
            ImGui::SliderInt("Thickness", &UserSettings.TracerThickness, 1, 10);
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Checkbox("Use Custom Bone", &UserSettings.EnableCustomTracerBone);
            if (UserSettings.EnableCustomTracerBone)
            {
                ImGui::SliderInt("Tracer Bone", &UserSettings.TracerBone, 0, 100);
            }
            else
            {
                if (ImGui::Button("Center"))
                {
                    UserSettings.TracerBone = 0;
                }
                if (ImGui::Button("Head"))
                {
                    UserSettings.TracerBone = 8;
                }
                if (ImGui::Button("Buttom"))
                {
                    UserSettings.TracerBone = 1;
                }
            }
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Text("Trace Starting Point:");
            if (ImGui::Button("Bottom Center"))
            {
                UserSettings.TraceFromFeet = false;
            }
            if (ImGui::Button("Player Feet"))
            {
                UserSettings.TraceFromFeet = true;
            }

        }
        ImGui::Separator();
        ImGui::Checkbox("Draw Boxes", &UserSettings.EnableBoundingBoxes);
        if (UserSettings.EnableBoundingBoxes)
        {
            ImGui::SliderInt("Thickness", &UserSettings.BoundingBoxesThnickness, 1, 10);
            ImGui::SliderFloat("Box Width", &UserSettings.BoundingBoxesWidth, 0.01f, 1.0f);
            ImGui::ColorEdit4("Enemy Color", (float*)(&UserSettings.EnemyBoxColor));
            ImGui::ColorEdit4("Friendly Color", (float*)(&UserSettings.FriendlyBoxColor));
        }
    }

    ImGui::Checkbox("Antialiasing", & UserSettings.Global_Antialias);

    ImGui::End();

    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

    windowWidth = GetSystemMetrics(SM_CXSCREEN);
    windowHeight = GetSystemMetrics(SM_CYSCREEN);
    if (UserSettings.EnableRecoilCrosshair)
    {
        int len = UserSettings.RecoilCrosshairLength;
        int thickness = UserSettings.RecoilCrosshairThickness;
        if (UserSettings.RecoilCrosshairCircle)
        {
            DrawCircle(
                RecoilCrosshairX,
                RecoilCrosshairY,
                (int)(len / 2),
                8,
                thickness,
                UserSettings.Global_Antialias,
                ImColor_D3D(UserSettings.RecoilCrosshairColor)
            );
        }
        if (UserSettings.RecoilCrosshairLine)
        {
            DrawLine(
                RecoilCrosshairX,
                RecoilCrosshairY,
                windowWidth / 2,
                windowHeight / 2,
                thickness,
                UserSettings.Global_Antialias,
                ImColor_D3D(UserSettings.RecoilCrosshairColor)

            );
        }
        else
        {
            DrawLine(
                RecoilCrosshairX - len,
                RecoilCrosshairY,
                RecoilCrosshairX + len,
                RecoilCrosshairY,
                thickness,
                UserSettings.Global_Antialias,
                ImColor_D3D(UserSettings.RecoilCrosshairColor)
            );
            DrawLine(
                RecoilCrosshairX,
                RecoilCrosshairY - len,
                RecoilCrosshairX,
                RecoilCrosshairY + len,
                thickness,
                UserSettings.Global_Antialias,
                ImColor_D3D(UserSettings.RecoilCrosshairColor)
            );

        }
    }

    if (UserSettings.EnableVisuals)
    {
        if (UserSettings.EnableTracers || UserSettings.EnableBoundingBoxes)
        {
            if (PlayerController.Exists())
            {
                Vector2 StartLocation = { windowWidth / 2, windowHeight };
                if (UserSettings.TraceFromFeet)
                {
                    float Matrix[16];
                    memcpy(&Matrix, (PBYTE*)(Global_GameModule + dwViewMatrix), sizeof(Matrix));
                    WorldToScreen(PlayerController.GetLocation(), StartLocation, Matrix);
                }
                Vector2 EndLocation;
                for (int i = 1; i < 32; i++)
                {
                    uintptr_t Entity = *(uintptr_t*)(Global_GameModule + dwEntityList + (i * 0x10));
                    if (Entity != NULL)
                    {
                        int EntityHealth = EntityController.GetHealth(Entity);
                        if (EntityHealth > 0 && EntityHealth < 101)
                        {
                            EndLocation = EntityController.GetBonePositionScreen(Entity, UserSettings.TracerBone);
                            Vector3 BaseLocation = EntityController.GetBonePosition(Entity, 1);
                            Vector3 HeadLocation = EntityController.GetBonePosition(Entity, 8);
                            HeadLocation.z += 15;

                            Vector2 Head;
                            Vector2 Base;
                            float Matrix[16];
                            memcpy(&Matrix, (PBYTE*)(Global_GameModule + dwViewMatrix), sizeof(Matrix));
                            WorldToScreen(HeadLocation, Head, Matrix);
                            WorldToScreen(BaseLocation, Base, Matrix);

                            if (EndLocation.x > 0 && EndLocation.y > 0)
                            {
                                D3DCOLOR TraceColor;
                                D3DCOLOR BoxColor;

                                int Height = Head.Distance(Base);

                                int PlayerTeam = PlayerController.GetTeam();
                                int EntityTeam = EntityController.GetTeam(Entity);

                                if (PlayerTeam != EntityTeam)
                                {
                                    TraceColor = ImColor_D3D(UserSettings.EnemyTracerColor);
                                    BoxColor = ImColor_D3D(UserSettings.EnemyBoxColor);
                                    {
                                        DrawLine(
                                            StartLocation.x,
                                            StartLocation.y,
                                            EndLocation.x,
                                            EndLocation.y,
                                            UserSettings.TracerThickness,
                                            UserSettings.Global_Antialias,
                                            TraceColor
                                        );
                                    }
                                    if (UserSettings.EnableBoundingBoxes)
                                    {
                                        DrawBoundingBox(
                                            Base.x,
                                            Base.y,
                                            Height* UserSettings.BoundingBoxesWidth,
                                            Height,
                                            UserSettings.BoundingBoxesThnickness,
                                            UserSettings.Global_Antialias,
                                            BoxColor
                                        );
                                    }
                                }
                                else
                                {
                                    TraceColor = ImColor_D3D(UserSettings.FriendlyTracerColor);
                                    BoxColor = ImColor_D3D(UserSettings.FriendlyBoxColor);
                                    {
                                        DrawLine(
                                            StartLocation.x,
                                            StartLocation.y,
                                            EndLocation.x,
                                            EndLocation.y,
                                            UserSettings.TracerThickness,
                                            UserSettings.Global_Antialias,
                                            TraceColor
                                        );
                                    }
                                    if (UserSettings.EnableBoundingBoxes)
                                    {
                                        DrawBoundingBox(
                                            Base.x,
                                            Base.y,
                                            Height * UserSettings.BoundingBoxesWidth,
                                            Height,
                                            UserSettings.BoundingBoxesThnickness,
                                            UserSettings.Global_Antialias,
                                            BoxColor
                                        );
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return oEndScene(pDevice);
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;
    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}
BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
    DWORD wndProcId;
    GetWindowThreadProcessId(handle, &wndProcId);

    if (GetCurrentProcessId() != wndProcId)
        return TRUE;
    window = handle;
    return FALSE;
}
HWND GetProcess()
{
    window = NULL;
    EnumWindows(EnumWindowsCallback, NULL);
    return window;
}

DWORD WINAPI MainThread(HMODULE hMod)
{
    // Hook
    if (GetD3D9Device(d3d9Device, sizeof(d3d9Device)))
    {
        memcpy(EndSceneBytes, (char*)d3d9Device[42], 7);
        oEndScene = (tEndScene)TrampHook((char*)d3d9Device[42], (char*)hkEndScene, 7);
    }
    window = GetProcess();
    oWndProc = (WNDPROC)SetWindowLongPtr(window, -4, (LONG_PTR)WndProc);

    // Loop
    while (!GetAsyncKeyState(UNINJECT_KB))
    {
        Sleep(500); // Always sleep when you're in a "while" loop because you get 20% of cpu usage if you dont
    }

    // Unhook
    Patch((BYTE*)d3d9Device[42], EndSceneBytes, 7);
    FreeLibraryAndExitThread(hMod, 0);
}

BOOL __stdcall StartThread(HMODULE hModule, LPTHREAD_START_ROUTINE StartAddress)
{
    return CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)StartAddress, hModule, 0, 0));
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        E.Init();
        StartThread(hModule, (LPTHREAD_START_ROUTINE)MainThread);
        StartThread(hModule, (LPTHREAD_START_ROUTINE)BHopThread);
        StartThread(hModule, (LPTHREAD_START_ROUTINE)TriggerbotThread);
        StartThread(hModule, (LPTHREAD_START_ROUTINE)RecoilThread);
        
    default:
        break;
    }
    return TRUE;
}
