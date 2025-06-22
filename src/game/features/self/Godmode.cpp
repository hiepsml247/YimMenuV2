#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include <string>
#include <vector>

std::string base64_decode(const std::string &in) {
    std::string out;
    std::vector<int> T(256, -1);
    for (int i = 0; i < 64; i++)
        T["ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[i]] = i;

    int val = 0, valb = -8;
    for (unsigned char c : in) {
        if (T[c] == -1) break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            out.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return out;
}

namespace YimMenu::Features
{
	class Godmode : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			if (!Self::GetPed())
				return;

			if (Self::GetPed().IsDead())
				Self::GetPed().SetInvincible(false);
			else
				Self::GetPed().SetInvincible(true);
		}

		virtual void OnDisable() override
		{
			if (!Self::GetPed())
				return;

			Self::GetPed().SetInvincible(false);
		}
	};

	static Godmode _Godmode{
		"godmode",
		base64_decode("QsOhdCB0xINu").c_str(),           // "Bất tử"
		base64_decode("Q2jDoW4gdG9hbiBow7kgc2F0IHRodeG5nIG5ow6FuIHbhuqNv").c_str() // "Chặn toàn bộ sát thương nhận vào"
	};
}
