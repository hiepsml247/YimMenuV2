#include "core/commands/LoopedCommand.hpp"
#include "core/commands/ListCommand.hpp"
#include "game/pointers/Pointers.hpp"

namespace YimMenu::Features
{
	static std::vector<std::pair<int, const char*>> g_RegionCodes = {
	    {0, "CIS"},
	    {1, "South America"},
	    {2, "US East"},
	    {3, "Europe"},
	    {4, "China"},
	    {5, "Australia"},
	    {6, "US West"},
	    {7, "Japan"},
	    {8, "Unknown"},
	};

	static ListCommand _SpoofedRegion{"mmregion", "Khu vực ghép trận", "Khu vực sẽ được giả lập khi ghép trận", g_RegionCodes, 0};

	class SpoofMatchmakingRegion : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		int m_OldRegion;

		virtual void OnEnable() override
		{
			m_OldRegion = *Pointers.RegionCode;
		}

		virtual void OnTick() override
		{
			*Pointers.RegionCode = _SpoofedRegion.GetState();
		}

		virtual void OnDisable() override
		{
			*Pointers.RegionCode = m_OldRegion;
		}
	};

	static SpoofMatchmakingRegion _SpoofMatchmakingRegion{"spoofmmregion", "Giả lập vùng ghép trận", "Thay đổi vùng ghép trận của bạn thành khu vực đã chọn"};
}