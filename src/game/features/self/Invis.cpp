#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Features
{
	static BoolCommand _LocallyVisible{"localvis", "Chỉ hiện với bản thân", "Bạn vẫn nhìn thấy mình, nhưng người chơi khác sẽ không thấy bạn"};

	class Invis : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			if (Self::GetPed())
			{
				Self::GetPed().SetVisible(false);
				if (_LocallyVisible.GetState())
					Self::GetPlayer().SetVisibleLocally(true);
				else
					Self::GetPlayer().SetVisibleLocally(false);
			}
		}

		virtual void OnDisable() override
		{
			if (Self::GetPed())
			{
				Self::GetPed().SetVisible(true);
				Self::GetPlayer().SetVisibleLocally(false);
			}
		}
	};

	static Invis _Invis{"invis", "Tàng hình", "Biến mất khỏi tầm nhìn của người khác"};
}