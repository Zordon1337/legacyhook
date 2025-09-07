#pragma once
#include <cstdint>
#include "CUserCmd.h"
#include "vars.hpp"
class IGlobalVars
{
public:
	float realTime;
	std::int32_t frameCount;
	float absFrameTime;
	float absFrameStartTime;
	float currentTime;
	float frameTime;
	std::int32_t maxClients;
	std::int32_t tickCount;
	float intervalPerTick;
	float interpolationAmount;
	std::int32_t frameSimulationTicks;
	std::int32_t networkProtocol;
	void* saveData;
	bool client;
	bool remoteClient;
	std::int32_t timestampNetworkingBase;
	std::int32_t timestampRandomizeWindow;

	float serverTime(CUserCmd* cmd) const noexcept
	{
		static int tick;
		static CUserCmd* lastCmd;

		if (cmd) {
			if (vars::localPlayer && (!lastCmd || lastCmd->hasbeenpredicted))
				tick = vars::localPlayer->tickBase();
			else
				tick++;
			lastCmd = cmd;
		}
		return tick * intervalPerTick;
	}
};