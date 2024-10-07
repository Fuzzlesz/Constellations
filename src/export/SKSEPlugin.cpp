#include "Data/ModObjectManager.h"
#include "Hooks/Athletics.h"
#include "Hooks/AthleticsPerks.h"
#include "Hooks/HandToHand.h"
#include "Hooks/HandToHandPerks.h"
#include "Hooks/Sorcery.h"
#include "Hooks/SorceryPerks.h"

namespace
{
	void InitializeLog()
	{
#ifndef NDEBUG
		auto sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
#else
		auto path = logger::log_directory();
		if (!path) {
			util::report_and_fail("Failed to find standard logging directory"sv);
		}

		*path /= fmt::format("{}.log"sv, Plugin::NAME);
		auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);
#endif

#ifndef NDEBUG
		const auto level = spdlog::level::trace;
#else
		const auto level = spdlog::level::info;
#endif

		auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));
		log->set_level(level);
		log->flush_on(level);

		spdlog::set_default_logger(std::move(log));
		spdlog::set_pattern("%s(%#): [%^%l%$] %v"s);
	}
}

extern "C" DLLEXPORT bool SKSEAPI
SKSEPlugin_Query(const SKSE::QueryInterface* a_skse, SKSE::PluginInfo* a_info)
{
	a_info->infoVersion = SKSE::PluginInfo::kVersion;
	a_info->name = Plugin::NAME.data();
	a_info->version = Plugin::VERSION[0];

	if (a_skse->IsEditor()) {
		logger::critical("Loaded in editor, marking as incompatible"sv);
		return false;
	}

	const auto ver = a_skse->RuntimeVersion();
	if (ver < SKSE::RUNTIME_1_5_39) {
		logger::critical(FMT_STRING("Unsupported runtime version {}"), ver.string());
		return false;
	}

	return true;
}

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
{
	InitializeLog();
	logger::info("{} v{}"sv, Plugin::NAME, Plugin::VERSION.string());

	SKSE::Init(a_skse);

	SKSE::AllocTrampoline(269);

	Hooks::Athletics::WriteHooks();
	Hooks::HandToHand::WriteHooks();
	Hooks::Sorcery::WriteHooks();

	Hooks::AthleticsPerks::WriteHooks();
	Hooks::HandToHandPerks::WriteHooks();
	Hooks::SorceryPerks::WriteHooks();

	SKSE::GetMessagingInterface()->RegisterListener(
		[](auto msg)
		{
			switch (msg->type) {
			case SKSE::MessagingInterface::kPostPostLoad:

				RE::ScriptEventSourceHolder::GetSingleton()->AddEventSink(
					&Data::ModObjectManager::Instance());

				Data::ModObjectManager::Instance().Reload();

				SKSE::GetMessagingInterface()->RegisterListener(
					"CustomSkills",
					[](auto msg)
					{
						CustomSkills::QueryCustomSkillsInterface(
							msg,
							PluginAPIStorage::get().customSkills);

						const auto customSkills = PluginAPIStorage::get().customSkills;

						if (!customSkills) {
							return;
						}

						if (const auto source = customSkills->GetEventDispatcher<
												CustomSkills::SkillIncreaseEvent>()) {
							source->AddEventSink(
								Hooks::Athletics::SkillIncreaseHandler::Instance());
						}
					});
			}
		});
	return true;
};
