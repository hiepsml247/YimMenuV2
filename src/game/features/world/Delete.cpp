#include "core/commands/Command.hpp"
#include "game/gta/Pools.hpp"
#include "game/gta/Object.hpp"

namespace YimMenu::Features
{
	class DeleteAllObjects : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			for (auto obj : Pools::GetObjects())
			{
				if (obj)
					obj.Delete();
			}
		}
	};

	class DeleteAllCameras : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			for (auto obj : Pools::GetObjects())
			{
				if (obj && obj.As<Object>().IsCamera())
					obj.Delete();
			}
		}
	};

	class DeleteAllPeds : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			for (auto ped : Pools::GetPeds())
			{
				if (!ped.IsPlayer())
					ped.Delete();
			}
		}
	};

	class DeleteAllVehs : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			for (auto veh : Pools::GetVehicles())
			{
				veh.Delete();
			}
		}
	};

	static DeleteAllCameras _DeleteAllCameras("delcams", "Xóa tất cả camera", "Xóa toàn bộ camera trong game");
	static DeleteAllObjects _DeleteAllObjects{"delobjs", "Xóa tất cả vật thể", "Xóa toàn bộ vật thể trong game, bao gồm cả những vật quan trọng trong nhiệm vụ"};
	static DeleteAllPeds _DeleteAllPeds{"delpeds", "Xóa tất cả NPC", "Xóa toàn bộ nhân vật điều khiển bởi máy trong game, kể cả những nhân vật quan trọng trong nhiệm vụ"};
	static DeleteAllVehs _DeleteAllVehs{"delvehs", "Xóa tất cả xe", "Xóa toàn bộ phương tiện trong game, bao gồm cả xe quan trọng trong nhiệm vụ"};
}