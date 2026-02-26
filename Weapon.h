#pragma once

#include <random>

class Character;

// Returned by Weapon::ComputeAttack to describe what happened.
struct AttackResult
{
	int damage = 0;
	bool critical = false;
	bool piercing = false;
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
