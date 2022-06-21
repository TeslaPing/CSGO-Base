#include "include.h"

inline D3DCOLOR ImColor_D3D(ImColor Input)
{
	return D3DCOLOR_RGBA(
		(int)(Input.Value.x * 255.0f),
		(int)(Input.Value.y * 255.0f),
		(int)(Input.Value.z * 255.0f),
		(int)(Input.Value.w * 255.0f)
	);
}

class USettings
{
public:
	bool EnableBhop = false;

	bool EnableTriggerbot = false;
	int TriggerbotDelay = 0;

	bool EnableRecoilControl = false;
	float RecoilControlAmount = 1.0f;
	
	bool EnableRecoilCrosshair = true;
	bool RecoilCrosshairLine = false;
	bool RecoilCrosshairCircle = false;
	int RecoilCrosshairThickness = 1;
	int RecoilCrosshairLength = 10;
	ImColor RecoilCrosshairColor = { 1.0f, 1.0f, 1.0f, 1.0f };

	bool EnableVisuals = false;
	bool EnableTracers = false;
	bool TraceTeammates = false;
	bool EnableCustomTracerBone = false;
	bool TraceFromFeet = false;
	int TracerBone = 1;
	int TracerThickness = 1;
	ImColor EnemyTracerColor = { 1.0f,1.0f, 1.0f, 1.0f };
	ImColor FriendlyTracerColor = { 1.0f,1.0f, 1.0f, 1.0f };

	bool EnableBoundingBoxes = false;
	float BoundingBoxesWidth = 0.5f;
	int BoundingBoxesThnickness = 1;
	ImColor EnemyBoxColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	ImColor FriendlyBoxColor = { 1.0f, 1.0f, 1.0f, 1.0f };

	bool EnableCustomFOV = false;
	int CustomDesiredFOV = 90;

	bool Global_Antialias = true;

};

