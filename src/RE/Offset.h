#pragma once

namespace RE
{
	namespace Offset
	{
		namespace ActiveEffect
		{
			constexpr auto AdjustForPerks = REL::ID(33278);						// 140557F30 1.6 - 14053DF40 1.5
			constexpr auto DoStandardCustomSkillUsage = REL::ID(33321);			// 14055A950 1.6 - 140540410 1.5
		}

		namespace ActiveEffectFactory
		{
			constexpr auto CheckTargetLevelMagnitude = REL::ID(33273);			// 1405579B0 1.6 - 14053DAA0 1.5
		}

		namespace Actor
		{
			constexpr auto ActorValueModifiedCallbacks = REL::ID(517376);		// 142FD4710 1.6 - 142F39A40 1.5
			constexpr auto CheckAbsorb = REL::ID(37792);						// 140656640 1.6 - 140630850 1.5
			constexpr auto CombatHit = REL::ID(37673);							// 14064E760 1.6 - 140628C20 1.5
			constexpr auto ComputeMovementType = REL::ID(37013);				// 14062F770 1.6 - 14060EEF0 1.5
			constexpr auto ForceUpdateCachedMovementType = REL::ID(36916);		// 14062F5C0 1.6 - 140607FA0 1.5
			constexpr auto Jump = REL::ID(36271);								// 1405F6600 1.6 - 1405D1F80 1.5
			constexpr auto UpdateCommandedActor = REL::ID(37845);				// 140659C90 1.6 - 140633C60 1.5
			constexpr auto UpdateSprinting = REL::ID(36994);					// 140636870 1.6 - 14060E820 1.5
		}

		namespace ActorMagicCaster
		{
			constexpr auto Update = REL::ID(33362);								// 14055C930 1.6 - 140541FC0 1.5
			constexpr auto Vtbl = REL::ID(257613);								// 14172D2D0 1.6 - 141637490 1.5
		}

		namespace BoundItemEffect
		{
			constexpr auto Update = REL::ID(33451);								// 140560A30 1.6 - 140545D10 1.5
		}

		namespace EnchantmentItem
		{
			constexpr auto Vtbl = REL::ID(228570);								// 14161B920 1.6 - 1415217E0 1.5
		}

		namespace EffectItemReplaceTagsFunc
		{
			constexpr auto Invoke = REL::ID(51027);								// 1408C3E80 1.6 - 1408937A0 1.5
		}

		namespace HitData
		{
			constexpr auto InitializeHitData = REL::ID(42832);					// 14076EDB0 1.6 - 140742850 1.5
		}

		namespace ItemCard
		{
			constexpr auto GetMagicItemDescription = REL::ID(51022);			// 1408C2D30 1.6 - 140892cd0 1.5
		}

		namespace MagicCaster
		{
			constexpr auto FindTargets = REL::ID(33634);						// 140568DD0 1.6 - 14054DC90 1.5
		}

		namespace MagicFormulas
		{
			constexpr auto AdjustMagicSpellCost = REL::ID(25922);				// 1403D8D80 1.6 - 1403C1310 1.5
		}

		namespace MagicItem
		{
			constexpr auto GetCost = REL::ID(11213);							// 14010BCB0 1.6 - 140101A30 1.5
		}

		namespace MagicTarget
		{
			constexpr auto AddTarget = REL::ID(33742);							// 14056EDE0 1.6 - 140553750 1.5
		}

		namespace MissileProjectile
		{
			constexpr auto AddImpact = REL::ID(42866);							// 140774140 1.6 - 140747810 1.5
		}

		namespace Projectile
		{
			constexpr auto CombatHit = REL::ID(43027);							// 140782030 1.6 - 1407546B0 1.5
			constexpr auto HandleSpellCollision = REL::ID(43014);				// 14077FEF0 1.6 - 140752620 1.5
		}

		namespace Script
		{
			constexpr auto IsInListConditionFunction = REL::ID(21089);			// 1402EE620 1.6 - 1402DA420 1.5
		}

		constexpr auto HandleWeaponSpeedChannel = REL::ID(41694);				// 1407461E0 1.6 - 14071B670 1.5
		constexpr auto HandleLeftWeaponSpeedChannel = REL::ID(41695);			// 140746230 1.6 - 14071B6C0 1.5
	}
}
