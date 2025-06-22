#include "game/commands/PlayerCommand.hpp"
#include "types/fx/ExplosionType.hpp"

namespace YimMenu::Features
{
	class Explode : public PlayerCommand
	{
		using PlayerCommand::PlayerCommand;

		virtual void OnCall(Player player) override
		{
			if (auto ped = player.GetPed())
				ped.Explode(ExplosionType::BLIMP, 900.f);
		}
	};

	static Explode _Explode{"explode", "Nổ người chơi", "Làm người chơi nổ tung"};
}