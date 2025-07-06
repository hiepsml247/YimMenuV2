#include "core/commands/Command.hpp"
#include "game/backend/PersonalVehicles.hpp"
#include "game/pointers/Pointers.hpp"

namespace YimMenu
{
	class DespawnPersonalVehicle : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			PersonalVehicles::GetCurrent()->Despawn();
		}
	};

	static DespawnPersonalVehicle _DespawnPersonalVehicle{"despawnpv", "Cất xe cá nhân", "Đưa xe cá nhân hiện tại của bạn về gara"};
}