#include "core/commands/Command.hpp"
#include "game/gta/Pools.hpp"

namespace YimMenu::Features
{
	class KillAll : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			for (auto ped : Pools::GetPeds())
			{
				if (!ped.IsPlayer())
					ped.Kill();
			}
		}
	};

	class KillAllEnemies : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			for (auto ped : Pools::GetPeds())
			{
				if (!ped.IsPlayer() && ped.IsEnemy())
					ped.Kill();
			}
		}
	};

	static KillAll _KillAll{"killallpeds", "Tiêu diệt tất cả NPC", "Hạ gục toàn bộ nhân vật điều khiển bởi máy trong game"};
	static KillAllEnemies _KillAllEnemies{"killallenemies", "Tiêu diệt tất cả kẻ địch", "Hạ gục toàn bộ kẻ thù trong thế giới game"};
}