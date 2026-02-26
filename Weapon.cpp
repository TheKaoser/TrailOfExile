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

// Staff — straightforward magic weapon, meant to be enhanced with enchantments.
Staff::Staff(int baseDmg, int variance) noexcept
	: Weapon(baseDmg, variance) {}

// ---------------------------------------------------------------------------
// Weapon Enchantments (Decorator pattern)
// ---------------------------------------------------------------------------

WeaponEnchantment::WeaponEnchantment(std::unique_ptr<Weapon> weapon, const std::string& prefix)
	: Weapon(0, 0), baseWeapon(std::move(weapon))
{
	// Build a composite name like "Flaming Staff" or "Venomous Flaming Staff".
	combinedName = prefix + " " + baseWeapon->GetName();
}

AttackResult WeaponEnchantment::ComputeAttack(std::mt19937& rng) const
{
	return baseWeapon->ComputeAttack(rng);
}

int WeaponEnchantment::GetBaseDamage() const noexcept
{
	return baseWeapon->GetBaseDamage();
}

// Flaming — adds flat fire damage to every hit.
FlamingEnchantment::FlamingEnchantment(std::unique_ptr<Weapon> weapon, int bonusDmg)
	: WeaponEnchantment(std::move(weapon), "Flaming"), bonusDamage(bonusDmg) {}

AttackResult FlamingEnchantment::ComputeAttack(std::mt19937& rng) const
{
	auto result = baseWeapon->ComputeAttack(rng);
	result.damage += bonusDamage;
	return result;
}

// Venom — chance to inject bonus poison damage.
VenomEnchantment::VenomEnchantment(std::unique_ptr<Weapon> weapon, double chance, int bonusDmg)
	: WeaponEnchantment(std::move(weapon), "Venomous"), procChance(chance), bonusDamage(bonusDmg) {}

AttackResult VenomEnchantment::ComputeAttack(std::mt19937& rng) const
{
	auto result = baseWeapon->ComputeAttack(rng);

	std::uniform_real_distribution<> roll(0.0, 1.0);
	if (roll(rng) < procChance)
	{
		result.damage += bonusDamage;
		if (result.enchantEffect.empty())
			result.enchantEffect = "(venom!)";
		else
			result.enchantEffect += " (venom!)";
	}
	return result;
}
