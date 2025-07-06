#include "HeistModifier.hpp"
#include "Heist/ApartmentHeist.hpp"
#include "Heist/DiamondCasinoHeist.hpp"
#include "Heist/CayoPericoHeist.hpp"
#include "Heist/DoomsdayHeist.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<Category> BuildHeistModifierMenu()
	{
		auto menu = std::make_shared<Category>("Phi vụ");

		menu->AddItem(std::make_shared<ImGuiItem>([] {
			ImGui::BeginTabBar("Thay đổi phi vụ cướp");
		}));
		menu->AddItem(RenderApartmentHeistMenu());
		menu->AddItem(RenderDiamondCasinoHeistMenu());
		menu->AddItem(RenderCayoPericoHeistMenu());
		menu->AddItem(RenderDoomsdayHeistMenu());
		menu->AddItem(std::make_shared<ImGuiItem>([] {
			ImGui::EndTabBar();
		}));

		return menu;
	}
}