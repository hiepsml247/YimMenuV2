#include "ApartmentHeist.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<TabItem> RenderApartmentHeistMenu()
	{
		auto tab = std::make_shared<TabItem>("Phi vụ cướp căn hộ");

		auto cuts = std::make_shared<Group>("Phần chia tiền phi vụ", 2);
		auto setups = std::make_shared<Group>("Chuẩn bị phi vụ");
		auto misc = std::make_shared<Group>("Linh tinh", 1);

		cuts->AddItem(std::make_shared<IntCommandItem>("apartmentheistcut1"_J));
		cuts->AddItem(std::make_shared<IntCommandItem>("apartmentheistcut3"_J));
		cuts->AddItem(std::make_shared<IntCommandItem>("apartmentheistcut2"_J));
		cuts->AddItem(std::make_shared<IntCommandItem>("apartmentheistcut4"_J));
		cuts->AddItem(std::make_shared<CommandItem>("apartmentheistforceready"_J));
		cuts->AddItem(std::make_shared<CommandItem>("apartmentheistsetcuts"_J));

		setups->AddItem(std::make_shared<CommandItem>("apartmentheistsetup"_J));

		misc->AddItem(std::make_shared<CommandItem>("apartmentheistskiphacking"_J));
		misc->AddItem(std::make_shared<CommandItem>("apartmentheistskipdrilling"_J));
		misc->AddItem(std::make_shared<CommandItem>("apartmentheistinstantfinish"_J));
		misc->AddItem(std::make_shared<CommandItem>("apartmentheistinstantfinishpacific"_J));

		tab->AddItem(cuts);
		tab->AddItem(setups);
		tab->AddItem(misc);

		return tab;
	}
}