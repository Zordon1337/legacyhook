#include "hooks.h"
#include "interfaces.h"
#include "minhook/MinHook.h"
#include <iostream>
void hk::Init() {

	if (MH_Initialize())
		throw std::runtime_error("Unable to initialize minhook");
	MH_CreateHook(
		memory::Get(I::clientmode, 24),
		&CreateMove,
		reinterpret_cast<void**>(&CreateMoveOriginal)
	);
	MH_EnableHook(MH_ALL_HOOKS);
}

bool __stdcall hk::CreateMove(float frameTime, CUserCmd* cmd) noexcept
{
	if (!cmd->command_number)
		return hk::CreateMoveOriginal(I::clientmode, frameTime,cmd);

	if (CreateMoveOriginal(I::clientmode, frameTime, cmd))
		I::engine->SetViewAngles(cmd->viewangles);

	if (I::engine->IsInGame())
	{
	{
		auto localPlayer = I::entitylist->GetEntityFromIndex(I::engine->GetLocalPlayerIndex());

		if (localPlayer)
		{
			if (!(localPlayer->getFlags() & CEntity::FL_ONGROUND)) {
				if (!(localPlayer->getFlags() & CEntity::FL_ONGROUND))
					cmd->buttons &= ~CUserCmd::IN_JUMP;
				else
					cmd->buttons |= CUserCmd::IN_JUMP;
			}
		}

	}

	return false;
}