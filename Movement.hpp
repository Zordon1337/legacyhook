#pragma once
#include "vars.hpp"
#include "CEntity.h"
#include "CUserCmd.h"
namespace Features::Movement {
	void RunBhop(CUserCmd* cmd) {
		if (!cfg::movement::bBunnyHop) return;
		if (!(vars::localPlayer->getFlags() & CEntity::FL_ONGROUND)) {
			if (!(vars::localPlayer->getFlags() & CEntity::FL_ONGROUND))
				cmd->buttons &= ~CUserCmd::IN_JUMP;
			else
				cmd->buttons |= CUserCmd::IN_JUMP;
		}
	}
	void RunAutoStrafe(CUserCmd* cmd) {
		if (!cfg::movement::bAutoStrafe) return;
		
		if (vars::localPlayer->getFlags() & CEntity::FL_ONGROUND) return;

		if (cmd->mousedx > 1 || cmd->mousedx < -1) {
			cmd->sidemove = cmd->mousedx < 0.f ? -450.f : 450.f;
		}
		else {
			cmd->viewangles.y = cmd->mousedx < 0.f ? -90.f : 90.f;
			cmd->sidemove = cmd->command_number % 2 == 0 ? 450.f : -450.f;
		}

	}



}