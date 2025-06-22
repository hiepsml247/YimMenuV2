#include "game/backend/Self.hpp"
#include "game/commands/PlayerCommand.hpp"

namespace YimMenu::Features
{
	class TeleportToPlayer : public PlayerCommand
	{
		using PlayerCommand::PlayerCommand;

		virtual void OnCall(Player player) override
		{
			if (auto ped = player.GetPed())
				Self::GetPed().TeleportTo(ped.GetPosition());
		}
	};

	static TeleportToPlayer _TeleportToPlayer{"tptoplayer", "Dịch chuyển đến người chơi", "Bạn sẽ được đưa tới chỗ người chơi mình chọn"};
}