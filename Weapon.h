#pragma once

#include <memory>
#include <random>
#include <string>

class Character;

// Returned by Weapon::ComputeAttack to describe what happened.
struct AttackResult
{
	int damage = 0;
	bool critical = false;
	bool piercing = false;
	std::string enchantEffect; // set by enchantments when they proc
};

// Base weapon. Subclasses override ComputeAttack() to add special mechanics
// like critical strikes (Spear) or armor-piercing shots (Crossbow).
class Weapon
{
protected:
	int baseDamage;
	int damageVariance;

public:
	Weapon(int baseDmg, int variance) noexcept;
	virtual ~Weapon() = default;

	// Roll damage with variance and any weapon-specific effects.
	virtual AttackResult ComputeAttack(std::mt19937& rng) const;
	int GetBaseDamage() const noexcept;
	virtual const char* GetName() const noexcept = 0;
};

// Fast melee weapon with a chance to land critical strikes.
class Spear : public Weapon
{
	double critChance;
	double critMultiplier;

public:
	Spear(int baseDmg, int variance, double critCh, double critMul) noexcept;
	AttackResult ComputeAttack(std::mt19937& rng) const override;
	const char* GetName() const noexcept override { return "Spear"; }
};

// Ranged weapon whose bolts can pierce through dodge.
class Crossbow : public Weapon
{
	double pierceChance;

public:
	Crossbow(int baseDmg, int variance, double pierceCh) noexcept;
	AttackResult ComputeAttack(std::mt19937& rng) const override;
	const char* GetName() const noexcept override { return "Crossbow"; }
};

// Simple magical weapon — reliable damage with low variance.
// Best used as a base for enchantment decorators.
class Staff : public Weapon
{
public:
	Staff(int baseDmg, int variance) noexcept;
	const char* GetName() const noexcept override { return "Staff"; }
};

// ---------------------------------------------------------------------------
// Decorator pattern — enchantments wrap any Weapon and layer extra behaviour
// on top of its ComputeAttack(). Decorators compose: a FlamingEnchantment
// wrapping a VenomEnchantment wrapping a Staff will fire all three layers.
// ---------------------------------------------------------------------------

// Abstract base for every enchantment. Delegates to the wrapped weapon by
// default; subclasses override ComputeAttack() to add their own modifier.
class WeaponEnchantment : public Weapon
{
protected:
	std::unique_ptr<Weapon> baseWeapon;
	std::string combinedName;

public:
	WeaponEnchantment(std::unique_ptr<Weapon> weapon, const std::string& prefix);
	~WeaponEnchantment() override = default;

	AttackResult ComputeAttack(std::mt19937& rng) const override;
	int GetBaseDamage() const noexcept;
	const char* GetName() const noexcept override { return combinedName.c_str(); }
};

// Adds flat fire damage to every hit.
class FlamingEnchantment : public WeaponEnchantment
{
	int bonusDamage;

public:
	FlamingEnchantment(std::unique_ptr<Weapon> weapon, int bonusDmg);
	AttackResult ComputeAttack(std::mt19937& rng) const override;
};

// Chance-based proc that adds bonus poison damage.
class VenomEnchantment : public WeaponEnchantment
{
	double procChance;
	int bonusDamage;

public:
	VenomEnchantment(std::unique_ptr<Weapon> weapon, double chance, int bonusDmg);
	AttackResult ComputeAttack(std::mt19937& rng) const override;
};
