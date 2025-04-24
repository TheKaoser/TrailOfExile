#include "Character.h"
#include "Manager.h"
#include <iostream>

Character::Character(int initialHealth, double attackProb, double dodgeProb, const std::string& name)
	: health(initialHealth), attackProbability(attackProb), dodgeProbability(dodgeProb),
	characterName(name), gen(rd()), dis(0.0, 1.0)
{
	state = std::make_unique<IdleState>();
	state->Enter(*this);
}

void Character::TakeDamage(int damage)
{
	if (dynamic_cast<DodgingState*>(state.get()))
	{
		std::cout << characterName << " dodged the attack and took no damage!" << std::endl;
		return;
	}

	health -= damage;
	if (health < 0) health = 0;
	std::cout << characterName << " took " << damage << " damage. Remaining health: " << health << std::endl;
}

int Character::GetHealth() const
{
	return health;
}

double Character::GetAttackProbability() const
{
	return attackProbability;
}

double Character::GetDodgeProbability() const
{
	return dodgeProbability;
}

const std::string& Character::GetName() const
{
	return characterName;
}

void Character::Update()
{
	double randomValue = dis(gen);
	state->HandleInput(*this, randomValue);
	state->Update(*this);
}

void Character::ChangeState(std::unique_ptr<State> newState)
{
	state = std::move(newState);
	state->Enter(*this);
}

State* Character::GetState() const
{
	return state.get();
}

Huntress::Huntress() : Character(100, 0.5, 0.3, "Huntress"), weapon(std::make_unique<Spear>()) {}

void Huntress::Attack(Character& target) const
{
	Character* opponent = Manager::GetInstance()->GetOpponent(const_cast<Huntress*>(this));
	if (opponent)
	{
		weapon->Attack(characterName, opponent);
	}
}

Mercenary::Mercenary() : Character(120, 0.2, 0, "Mercenary"), weapon(std::make_unique<Crossbow>()) {}

void Mercenary::Attack(Character& target) const
{
	Character* opponent = Manager::GetInstance()->GetOpponent(const_cast<Mercenary*>(this));
	if (opponent)
	{
		weapon->Attack(characterName, opponent);
	}
}
