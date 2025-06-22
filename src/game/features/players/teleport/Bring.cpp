#include "game/commands/PlayerCommand.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Features
{
	class Bring : public PlayerCommand
	{
		using PlayerCommand::PlayerCommand;

		virtual void OnCall(Player player) override
		{
			player.TeleportTo(Self::GetPed().GetPosition());
		}
	};

	static Bring _Bring{"bring", "Kéo người chơi lại gần bạn", "Đưa người chơi đến vị trí của bạn"};
}