#include "core/commands/Command.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Features
{
	class ClearDamage : Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			Self::GetPed().ClearDamage();
		}
	};

	static ClearDamage _ClearDamage{"cleardamage", "Làm sạch vết bẩn", "Xóa sạch mọi vết bẩn và máu trên người bạn"};
}