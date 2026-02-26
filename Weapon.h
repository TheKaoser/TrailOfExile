#pragma once

class Character;

// Base weapon. Subclasses only need to define their damage value;
// override Attack() if the weapon needs special behaviour (e.g. AoE, piercing).
class Weapon
{
protected:
	int damage;

public:
	explicit constexpr Weapon(int dmg) noexcept : damage(dmg) {}
	virtual ~Weapon() = default;

	virtual void Attack(Character* target) const;
	int GetDamage() const noexcept;
};

class Crossbow : public Weapon
{
public:
	constexpr Crossbow() noexcept : Weapon(20) {}
};

class Spear : public Weapon
{
public:
	constexpr Spear() noexcept : Weapon(15) {}
};
