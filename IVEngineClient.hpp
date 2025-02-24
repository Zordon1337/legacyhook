
#pragma once
#include "memory.h"
#include "Structs.h"
class IVEngineClient
{
public:
	constexpr std::int32_t GetLocalPlayerIndex() noexcept
	{
		return memory::Call<std::int32_t>(this, 12);
	}

	constexpr void GetViewAngles(const CVector& viewAngles) noexcept
	{
		memory::Call<void, const CVector&>(this, 18, viewAngles);
	}
	constexpr void SetViewAngles(const CVector& viewAngles) noexcept
	{
		memory::Call<void, const CVector&>(this, 19, viewAngles);
	}

	constexpr bool IsInGame() noexcept
	{
		return memory::Call<bool>(this, 26);
	}
};