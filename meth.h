
#include "Structs.h"
#include "CUserCmd.h"
namespace meth {
	inline float DotProduct(const CVector& a, const CVector& b);
	void Norm(CVector& angles);
	float Normalize(float ang);
	void CorrectMovement(CVector vOldAngles, CUserCmd* pCmd, float fOldForward, float fOldSidemove);
}