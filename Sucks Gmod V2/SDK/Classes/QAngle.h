/*===========================================*/
/*		   Created by I SUCK AT LIFE	   	 */
/*			  PLEASE DONT STEAL :)		 	 */
/*===========================================*/
#pragma once

class QAngle
{
public:
	float x;
	float y;
	float z;

	QAngle() { x = 0; y = 0; z = 0; }
	QAngle(float ix, float iy, float iz) { x = ix; y = iy; z = iz; }

	void Clamp()
	{
		if (x > 89.f && x <= 180.f)
			x = 89.f;
		if (x > 180.0f)
			x = x - 360.0f;
		if (x < -89.0f)
			x = -89.0f;
		if (y > 180.0f)
			y = y - 360.0f;
		if (y < -180.0f)
			y = y + 360.0f;
	}

	auto Clamped() {
		QAngle tmp = *this;
		tmp.Clamp();
		return tmp;
	}

	void Normalize()
	{
		if (x > 180)
			x -= 360.0f;
		if (x < 180)
			x += 360.0f;
		if (y > 180)
			y -= 360.0f;
		if (y < 180)
			y += 360.0f;
	}

	QAngle operator-(QAngle angle)
	{
		return QAngle(x - angle.x, y - angle.y, z - angle.z);
	}

	QAngle operator+(QAngle angle)
	{
		return QAngle(x + angle.x, y + angle.y, z + angle.z);
	}

	QAngle operator*(const float &f)
	{
		return QAngle(x * f, y * f, z * f);
	}

	QAngle operator/(QAngle angle)
	{
		return QAngle(x / angle.x, y / angle.y, z / angle.z);
	}

	QAngle operator/(const float &f)
	{
		return QAngle(x / f, y / f, z / f);
	}

	bool IsNan()
	{
		if (isnan(x) || isnan(y) || isnan(z))
			return true;

		return false;
	}

	auto LengthSqr() const {
		return (x * x + y * y + z * z);
	}

	auto Length2DSqr() const {
		return (x * x + y * y);
	}

	auto Length() const {
		return sqrt(LengthSqr());
	}

	auto Length2D() const {
		return sqrt(Length2DSqr());
	}
};