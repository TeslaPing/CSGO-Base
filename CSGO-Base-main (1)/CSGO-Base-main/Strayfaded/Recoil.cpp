#include "include.h"

DWORD WINAPI RecoilThread(HMODULE hMod)
{
	LocalPlayer L;
	DWORD localPlayer = L.Get();
	Vector3 OldPunch{ 0, 0, 0 };

	while (!GetAsyncKeyState(UNINJECT_KB))
	{
		if (UserSettings.EnableRecoilControl)
		{
			if (localPlayer)
			{
				int* ShotsFired = (int*)(localPlayer + m_iShotsFired);
				Vector3* RecoilPuch = (Vector3*)(localPlayer + m_aimPunchAngle);
				Vector3 PunchAngle = *RecoilPuch * (UserSettings.RecoilControlAmount * 2);

				if (*ShotsFired > 1 && GetAsyncKeyState(VK_LBUTTON))
				{
					Vector3 Angle = L.GetViewAngles() + OldPunch - PunchAngle;
					L.SetViewAngles(Angle);
				}
				OldPunch = PunchAngle;
			}
			else
			{
				localPlayer = L.Get();
			}
		}
		if (UserSettings.EnableRecoilCrosshair)
		{
			if (localPlayer)
			{
				Vector3 angle = *(Vector3*)(localPlayer + m_aimPunchAngle);
				if (UserSettings.EnableCustomFOV)
				{
					int FOV = UserSettings.CustomDesiredFOV;
					RecoilCrosshairX = windowWidth / 2 - (windowWidth / FOV * angle.y);
					RecoilCrosshairY = windowHeight / 2 + (windowHeight / FOV * angle.x);
				}
				else
				{
					int FOV = 90;
					RecoilCrosshairX = windowWidth / 2 - (windowWidth / FOV * angle.y);
					RecoilCrosshairY = windowHeight / 2 + (windowHeight / FOV * angle.x);
				}
			}
			else
			{
				localPlayer = L.Get();
			}
		}
	}	

	FreeLibraryAndExitThread(hMod, 0);
}