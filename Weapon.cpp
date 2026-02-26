#include "Weapon.h"

Weapon::Weapon(int baseDmg, int variance) noexcept
	: baseDamage(baseDmg), damageVariance(variance) {}

int Weapon::GetBaseDamage() const noexcept
{
	return baseDamage;
}

AttackResult Weapon::ComputeAttack(std::mt19937& rng) const
{
	std::uniform_int_distribution<> dist(0, damageVariance);
	return { baseDamage + dist(rng) };
}

// Spear — rolls for a critical strike after computing base damage.
Spear::Spear(int baseDmg, int variance, double critCh, double critMul) noexcept
	: Weapon(baseDmg, variance), critChance(critCh), critMultiplier(critMul) {}

AttackResult Spear::ComputeAttack(std::mt19937& rng) const
{
	auto result = Weapon::ComputeAttack(rng);

	std::uniform_real_distribution<> roll(0.0, 1.0);
	if (roll(rng) < critChance)
	{
		result.damage = static_cast<int>(result.damage * critMultiplier);
		result.critical = true;
	}
	return result;
}

// Crossbow — bolts have a chance to pierce through dodge.
Crossbow::Crossbow(int baseDmg, int variance, double pierceCh) noexcept
	: Weapon(baseDmg, variance), pierceChance(pierceCh) {}

AttackResult Crossbow::ComputeAttack(std::mt19937& rng) const
{
	auto result = Weapon::ComputeAttack(rng);

	std::uniform_real_distribution<> roll(0.0, 1.0);
	if (roll(rng) < pierceChance)
	{
		result.piercing = true;
	}
	return result;
}
