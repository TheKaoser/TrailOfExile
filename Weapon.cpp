#include "Weapon.h"
#include "Character.h"

int Weapon::GetDamage() const noexcept
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
