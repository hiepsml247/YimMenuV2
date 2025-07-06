#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Features
{
	class KeepPlayerClean : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			if (!Self::GetPed())
				return;

			Self::GetPed().ClearDamage();
		}
	};

	static KeepPlayerClean _KeepPlayerClean{"keepplayerclean", "Luôn sạch sẽ", "Giữ cho nhân vật không dính máu, bùn đất hay nước bẩn"};
}