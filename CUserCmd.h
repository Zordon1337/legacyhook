#pragma once
#include "Structs.h"

class CUserCmd
{

public:
    enum ECommandButton : std::int32_t
    {
        IN_ATTACK = (1 << 0),
        IN_JUMP = (1 << 1),
        IN_DUCK = (1 << 2),
        IN_FORWARD = (1 << 3),
        IN_BACK = (1 << 4),
        IN_USE = (1 << 5),
        IN_CANCEL = (1 << 6),
        IN_LEFT = (1 << 7),
        IN_RIGHT = (1 << 8),
        IN_MOVELEFT = (1 << 9),
        IN_MOVERIGHT = (1 << 10),
        IN_SECOND_ATTACK = (1 << 11),
        IN_RUN = (1 << 12),
        IN_RELOAD = (1 << 13),
        IN_LEFT_ALT = (1 << 14),
        IN_RIGHT_ALT = (1 << 15),
        IN_SCORE = (1 << 16),
        IN_SPEED = (1 << 17),
        IN_WALK = (1 << 18),
        IN_ZOOM = (1 << 19),
        IN_FIRST_WEAPON = (1 << 20),
        IN_SECOND_WEAPON = (1 << 21),
        IN_BULLRUSH = (1 << 22),
        IN_FIRST_GRENADE = (1 << 23),
        IN_SECOND_GRENADE = (1 << 24),
        IN_MIDDLE_ATTACK = (1 << 25)
    };
    void* vmt;
    int command_number; //4
    int tick_count; //8
    CVector viewangles; //C
    CVector aimDirection;
    float forwardmove; //18
    float sidemove; //1C
    float upmove; //20
    int	buttons; //24
    char impulse; //28
    int weaponselect; //2C
    int weaponsubtype; //30
    int random_seed; //34
    short mousedx; //38
    short mousedy; //3A
    bool hasbeenpredicted;
    CVector headAngles;
    CVector headOffset;
};