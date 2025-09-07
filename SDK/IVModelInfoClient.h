#pragma once
#include "memory.h"

class IVModelInfoClient {
public:
	constexpr std::int32_t GetModelIndex(const char* path) noexcept
	{
		return memory::Call<std::int32_t>(this, 2,path);
	}
};