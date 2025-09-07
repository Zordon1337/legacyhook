#pragma once
#include "CEntity.h"
#include "memory.h"
class IClientEntityList
{
public:
	constexpr CEntity* GetEntityFromIndex(const std::int32_t index) noexcept
	{
		return memory::Call<CEntity*>(this, 3, index);
	}

	constexpr CEntity* GetClientEntityFromHandle(DWORD Handle) noexcept
	{
		return memory::Call<CEntity*>(this, 4, Handle);
	}
};