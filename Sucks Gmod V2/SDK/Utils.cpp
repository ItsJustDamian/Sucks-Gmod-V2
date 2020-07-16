#include "Utils.h"

# define M_PI           3.14159265358979323846

bool Utils::file_exists(char * file)
{
	struct stat buffer;
	return (stat(file, &buffer) == 0);
}

bool Utils::ScreenTransform(QAngle & in, QAngle & out)
{
	const VMatrix& w2sMatrix = Interfaces->EngineClient->GetViewMatrix(); //*(CUST_VMatrix*)(G::EngineModule + 0x003FCD6C);

	out.x = w2sMatrix.m[0][0] * in.x + w2sMatrix.m[0][1] * in.y + w2sMatrix.m[0][2] * in.z + w2sMatrix.m[0][3];
	out.y = w2sMatrix.m[1][0] * in.x + w2sMatrix.m[1][1] * in.y + w2sMatrix.m[1][2] * in.z + w2sMatrix.m[1][3];
	out.z = 0.0f;

	float w = w2sMatrix.m[3][0] * in.x + w2sMatrix.m[3][1] * in.y + w2sMatrix.m[3][2] * in.z + w2sMatrix.m[3][3];

	if (w < 0.001f) {
		out.x *= 100000;
		out.y *= 100000;
		return false;
	}

	out.x /= w;
	out.y /= w;

	return true;
}

bool Utils::WorldToScreen(QAngle & in, QAngle & out)
{
	int width, height;
	Interfaces->EngineClient->GetScreenSize(width, height);

	if (ScreenTransform(in, out)) {
		out.x = (width / 2.0f) + (out.x * width) / 2.0f;
		out.y = (height / 2.0f) - (out.y * height) / 2.0f;

		return true;
	}
	return false;
}

float Utils::Distance(QAngle pos1, QAngle pos2)
{
	return sqrt(
		pow(pos2.x - pos1.x, 2.f) +
		pow(pos2.y - pos1.y, 2.f) +
		pow(pos2.z - pos1.z, 2.f)
	);
}

float Utils::Distance2D(QAngle pos1, QAngle pos2)
{
	return sqrt(
		pow(pos2.x - pos1.x, 2.f) +
		pow(pos2.y - pos1.y, 2.f)
	);
}

void* Utils::GetLocalPlayer()
{
	return Interfaces->ClientEntityList->GetClientEntity(Interfaces->EngineClient->GetLocalPlayer());
}

void Utils::VectorAngles(const QAngle & forward, QAngle & angles)
{
	if (forward.y == 0 && forward.x == 0) {
		angles.x = forward.z > 0.f ? 270.f : 90.f;
		angles.y = 0;
	}

	else {
		angles.x = (atan2(-forward.z, forward.Length2D()) * 180 / M_PI);
		if (angles.x < 0)
			angles.x += 360;

		angles.y = (atan2(forward.y, forward.x) * 180 / M_PI);
		if (angles.y < 0)
			angles.y += 360;
	}

	angles.z = 0;
}

QAngle Utils::CalcAngle(QAngle src, QAngle dst)
{
	QAngle angles;
	QAngle delta = dst - src;

	VectorAngles(delta, angles);

	angles.Normalize();

	return angles;
}