#include "core/commands/StringCommand.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Object.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	static StringCommand _PedModelName{"pedmodelname", "Mẫu nhân vật", "Tên mẫu của nhân vật (NPC) bạn muốn tạo ra"};
	static StringCommand _ObjectModelName{"objectmodelname", "Mẫu vật thể", "Tên mô hình của vật thể bạn muốn tạo ra"};


	class SpawnPed : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			auto model = _PedModelName.GetString();
			if (!model.length())
			{
				Notifications::Show("Gọi NPC", "Bạn chưa cung cấp tên mẫu nhân vật cần tạo", NotificationType::Error);
				return;
			}

			auto modelHash = Joaat(model);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(modelHash))
			{
				Ped::Create(modelHash, Self::GetPed().GetPosition(), Self::GetPed().GetHeading());
			}
			else
			{
				Notifications::Show("Gọi NPC", "Tên mô hình không hợp lệ", NotificationType::Error);
			}
		}
	};

	class SpawnObject : public Command
	{
		using Command::Command;

		virtual void OnCall() override
		{
			auto model = _ObjectModelName.GetString();
			if (!model.length())
			{
				Notifications::Show("Gọi đối tượng", "Chưa nhập tên mô hình vật thể", NotificationType::Error);
				return;
			}

			auto modelHash = Joaat(model);
			if (STREAMING::IS_MODEL_IN_CDIMAGE(modelHash))
			{
				Object::Create(modelHash, Self::GetPed().GetPosition());
			}
			else
			{
				Notifications::Show("Gọi đối tượng", "Tên mô hình không hợp lệ", NotificationType::Error);
			}
		}
	};

	static SpawnPed _SpawnPed{"spawnped", "Gọi NPC", "Tạo một NPC ngay tại chỗ bạn đang đứng"};
	static SpawnObject _SpawnObject{"spawnobject", "Gọi đối tượng", "Tạo một đối tượng trong game ngay chỗ bạn đang đứng"};
}