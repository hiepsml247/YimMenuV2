#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Pools.hpp"

#include <game/gta/Natives.hpp>

namespace YimMenu::Features
{
	class PedRiotMode : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;
		virtual void OnTick() override
		{
			MISC::SET_RIOT_MODE_ENABLED(TRUE);
		}

		virtual void OnDisable() override
		{
			MISC::SET_RIOT_MODE_ENABLED(FALSE);
		}
	};

	static PedRiotMode _PedRiotMode{"PedRiotMode", "Chế độ bạo loạn", "Tất cả NPC sẽ tấn công lẫn nhau"};

}