#include "meth.h"
inline float meth::DotProduct(const CVector& a, const CVector& b) { return(a.x * b.x + a.y * b.y); }
void meth::Norm(CVector& angles)
{
	int i;

	for (i = 0; i < 3; i++)
	{
		switch (i)
		{
		case 0:
			if (angles.x > 180.0)
			{
				angles.x -= 360.0;
			}
			else if (angles.x < -180.0)
			{
				angles.x += 360.0;
			}
			break;
		case 1:
			if (angles.y > 180.0)
			{
				angles.y -= 360.0;
			}
			else if (angles.y < -180.0)
			{
				angles.y += 360.0;
			}
			break;
		case 2:
			if (angles.z > 180.0)
			{
				angles.z -= 360.0;
			}
			else if (angles.z < -180.0)
			{
				angles.z += 360.0;
			}
			break;
		}

	}
}
float meth::Normalize(float ang)
{
	if (ang > 180.0)
	{
		ang -= 360.0;
	}
	else if (ang < -180.0)
	{
		ang += 360.0;
	}
	return ang;
}
#define M_PI 3.141592653589793
double DEG2RAD(double degrees) {
	return degrees * M_PI / 180.0;
}
void meth::CorrectMovement(CVector vOldAngles, CUserCmd* pCmd, float fOldForward, float fOldSidemove)
{
	//side/forward move correction
	float deltaView = pCmd->viewangles.y - vOldAngles.y;
	float f1;
	float f2;

	if (vOldAngles.y < 0.f)
		f1 = 360.0f + vOldAngles.y;
	else
		f1 = vOldAngles.y;

	if (pCmd->viewangles.y < 0.0f)
		f2 = 360.0f + pCmd->viewangles.y;
	else
		f2 = pCmd->viewangles.y;

	if (f2 < f1)
		deltaView = abs(f2 - f1);
	else
		deltaView = 360.0f - abs(f1 - f2);
	deltaView = 360.0f - deltaView;

	pCmd->forwardmove = cos(DEG2RAD(deltaView)) * fOldForward + cos(DEG2RAD(deltaView + 90.f)) * fOldSidemove;
	pCmd->sidemove = sin(DEG2RAD(deltaView)) * fOldForward + sin(DEG2RAD(deltaView + 90.f)) * fOldSidemove;
}
void SinCos(float a, float* s, float* c)
{
	*s = sin(a);
	*c = cos(a);
}

void meth::AngleVectors(const QAngle& angles, CVector& forward)
{
	float	sp, sy, cp, cy;

	SinCos(DEG2RAD(angles.y), &sy, &cy);
	SinCos(DEG2RAD(angles.x), &sp, &cp);

	forward.x = cp * cy;
	forward.y = cp * sy;
	forward.z = -sp;
}
void meth::AngleVectors(const QAngle& angles, CVector& forward, CVector& right, CVector& up)
{
	float sr, sp, sy, cr, cp, cy;

	SinCos(DEG2RAD(angles.y), &sy, &cy);
	SinCos(DEG2RAD(angles.x), &sp, &cp);
	SinCos(DEG2RAD(angles.z), &sr, &cr);

	forward.x = (cp * cy);
	forward.y = (cp * sy);
	forward.z = (-sp);
	right.x = (-1 * sr * sp * cy + -1 * cr * -sy);
	right.y = (-1 * sr * sp * sy + -1 * cr * cy);
	right.z = (-1 * sr * cp);
	up.x = (cr * sp * cy + -sr * -sy);
	up.y = (cr * sp * sy + -sr * cy);
	up.z = (cr * cp);
}
void meth::VectorAngles(const CVector& forward, QAngle& angles)
{
	if (forward.y == 0.0f && forward.x == 0.0f)
	{
		angles.x = (forward.z > 0.0f) ? 270.0f : 90.0f;
		angles.y = 0.0f;
	}
	else
	{
		angles.x = atan2(-forward.z, forward.Length2D()) * -180 / 3.14;
		angles.y = atan2(forward.y, forward.x) * 180 / 3.14;

		if (angles.y > 90) angles.y -= 180;
		else if (angles.y < 90) angles.y += 180;
		else if (angles.y == 90) angles.y = 0;
	}

	angles.z = 0.0f;
}

CVector CrossProduct(const CVector& a, const CVector& b)
{
	return CVector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

void meth::VectorAngles(const CVector& forward, CVector& up, QAngle& angles)
{
	CVector left = CrossProduct(up, forward);

	float forwardDist = forward.Length2D();

	if (forwardDist > 0.001f)
	{
		angles.x = atan2f(-forward.z, forwardDist) * 180 / 3.14;
		angles.y = atan2f(forward.y, forward.x) * 180 / 3.14;

		float upZ = (left.y * forward.x) - (left.x * forward.y);
		angles.z = atan2f(left.z, upZ) * 180 / 3.14;
	}
	else
	{
		angles.x = atan2f(-forward.z, forwardDist) * 180 / 3.14;
		angles.y = atan2f(-left.x, left.y) * 180 / 3.14;
		angles.z = 0;
	}
}