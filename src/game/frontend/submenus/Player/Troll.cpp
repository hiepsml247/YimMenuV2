#include "Troll.hpp"

namespace YimMenu::Submenus
{
	std::shared_ptr<Category> BuildTrollMenu()
	{
		auto menu = std::make_shared<Category>("Trêu vui");

		auto general = std::make_shared<Group>("Thông tin chung");
		auto bounty = std::make_shared<Group>("Tiền thưởng", 1);
		auto vehicle = std::make_shared<Group>("Xe");

		general->AddItem(std::make_shared<PlayerCommandItem>("sendsext"_J));
		general->AddItem(std::make_shared<PlayerCommandItem>("sendphantomcar"_J));
		general->AddItem(std::make_shared<PlayerCommandItem>("sendgooch"_J));

		bounty->AddItem(std::make_shared<IntCommandItem>("bountyamount"_J, "Số tiền"));
		bounty->AddItem(std::make_shared<BoolCommandItem>("anonymousbounty"_J, "Ẩn danh"));
		bounty->AddItem(std::make_shared<PlayerCommandItem>("setbounty"_J));

		vehicle->AddItem(std::make_shared<PlayerCommandItem>("deleteveh"_J));

		menu->AddItem(general);
		menu->AddItem(bounty);
		menu->AddItem(vehicle);

		return menu;
	}
}