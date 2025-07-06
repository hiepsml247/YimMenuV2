#include "core/commands/Command.hpp"
#include "core/commands/IntCommand.hpp"
#include "core/commands/LoopedCommand.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	static IntCommand _NetworkTimeHour{"networktimehour", "Giờ", "Đặt giờ (0–23)", 0, 23, 12};
	static IntCommand _NetworkTimeMinute{"networktimeminute", "Phút", "Đặt phút (0-59)", 0, 59, 0};
	static IntCommand _NetworkTimeSecond{"networktimesecond", "Giây", "Đặt giây (0-59)", 0, 59, 0};


	class SetNetworkTime : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(_NetworkTimeHour.GetState(),
			    _NetworkTimeMinute.GetState(),
			    _NetworkTimeSecond.GetState());
		}
	};

	class FreezeNetworkTime : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(_NetworkTimeHour.GetState(),
			    _NetworkTimeMinute.GetState(),
			    _NetworkTimeSecond.GetState());
		}

		virtual void OnDisable() override
		{
			NETWORK::NETWORK_CLEAR_CLOCK_TIME_OVERRIDE();
		}
	};

	static SetNetworkTime _SetTime{"setnetworktime", "Chỉnh giờ trong game", "Thay đổi thời gian hiện tại khi chơi online"};
	static FreezeNetworkTime _FreezeTime{"freezenetworktime", "Đóng băng thời gian", "Giữ nguyên đồng hồ trong game ở thời điểm đã chọn khi chơi online"};
}
