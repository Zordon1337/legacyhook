#include "memory.h"
#include "Structs.h"
class IPrediction {
public:

	void SetLocalViewAngles(CVector& Angles)
	{
		memory::Call<void>(this, 13, &Angles);
	}
};