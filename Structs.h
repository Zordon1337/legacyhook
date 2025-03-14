#pragma once
#include <numbers>
#include <cstdint>
#include <cmath>

class QAngle
{

public:
    QAngle() : x(0.0f), y(0.0f), z(0.0f) {}

    // Constructor with x, y, and z arguments
    QAngle(float x, float y, float z) : x(x), y(y), z(z) {}

    // Copy constructor
    QAngle(const QAngle& other) : x(other.x), y(other.y), z(other.z) {}

    // Copy assignment operator
    QAngle& operator=(const QAngle& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            z = other.z;
        }
        return *this;
    }

    // Addition operator
    QAngle operator+(const QAngle& other) const {
        return QAngle(x + other.x, y + other.y, z + other.z);
    }

    // Subtraction operator
    QAngle operator-(const QAngle& other) const {
        return QAngle(x - other.x, y - other.y, z - other.z);
    }

    // Multiplication operator
    QAngle operator*(const QAngle& other) const {
        return QAngle(x * other.x, y * other.y, z * other.z);
    }

    // Division operator
    QAngle operator/(const QAngle& other) const {
        return QAngle(x / other.x, y / other.y, z / other.z);
    }

    // Scalar multiplication
    QAngle Scale(float factor) const {
        return QAngle(x * factor, y * factor, z * factor);
    }
    inline QAngle ToVector() const noexcept
    {
        return {
            -static_cast<float>(std::sin(z * (std::numbers::pi / 180.0))),
        static_cast<float>(std::cos(z * (std::numbers::pi / 180.0)) * std::cos(x * (std::numbers::pi / 180.0))),
        static_cast<float>(std::sin(x * (std::numbers::pi / 180.0)))
        };
    }

    float x{}, y{}, z{};
};

class CVector
{
public:
    constexpr CVector operator+(const CVector& other) const noexcept
    {
        return { x + other.x, y + other.y, z + other.z };
    }

    constexpr CVector operator-(const CVector& other) const noexcept
    {
        return { x - other.x, y - other.y, z - other.z };
    }

    constexpr CVector operator*(const CVector& other) const noexcept
    {
        return { x * other.x, y * other.y, z * other.z };
    }

    constexpr CVector operator/(const CVector& other) const noexcept
    {
        return { x / other.x, y / other.y, z / other.z };
    }

    constexpr CVector Scale(float factor) const noexcept
    {
        return { x * factor, y * factor, z * factor };
    }

    inline CVector ToAngle() const noexcept
    {
        return {
            std::atan2(-z, std::hypot(x, y)) * (180.0f / std::numbers::pi_v<float>),
            std::atan2(y, x) * (180.0f / std::numbers::pi_v<float>),
            0.0f
        };
    }

    float x{ }, y{ }, z{ };
};

__declspec(align(16)) class CVectorAligned : public CVector
{
public:
    constexpr CVectorAligned operator-(const CVectorAligned& other) const noexcept
    {
        return { x - other.x, y - other.y, z - other.z, w - other.w };
    }

    float w{ };
};

class CMatrix3x4
{
public:
    constexpr float* operator[](size_t index) noexcept
    {
        return data[index];
    }

    constexpr CVector Origin() noexcept
    {
        return { data[0][3], data[1][3], data[2][3] };
    }
    constexpr bool IsValidBone() {

        return data[0][0] != 0.0f || data[0][1] != 0.0f || data[0][2] != 0.0f || data[0][3] != 0.0f;
    }
    float data[3][4];
};

class CMatrix4x4
{
public:
    float data[4][4];

    float* operator[](int index) {
        return data[index];
    }

    const float* operator[](int index) const {
        return data[index];
    }
};