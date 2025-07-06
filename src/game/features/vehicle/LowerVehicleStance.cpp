#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Features
{
	class LowerVehicleStance : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			auto veh = Self::GetVehicle();
			if (veh)
			{
				veh.LowerStance(true);
			}
		}

		virtual void OnDisable() override
		{
			auto veh = Self::GetVehicle();
			if (veh)
			{
				veh.LowerStance(false);
			}
		}
	};

	static LowerVehicleStance _LowerVehicleStance{"lowervehiclestance", "Hạ gầm xe", "Hạ thấp chiều cao gầm của phương tiện hiện tại (chỉ áp dụng với một số loại xe)"};
}