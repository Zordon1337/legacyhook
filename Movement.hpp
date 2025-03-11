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
		

		if (!(vars::localPlayer->getFlags() & CEntity::FL_ONGROUND)) {
			if (cmd->mousedx < 0)
				cmd->sidemove = -450.0f;
			if (cmd->mousedx > 0)
				cmd->sidemove = 450.0f;
		}

	}



}