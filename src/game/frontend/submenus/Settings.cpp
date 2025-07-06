#include "Settings.hpp"

#include "core/commands/Commands.hpp"
#include "core/commands/HotkeySystem.hpp"
#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/frontend/items/Items.hpp"
#include "game/frontend/items/DrawHotkey.hpp"
#include "game/frontend/submenus/Settings/LuaScripts.hpp"

namespace YimMenu::Submenus
{
	// TODO: refactor this
	static void Hotkeys()
	{
		ImGui::BulletText("Giữ nút chứa tên lệnh và nhấn phím tắt mới để thay đổi hotkey.");
		ImGui::BulletText("Nếu lệnh đã có hotkey, nhấn nút sẽ xóa hotkey đó.");

		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();
		
		// this assumes we can't add new commands in runtime, but a lot of other subsystems assume that too
		static std::map<std::string, CommandLink*> sortedCommands;
		static bool commandsSorted = []() {
			for (auto& [hash, command] : Commands::GetCommands())
			{
				if (auto it = g_HotkeySystem.m_CommandHotkeys.find(hash); it != g_HotkeySystem.m_CommandHotkeys.end())
					sortedCommands.emplace(command->GetLabel(), &it->second);
			}
			return true;
		}();

		HotkeySystem::SetBeingModifed(false);

		for (auto& [name, link] : sortedCommands)
		{
			DrawHotkey(link, name);
		}
	};

	Settings::Settings() :
	#define ICON_FA_GEARS "\xef\x80\x93"
	    Submenu::Submenu("Cài đặt", ICON_FA_GEARS)
	{
		auto hotkeys = std::make_shared<Category>("Phím tắt");
		auto gui = std::make_shared<Category>("Giao diện đồ họa");
		auto game = std::make_shared<Category>("Trò chơi");

		auto uiStyle = std::make_shared<Group>("Giao diện người dùng");
		auto playerEsp = std::make_shared<Group>("Hiển thị người chơi (ESP)", 10);
		auto pedEsp = std::make_shared<Group>("Hiển thị nhân vật (Ped ESP)", 10);
		auto objectEsp = std::make_shared<Group>("Hiển thị vật thể (Object ESP)");
		auto overlay = std::make_shared<Group>("Lớp phủ");
		auto chat = std::make_shared<Group>("Trò chuyện");

		hotkeys->AddItem(std::make_shared<ImGuiItem>(Hotkeys));

		// Players
		uiStyle->AddItem(std::make_shared<ListCommandItem>("styleselector"_J));

		playerEsp->AddItem(std::make_shared<BoolCommandItem>("espdrawplayers"_J));
		playerEsp->AddItem(std::make_shared<ConditionalItem>("espdrawplayers"_J, std::make_shared<BoolCommandItem>("espdrawdeadplayers"_J)));

		playerEsp->AddItem(std::make_shared<ConditionalItem>("espdrawplayers"_J, std::make_shared<BoolCommandItem>("espnameplayers"_J, "Tên người chơi")));
		playerEsp->AddItem(std::make_shared<ConditionalItem>("espdrawplayers"_J, std::make_shared<ColorCommandItem>("namecolorplayers"_J)));

		playerEsp->AddItem(std::make_shared<ConditionalItem>("espdrawplayers"_J, std::make_shared<BoolCommandItem>("espdistanceplayers"_J, "Khoảng cách người chơi")));

		playerEsp->AddItem(std::make_shared<ConditionalItem>("espdrawplayers"_J, std::make_shared<BoolCommandItem>("espskeletonplayers"_J, "Khung xương người chơi")));
		playerEsp->AddItem(std::make_shared<ConditionalItem>("espdrawplayers"_J, std::make_shared<ColorCommandItem>("skeletoncolorplayers"_J)));

		// Peds
		pedEsp->AddItem(std::make_shared<BoolCommandItem>("espdrawpeds"_J));
		pedEsp->AddItem(std::make_shared<ConditionalItem>("espdrawpeds"_J, std::make_shared<BoolCommandItem>("espdrawdeadpeds"_J)));

		pedEsp->AddItem(std::make_shared<ConditionalItem>("espdrawpeds"_J, std::make_shared<BoolCommandItem>("espmodelspeds"_J, "Mã định danh nhân vật (Ped Hashes)")));
		pedEsp->AddItem(std::make_shared<ConditionalItem>("espdrawpeds"_J, std::make_shared<ColorCommandItem>("hashcolorpeds"_J)));

		pedEsp->AddItem(std::make_shared<ConditionalItem>("espdrawpeds"_J, std::make_shared<BoolCommandItem>("espnetinfopeds"_J, "Thông tin mạng nhân vật")));
		pedEsp->AddItem(std::make_shared<ConditionalItem>("espdrawpeds"_J, std::make_shared<BoolCommandItem>("espscriptinfopeds"_J, "Thông tin script nhân vật")));

		pedEsp->AddItem(std::make_shared<ConditionalItem>("espdrawpeds"_J, std::make_shared<BoolCommandItem>("espdistancepeds"_J, "Khoảng cách nhân vật")));

		pedEsp->AddItem(std::make_shared<ConditionalItem>("espdrawpeds"_J, std::make_shared<BoolCommandItem>("espskeletonpeds"_J, "Khung xương nhân vật")));
		pedEsp->AddItem(std::make_shared<ConditionalItem>("espdrawpeds"_J, std::make_shared<ColorCommandItem>("skeletoncolorpeds"_J)));

		objectEsp->AddItem(std::make_shared<BoolCommandItem>("espdrawobjects"_J));
		objectEsp->AddItem(std::make_shared<ConditionalItem>("espdrawobjects"_J, std::make_shared<ColorCommandItem>("hashcolorobjects"_J)));
		objectEsp->AddItem(std::make_shared<ConditionalItem>("espdrawobjects"_J, std::make_shared<BoolCommandItem>("espnetinfoobjects"_J, "Thông tin mạng vật thể")));
		objectEsp->AddItem(std::make_shared<ConditionalItem>("espdrawobjects"_J, std::make_shared<BoolCommandItem>("espscriptinfoobjects"_J, "Thông tin script vật thể")));

		objectEsp->AddItem(std::make_shared<ConditionalItem>("espdrawobjects"_J, std::make_shared<BoolCommandItem>("espdistanceobjects"_J, "Khoảng cách vật thể")));


		overlay->AddItem(std::make_shared<BoolCommandItem>("overlay"_J));
		overlay->AddItem(std::make_shared<ConditionalItem>("overlay"_J, std::make_shared<BoolCommandItem>("overlayfps"_J)));

		chat->AddItem(std::make_shared<BoolCommandItem>("clearchat"_J));

		game->AddItem(playerEsp);
		game->AddItem(pedEsp);
		game->AddItem(objectEsp);

		gui->AddItem(uiStyle);
		gui->AddItem(overlay);
		gui->AddItem(chat);

		AddCategory(std::move(hotkeys));
		AddCategory(std::move(gui));
		AddCategory(std::move(game));
		AddCategory(BuildLuaScriptsMenu());
	}
}