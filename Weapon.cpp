#include "Weapon.h"
#include "Character.h"

Weapon::Weapon(int dmg) : damage(dmg) {}

int Weapon::GetDamage() const
{
	return damage;
}

void Weapon::Attack(Character* target) const
{
	if (target)
	{
		target->TakeDamage(damage);
	}
}

Crossbow::Crossbow() : Weapon(20) {}

Spear::Spear() : Weapon(15) {}
