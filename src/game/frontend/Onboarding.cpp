#include "Onboarding.hpp"
#include "GUI.hpp"
#include "core/commands/Commands.hpp"
#include "core/commands/BoolCommand.hpp"
#include "game/backend/AnticheatBypass.hpp"
#include "game/pointers/Pointers.hpp"
#include <shellapi.h>

namespace YimMenu
{
	static BoolCommand _OnboardingComplete{"$onboardingcomplete", "", ""};

	void ProcessOnboarding()
	{
		if (_OnboardingComplete.GetState())
			return;

		static bool ensure_popup_open = [] {
			ImGui::OpenPopup("QUAN TRỌNG! VUI LÒNG ĐỌC KỸ!");
			GUI::SetOnboarding(true);
			return true;
		}();

		const auto window_size = ImVec2{700, 500};
		const auto window_position = ImVec2{(*Pointers.ScreenResX - window_size.x) / 2, (*Pointers.ScreenResY - window_size.y) / 2};

		ImGui::SetNextWindowSize(window_size, ImGuiCond_Once);
		ImGui::SetNextWindowPos(window_position, ImGuiCond_Once);

		if (ImGui::BeginPopupModal("QUAN TRỌNG! VUI LÒNG ĐỌC KỸ!", nullptr, ImGuiWindowFlags_NoSavedSettings))
		{
			ImGui::TextWrapped("%s",
			    "Chào mừng bạn đến với ChichSML! Bạn có thể nhấn phím INSERT hoặc Ctrl+\\ để mở menu. Kể từ khi BattlEye được áp dụng, khả năng tham gia và ở lại các phòng công khai đã bị giới hạn nghiêm ngặt. "
			    "Bạn có thể chọn chơi chỉ với những người dùng ChichSML khác, hoặc kết nối vào các phòng công khai có BattlEye bảo vệ. "
			    "Tuy nhiên, bạn sẽ tự động bị đẩy ra khỏi các phòng công khai này trong chưa tới ba phút, và có thể bị chặn "
			    "tạm thời không cho vào lại lên đến hai ngày, ngay cả sau khi bật lại BattlEye.");
			static int value = 0;
			ImGui::RadioButton("Tham gia phòng với người dùng ChichSML", &value, 0);
			ImGui::SameLine();
			ImGui::RadioButton("Chơi chung với mọi người (Đang bị lỗi!)", &value, 1);
			ImGui::TextWrapped("%s",
			    "Bạn luôn có thể thay đổi lựa chọn của mình bằng cách vào Mạng > Giả lập > Vào phòng chỉ dành cho YimMenu. OKho lưu trữ chính thức của chúng tôi nằm tại "
			    "http://cocailon.com/. Nhớ chỉ tải menu từ GitHub để tránh phần mềm độc hại. "
			    "Bạn có thể sử dụng kho lưu trữ để báo lỗi, đề xuất tính năng mới, hoặc đóng góp code qua pull request. Chúng tôi cũng có "
			    "máy chủ Matrix tại http://cocailon.com/ để bạn liên hệ nhanh với đội ngũ phát triển  "
			    "và các người dùng khác. Matrix là nền tảng miễn phí, mã nguồn mở, thay thế cho Discord; tạo tài khoản rất an toàn và dễ dàng");
			if (ImGui::Button("Open GitHub"))
			{
				ShellExecuteA(NULL, "open", "http://cocailon.com/", NULL, NULL, SW_SHOWNORMAL);
			}
			ImGui::SameLine();
			if (ImGui::Button("Open Matrix server"))
			{
				ShellExecuteA(NULL, "open", "http://cocailon.com/", NULL, NULL, SW_SHOWNORMAL);
			}
			ImGui::TextWrapped("%s",
			    "Hãy thường xuyên kiểm tra cập nhật, chúng tôi phát hành phiên bản mới mỗi ngày. Quan trọng nhất là hãy khám phá và vui vẻ cùng ChichSML nhé!");
			if (ImGui::Button("Close"))
			{
				Commands::GetCommand<BoolCommand>("cheaterpool"_J)->SetState(!value);
				_OnboardingComplete.SetState(true);
				GUI::SetOnboarding(false);
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}
}