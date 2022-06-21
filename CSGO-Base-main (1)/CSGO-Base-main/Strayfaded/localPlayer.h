#include "include.h"

class LocalPlayer
{
public:
	DWORD Get();

	bool Exists();

	int GetHealth();
	int GetTeam();

	int CrosshairID();

	void ForceJump();
	void ForceAttack();
	void StopAttack();

	void SetViewAngles(Vector3 Input);
	Vector3 GetViewAngles();

	Vector3 GetLocation();
	Vector3 GetBonePosition(int Bone);
	Vector2 GetBonePositionScreen(int Bone);


};