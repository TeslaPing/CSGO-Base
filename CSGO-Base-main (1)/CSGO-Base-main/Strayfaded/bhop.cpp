#include "include.h"

DWORD WINAPI BHopThread(HMODULE hMod)
{	
	LocalPlayer L;
	while (!GetAsyncKeyState(UNINJECT_KB))
	{
		if (L.Exists() && UserSettings.EnableBhop)
		{
			DWORD flag = *(BYTE*)(L.Get() + m_fFlags);
			if (GetAsyncKeyState(VK_SPACE) && flag & (1 << 0))
			{
				L.ForceJump();
			}
		}
	}
	FreeLibraryAndExitThread(hMod, 0);
}