#ifndef WEAPON_H
#define WEAPON_H

#include <string>

class Character;

class Weapon
{
protected:
	int damage;

public:
	explicit Weapon(int dmg);
	virtual ~Weapon() = default;

	virtual void Attack(const std::string& attackerName, Character* target) const = 0;
	int GetDamage() const;
};

class Crossbow : public Weapon
{
public:
	Crossbow();
	void Attack(const std::string& attackerName, Character* target) const override;
};

class Spear : public Weapon
{
public:
	Spear();
	void Attack(const std::string& attackerName, Character* target) const override;
};

#endif // WEAPON_H
