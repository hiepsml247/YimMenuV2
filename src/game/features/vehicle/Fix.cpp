#include "core/commands/Command.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Features
{
	class RepairVehicle : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (Self::GetVehicle())
				Self::GetVehicle().Fix();
		}
	};

	static RepairVehicle _RepairVehicle{"repairvehicle", "Sửa xe", "Khắc phục mọi hư hỏng trên phương tiện bạn đang sử dụng"};
}