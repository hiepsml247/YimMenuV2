#include "game/backend/Self.hpp"
#include "game/commands/PlayerCommand.hpp"
#include "core/commands/Vector3Command.hpp"

namespace YimMenu::Features
{
	static Vector3Command _PlayerTeleportCoordinate{"playertpcoord", "Tọa độ cần dịch chuyển", "Nơi người chơi sẽ đến khi dịch chuyển"};

	class TeleportToCoord : public PlayerCommand
	{
		using PlayerCommand::PlayerCommand;

		virtual void OnCall(Player player) override
		{
			player.TeleportTo(_PlayerTeleportCoordinate.GetState());
		}
	};

	static TeleportToCoord _TeleportToCoord{"tpplayertocoord", "Dịch chuyển đến tọa độ", "Đưa người chơi tới điểm bạn chỉ định"};
}