#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	class DisableActionMode : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			PED::SET_PED_RESET_FLAG(Self::GetPed().GetHandle(), 200, true);
		}
	};

	static DisableActionMode _DisableActionMode{"disableactionmode", "Tắt di chuyển kiểu chiến đấu", "Nhân vật sẽ di chuyển mượt hơn khi vào combat"};
};
