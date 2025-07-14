#include "common.hpp"
#include "core/backend/ScriptMgr.hpp"
#include "core/backend/FiberPool.hpp"
#include "core/commands/Commands.hpp"
#include "core/commands/HotkeySystem.hpp"
#include "core/settings/Settings.hpp"
#include "core/filemgr/FileMgr.hpp"
#include "core/frontend/Notifications.hpp"
#include "core/hooking/Hooking.hpp"
#include "core/hooking/CallHook.hpp"
#include "core/memory/ModuleMgr.hpp"
#include "core/renderer/Renderer.hpp"
#include "core/util/Wine.hpp"
#include "core/scripting/LuaManager.hpp"
#include "game/backend/AnticheatBypass.hpp"
#include "game/backend/Players.hpp"
#include "game/backend/SavedLocations.hpp"
#include "game/backend/SavedPlayers.hpp"
#include "game/backend/Self.hpp"
#include "game/backend/NativeHooks.hpp"
#include "game/backend/Tunables.hpp"
#include "game/backend/ScriptPointers.hpp"
#include "game/frontend/GUI.hpp"
#include "game/pointers/Pointers.hpp"
#include "game/features/vehicle/SavePersonalVehicle.hpp"
#include "game/features/self/OpenGunLocker.hpp"
#include "game/features/recovery/DailyActivities.hpp"
#include "json.hpp"

using json = nlohmann::json;

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string fetch_active_status() {
    CURL* curl = curl_easy_init();
    std::string readBuffer;
    if (curl) {
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "apikey: KEY");
        headers = curl_slist_append(headers, "Authorization: AUTH");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_URL, "http://basic3.asaka.asia:27053/status");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
            readBuffer = "{}";
        }
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}

std::pair<std::string, std::string> parse_status(const std::string& jsonStr) {
    try {
        auto j = json::parse(jsonStr);
        std::string name = j.value("name", "Unknown");
        std::string color;
        if (name == "Working" || name == u8"Hoạt động") color = "32";
        else if (name == "Under Maintenance" || name == u8"Bảo trì") color = "33";
        else if (name == "Not Working" || name == u8"Không hoạt động") color = "31";
        else color = "94";
        return { name, color };
    } catch (...) {
        return { "Unknown", "31" };
    }
}

namespace YimMenu
{
	DWORD Main(void*)
	{
		const auto documents = std::filesystem::path(std::getenv("appdata")) / "ChichSML";
		FileMgr::Init(documents);

		LogHelper::Init("ChichSML", FileMgr::GetProjectFile("./cout.log"));

		// --- Fetch & log API status
    	const auto status_json = fetch_active_status();
    	auto [status_name, status_color] = parse_status(status_json);
    	LOGF(INFO, "[Status] API: %s", status_name.c_str());

		LOGF(INFO, "Chào mừng đến với ChichSML! Ngày tạo: {} at {}", __DATE__, __TIME__);

		g_HotkeySystem.RegisterCommands();
		SavedLocations::FetchSavedLocations();
		Settings::Initialize(FileMgr::GetProjectFile("./settings.json"));

		if (!ModuleMgr.LoadModules())
			goto EARLY_UNLOAD;

		if (ModuleMgr.IsManualMapped())
			LOGF(WARNING, "Đã phát hiện nạp thủ công, hãy thử đổi sang nạp thông thường nếu có lỗi");

		if (!Pointers.Init())
			goto EARLY_UNLOAD;

		AnticheatBypass::RunOnStartup();

		if (!Renderer::Init())
			goto EARLY_UNLOAD;

		Players::Init();

		Hooking::Init();

		ScriptMgr::Init();
		LOG(INFO) << "ScriptMgr initialized";

		ScriptPointers::Init();

		GUI::Init();

		ScriptMgr::AddScript(std::make_unique<Script>(&NativeHooks::RunScript)); // runs once
		ScriptMgr::AddScript(std::make_unique<Script>(&Tunables::RunScript));    // runs once
		ScriptMgr::AddScript(std::make_unique<Script>(&AnticheatBypass::RunScript));
		ScriptMgr::AddScript(std::make_unique<Script>(&Self::RunScript));
		ScriptMgr::AddScript(std::make_unique<Script>(&GUI::RunScript));
		FiberPool::Init(16);
		ScriptMgr::AddScript(std::make_unique<Script>(&LuaManager::RunScript));
		ScriptMgr::AddScript(std::make_unique<Script>(&HotkeySystem::RunScript));
		ScriptMgr::AddScript(std::make_unique<Script>(&Commands::RunScript));
		ScriptMgr::AddScript(std::make_unique<Script>(&Features::SavePersonalVehicle::RunScript));
		ScriptMgr::AddScript(std::make_unique<Script>(&Features::OpenGunLocker::RunScript));
		ScriptMgr::AddScript(std::make_unique<Script>(&Features::OpenStreetDealerMenu::RunScript));
		ScriptMgr::AddScript(std::make_unique<Script>(&SavedPlayers::RunScript));

		if (!Pointers.LateInit())
			LOG(WARNING) << "Tải mẫu Social Club thất bại";

		Notifications::Show("ChichSML", "Tải thành công", NotificationType::Success);

		if (InWine().value_or(false))
		    LOG(INFO) << "Running in Wine!";

		while (g_Running)
		{
			Settings::Tick();
			std::this_thread::yield();
		}

		LOG(INFO) << "Unloading";
		NativeHooks::Destroy();
		FiberPool::Destroy();
		ScriptMgr::Destroy();
		Hooking::Destroy();
		CallSiteHook::Destroy();

	EARLY_UNLOAD:
		g_Running = false;
		Renderer::Destroy();
		LogHelper::Destroy();

		CloseHandle(g_MainThread);
		FreeLibraryAndExitThread(g_DllInstance, EXIT_SUCCESS);

		return EXIT_SUCCESS;
	}
}

BOOL WINAPI DllMain(HINSTANCE dllInstance, DWORD reason, void*)
{
	using namespace YimMenu;

	if (dllInstance)
		DisableThreadLibraryCalls(dllInstance);

	if (reason == DLL_PROCESS_ATTACH)
	{
		g_DllInstance = dllInstance;

		g_MainThread = CreateThread(nullptr, 0, Main, nullptr, 0, &g_MainThreadId);
	}
	return true;
}