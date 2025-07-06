#include "core/commands/Command.hpp"
#include "core/commands/LoopedCommand.hpp"
#include "core/commands/IntCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	static IntCommand _WantedSlider{"wantedslider", "Điều chỉnh mức truy nã", "Thiết lập hoặc đóng băng cấp độ truy nã", 0, 5, 0};

	class ClearWanted : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			Self::GetPlayer().SetWantedLevel(0);
		}
	};

	class SetWanted : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			Self::GetPlayer().SetWantedLevel(_WantedSlider.GetState());
		}
	};

	class NeverWanted : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			Self::GetPlayer().SetWantedLevel(0);
			PLAYER::SET_MAX_WANTED_LEVEL(0);
		}

		virtual void OnDisable() override
		{
			PLAYER::SET_MAX_WANTED_LEVEL(6);
		}
	};

	class FreezeWanted : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			if (Self::GetPlayer().GetWantedLevel() != _WantedSlider.GetState())
				Self::GetPlayer().SetWantedLevel(_WantedSlider.GetState());
			PLAYER::SET_MAX_WANTED_LEVEL(_WantedSlider.GetState());
		}
	};

	static ClearWanted _ClearWanted{"clearwanted", "Xóa truy nã", "Xóa cấp độ truy nã của bạn"};
	static SetWanted _SetWanted{"setwanted", "Đặt truy nã", "Thiết lập mức truy nã theo ý muốn"};
	static NeverWanted _NeverWanted{"neverwanted", "Không bao giờ bị truy nã", "Bạn sẽ không bao giờ bị tăng cấp độ truy nã"};
	static FreezeWanted _FreezeWanted{"freezewanted", "Đóng băng truy nã", "Giữ nguyên mức truy nã hiện tại theo mong muốn"};
}