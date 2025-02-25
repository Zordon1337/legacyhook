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