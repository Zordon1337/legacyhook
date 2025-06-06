#pragma once
#include <cstddef>

enum class WeaponType {
    Knife = 0,
    Pistol,
    SubMachinegun,
    Rifle,
    Shotgun,
    SniperRifle,
    Machinegun,
    C4,
    Placeholder,
    Grenade,
    Unknown,
    StackableItem,
    Fists,
    BreachCharge,
    BumpMine,
    Tablet,
    Melee
};
struct CSWeaponData {
    std::byte pad1[20];
    int maxClip;
    std::byte pad2[112];
    const char* name;
    std::byte pad3[60];
    WeaponType type;
    std::byte pad4[4];
    int price;
    std::byte pad5[8];
    float cycletime;
    std::byte pad6[12];
    bool fullAuto;
    std::byte pad7[3];
    int damage;
    float headshotMultiplier;
    float armorRatio;
    int bullets;
    float penetration;
    std::byte pad8[8];
    float range;
    float rangeModifier;
    std::byte pad9[16];
    bool silencer;
    std::byte pad10[15];
    float maxSpeed;
    float maxSpeedAlt;
    std::byte pad11[100];
    float recoilMagnitude;
    float recoilMagnitudeAlt;
    std::byte pad12[16];
    float recoveryTimeStand;
};