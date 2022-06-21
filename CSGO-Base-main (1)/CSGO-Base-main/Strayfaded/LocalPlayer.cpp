#include "include.h"


DWORD LocalPlayer::Get()
{
	return *(DWORD*)(Global_GameModule + dwLocalPlayer);
}
int LocalPlayer::GetHealth()
{
	DWORD Player = Get();
	if (Player)
		return *(int*)(Player + m_iHealth);
	return -1;
}
int LocalPlayer::GetTeam()
{
	DWORD Player = Get();
	if (Player)
		return *(int*)(Player + m_iTeamNum);
	return -1;
}
int LocalPlayer::CrosshairID()
{
	DWORD Player = Get();
	if (Player)
		return *(int*)(Player + m_iCrosshairId);
	return -1;
}
bool LocalPlayer::Exists()
{
	if (*(DWORD*)(Global_GameModule + dwLocalPlayer))
	{
		return true;
	}
	return false;
}
void LocalPlayer::ForceJump()
{
	*(DWORD*)(Global_GameModule + dwForceJump) = 6;
}
void LocalPlayer::ForceAttack()
{
	*(int*)(Global_GameModule + dwForceAttack) = 5;
}
void LocalPlayer::StopAttack()
{
	*(int*)(Global_GameModule + dwForceAttack) = 4;
}
void LocalPlayer::SetViewAngles(Vector3 Input)
{
	Input.Normalize();
	Vector3* ViewAngles = (Vector3*)(*(DWORD*)(Global_EngineModule + dwClientState) + dwClientState_ViewAngles);
	*ViewAngles = Input;

}
Vector3 LocalPlayer::GetViewAngles()
{
	Vector3* ViewAngles = (Vector3*)(*(DWORD*)(Global_EngineModule + dwClientState) + dwClientState_ViewAngles);
	return *ViewAngles;
}

Vector3 LocalPlayer::GetLocation()
{
	DWORD Plr = Get();
	if (Plr)
		return *(Vector3*)(Plr + m_vecOrigin);
	return { 0, 0, 0 };
}
Vector3 LocalPlayer::GetBonePosition(int Bone)
{
	DWORD Plr = Get();
	if (Plr)
	{
		uintptr_t BoneMatrixBase = *(uintptr_t*)(Plr + m_dwBoneMatrix);
		BoneMatrix BoneMat = *(BoneMatrix*)(BoneMatrixBase + sizeof(Bone) * Bone);
		Vector3 Location = { BoneMat.x, BoneMat.y, BoneMat.z };
		return Location;
	}
	return{ 0,0,0 };
}
Vector2 LocalPlayer::GetBonePositionScreen(int Bone)
{
	DWORD Plr = Get();
	if (Plr)
	{
		uintptr_t BoneMatrixBase = *(uintptr_t*)(Plr + m_dwBoneMatrix);
		BoneMatrix BoneMat = *(BoneMatrix*)(BoneMatrixBase + sizeof(Bone) * Bone);
		Vector3 Location = { BoneMat.x, BoneMat.y, BoneMat.z };

		float Matrix[16];
		Vector2 Out;
		memcpy(&Matrix, (PBYTE*)(Global_GameModule + dwViewMatrix), sizeof(Matrix));
		if (WorldToScreen(Location, Out, Matrix))
		{
			return Out;
		}
	}
	return{ 0,0};
}
