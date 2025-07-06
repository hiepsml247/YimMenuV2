#include "core/commands/Command.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Features
{
	class EnterLastVehicle : Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (auto last_veh = Self::GetPed().GetLastVehicle())
				Self::GetPed().SetInVehicle(last_veh);
		}
	};

	static EnterLastVehicle _EnterLastVehicle{"enterlastvehicle", "Vào lại xe gần nhất", "Bạn sẽ tự động vào chiếc xe gần nhất mà mình từng sử dụng"};
};