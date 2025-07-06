#include "core/commands/Command.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Pools.hpp"

namespace YimMenu::Features
{
	class BringAllObjs : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			auto pos = Self::GetPed().GetPosition();
			for (auto obj : Pools::GetObjects())
			{
				if (obj)
				{
					obj.ForceControl();
					obj.SetPosition(pos);
				}
			}
		}
	};

	class BringAllPeds : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			auto pos = Self::GetPed().GetPosition();
			for (auto ped : Pools::GetPeds())
			{
				if (!ped.IsPlayer())
				{
					ped.ForceControl();
					ped.SetPosition(pos);
				}
			}
		}
	};

	class BringAllVehs : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			auto pos = Self::GetPed().GetPosition();
			for (auto veh : Pools::GetVehicles())
			{
				veh.ForceControl();
				veh.SetPosition(pos);
			}
		}
	};

	static BringAllObjs _BringAllObjs{"bringobjs", "Kéo tất cả vật thể", "Dịch chuyển toàn bộ vật thể trong game đến vị trí của bạn"};
	static BringAllPeds _BringAllPeds{"bringpeds", "Kéo tất cả NPC", "Dịch chuyển toàn bộ nhân vật điều khiển bởi máy (NPC) đến vị trí của bạn"};
	static BringAllVehs _BringAllVehs{"bringvehs", "Kéo tất cả xe", "Dịch chuyển toàn bộ phương tiện trong game đến vị trí của bạn"};
}