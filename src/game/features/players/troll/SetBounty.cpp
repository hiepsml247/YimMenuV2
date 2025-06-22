#include "core/commands/BoolCommand.hpp"
#include "core/commands/IntCommand.hpp"
#include "game/commands/PlayerCommand.hpp"
#include "types/script/ScriptEvent.hpp"
#include "types/script/globals/GSBD_FM_Events.hpp"

namespace YimMenu::Features
{
	static IntCommand _BountyAmount{"bountyamount", "Đặt tiền thưởng truy nã", "Mức thưởng truy nã cần thiết lập", 1, 1000000, 9000};
	static BoolCommand _AnonymousBounty{"anonymousbounty", "Truy nã ẩn danh", "Đặt tiền truy nã dưới dạng ẩn danh"};

	class SetBounty : public PlayerCommand
	{
		using PlayerCommand::PlayerCommand;

		virtual void OnCall(Player player) override
		{
			SCRIPT_EVENT_BOUNTY bounty;
			bounty.Target = player.GetId();
			bounty.FromPed = _AnonymousBounty.GetState();
			bounty.Amount = _BountyAmount.GetState();
			bounty.BountyFlags = 1;
			bounty.AntiReplayValue1 = GSBD_FM_Events::Get()->AntiReplayValue1;
			bounty.AntiReplayValue2 = GSBD_FM_Events::Get()->AntiReplayValue2;
			bounty.SetAllPlayers();
			bounty.Send();
		}
	};

	static SetBounty _SetBounty{"setbounty", "Đặt truy nã", "Đặt số tiền truy nã cho người chơi đã chọn"};
}