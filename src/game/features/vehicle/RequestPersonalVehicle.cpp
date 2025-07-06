#include "core/commands/Command.hpp"
#include "game/backend/PersonalVehicles.hpp"
#include "game/pointers/Pointers.hpp"

namespace YimMenu
{
	class RequestPersonalVehicle : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			if (!*Pointers.IsSessionStarted)
				return;

			PersonalVehicles::GetCurrent()->Request();
		}
	};

	static RequestPersonalVehicle _RequestPersonalVehicle{"requestpv", "Gọi xe cá nhân", "Yêu cầu mang phương tiện cá nhân hiện tại đến cho bạn"};
}