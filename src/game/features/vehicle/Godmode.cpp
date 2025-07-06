#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Features
{
	class VehicleGodmode : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			auto veh = Self::GetVehicle();
			if (veh)
			{
				veh.SetInvincible(true);
			}
		}

		virtual void OnDisable() override
		{
			auto veh = Self::GetVehicle();
			if (veh)
			{
				veh.SetInvincible(false);
			}
		}
	};

	static VehicleGodmode _VehicleGodmode{"vehiclegodmode", "Chế độ bất tử cho xe", "Chặn mọi sát thương vào phương tiện bạn đang sử dụng"};
}