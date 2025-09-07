#pragma once
#include "Structs.h"

class CInput
{
public:
	void* pvftable;							//0x00
	bool                m_fTrackIRAvailable;				//0x04
	bool                m_fMouseInitialized;				//0x05
	bool                m_fMouseActive;					//0x06
	bool                m_fJoystickAdvancedInit;			//0x07
	char                pad_0x08[0x2C];					//0x08
	void* m_pKeys;							//0x34
	char                pad_0x38[0x64];					//0x38
	int                 pad_0x41;							//0x9C
	int                 pad_0x42;							//0xA0
	bool                m_fCameraInterceptingMouse;		//0xA4
	bool                m_fCameraInThirdPerson;			//0xA5
	bool                m_fCameraMovingWithMouse;			//0xA6
	CVector              m_vecCameraOffset;					//0xA7
	bool                m_fCameraDistanceMove;				//0xB3
	int                 m_nCameraOldX;						//0xB4
	int                 m_nCameraOldY;						//0xB8
	int                 m_nCameraX;						//0xBC
	int                 m_nCameraY;						//0xC0
};