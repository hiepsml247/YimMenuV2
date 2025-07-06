#include "core/commands/BoolCommand.hpp"
#include "game/pointers/Pointers.hpp"

namespace YimMenu::Features
{
	class Aimbot : public BoolCommand
	{
		using BoolCommand::BoolCommand;

		virtual void OnEnable() override
		{
			Pointers.ShouldNotTargetEntityPatch->Apply();
			Pointers.GetAssistedAimTypePatch->Apply();
		}

		virtual void OnDisable() override
		{
			Pointers.ShouldNotTargetEntityPatch->Restore();
			Pointers.GetAssistedAimTypePatch->Restore();
		}
	};

	class AimbotAimForHead : BoolCommand
	{
		using BoolCommand::BoolCommand;

		virtual void OnEnable() override
		{
			Pointers.GetLockOnPosPatch->Apply();
		}

		virtual void OnDisable() override
		{
			Pointers.GetLockOnPosPatch->Restore();
		}
	};

	class AimbotTargetDrivers : BoolCommand
	{
		using BoolCommand::BoolCommand;

		virtual void OnEnable() override
		{
			Pointers.ShouldAllowDriverLockOnPatch->Apply();
		}

		virtual void OnDisable() override
		{
			Pointers.ShouldAllowDriverLockOnPatch->Restore();
		}
	};

	static Aimbot _Aimbot{"aimbot", "Tự động ngắm", "Tự động khóa mục tiêu vào kẻ địch và người chơi khác"};
	static AimbotAimForHead _AimbotAimForHead{"aimbotaimforhead", "Ngắm vào đầu", "Khi tự động khóa mục tiêu sẽ nhắm thẳng vào đầu đối thủ hoặc người chơi khác"};
	static AimbotTargetDrivers _AimbotTargetDrivers{"aimbottargetdrivers", "Ngắm tài xế", "Cho phép tự động ngắm vào kẻ địch và người chơi đang lái xe"};
}