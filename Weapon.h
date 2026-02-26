#ifndef WEAPON_H
#define WEAPON_H

class Character;

class Weapon
{
protected:
	int damage;

public:
	explicit Weapon(int dmg);
	virtual ~Weapon() = default;

	virtual void Attack(Character* target) const;
	int GetDamage() const;
};

class Crossbow : public Weapon
{
public:
	Crossbow();
};

class Spear : public Weapon
{
public:
	Spear();
};

#endif // WEAPON_H
