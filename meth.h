
#include "Structs.h"
#include "CUserCmd.h"
namespace meth {
	inline float DotProduct(const CVector& a, const CVector& b);
	void Norm(CVector& angles);
	float Normalize(float ang);
	void CorrectMovement(CVector vOldAngles, CUserCmd* pCmd, float fOldForward, float fOldSidemove);
	void AngleVectors(const QAngle& angles, CVector& forward);
	void AngleVectors(const QAngle& angles, CVector& forward, CVector& right, CVector& up);
	void VectorAngles(const CVector& forward, QAngle& angles);
	void VectorAngles(const CVector& forward, CVector& up, QAngle& angles);
}