#include "HandToHand.h"
#include "HandToHandPerks.h"

#include "Data/Skills.h"
#include "RE/Offset.h"

namespace Hooks
{
	void HandToHand::WriteHooks()
	{
		ExperiencePatch();
		SkillMultiplierPatch();
	}

	void HandToHand::ExperiencePatch()
	{
		auto hook = REL::Relocation<std::uintptr_t>(RE::Offset::Actor::CombatHit, 0x434);
		REL::make_pattern<"E8">().match_or_fail(hook.address());

		// TRAMPOLINE: 14
		auto& trampoline = SKSE::GetTrampoline();
		_ProcessHandToHandXP = trampoline.write_call<5>(hook.address(), &HandToHand::ProcessHandToHandXP);
	}

	void HandToHand::SkillMultiplierPatch()
	{
		auto hook = REL::Relocation<std::uintptr_t>(RE::Offset::HitData::InitializeHitData, 0x26A);
		REL::make_pattern<"E8">().match_or_fail(hook.address());

		// TRAMPOLINE: 14
		auto& trampoline = SKSE::GetTrampoline();
		_GetUnarmedDamage = trampoline.write_call<5>(hook.address(), &HandToHand::GetUnarmedDamage);
	}

	void HandToHand::ProcessHandToHandXP(const RE::HitData& a_hitData)
	{
		_ProcessHandToHandXP(a_hitData);

		const auto aggressor = a_hitData.aggressor.get();
		if (!aggressor || !aggressor->GetIsPlayerOwner())
			return;

		if (!a_hitData.weapon || !a_hitData.weapon->IsHandToHandMelee())
			return;

		const float skillUse = aggressor->GetActorValue(RE::ActorValue::kUnarmedDamage);
		if (const auto customSkills = util::GetCustomSkillsInterface()) {
			customSkills->AdvanceSkill("HandToHand", skillUse);
		}
	}

	void HandToHand::GetUnarmedDamage(const RE::ActorValueOwner* a_avOwner, float& a_damage)
	{
		_GetUnarmedDamage(a_avOwner, a_damage);

		const auto actor = SKSE::stl::adjust_pointer<RE::Actor>(a_avOwner, -0xB0);
		HandToHandPerks::HandleBaseDamage(actor, a_damage);

		if (a_avOwner->GetIsPlayerOwner()) {
			const float skill = (std::max)(Data::HandToHand::GetLevel(), 0.0f);

			const float maxMult = "fDamagePCSkillMax"_gs.value_or(1.5f);
			const float minMult = "fDamagePCSkillMin"_gs.value_or(1.0f);
			const float skillMult = std::lerp(minMult, maxMult, skill / 100.0f);

			a_damage *= skillMult;
		}
	}
}
