#include "Weapon.h"
#include "Character.h"
#include <iostream>

Weapon::Weapon(int dmg) : damage(dmg) {}

int Weapon::GetDamage() const
{
	return damage;
}

Crossbow::Crossbow() : Weapon(20) {}

void Crossbow::Attack(const std::string& attackerName, Character* target) const
{
	if (target)
	{
		target->TakeDamage(damage);
	}
}

Spear::Spear() : Weapon(15) {}

void Spear::Attack(const std::string& attackerName, Character* target) const
{
	if (target)
	{
		target->TakeDamage(damage);
	}
}
