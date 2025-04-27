#include "Character.h"
#include "GameManager.h"
#include <iostream>

Character::Character(int initialHealth, double attackProb, double dodgeProb, const std::string& name, std::unique_ptr<Weapon> weapon)
	: health(initialHealth), attackProbability(attackProb), dodgeProbability(dodgeProb),
	characterName(name), weapon(std::move(weapon))
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
	double randomValue = GameManager::GetInstance()->GetRandomDouble(0.0, 1.0);
	std::unique_ptr<State> nextState = state->GetNextState(*this, randomValue);
	if (nextState)
	{
		state = std::move(nextState);
		state->Enter(*this);
	}
	state->Update(*this);
}

Huntress::Huntress(std::unique_ptr<Weapon> weapon) : Character(100, 0.5, 0.3, "Huntress", std::move(weapon)) {}

void Huntress::Attack(Character& target) const
{
	Character* opponent = GameManager::GetInstance()->GetOpponent(this);
	if (opponent)
	{
		weapon->Attack(characterName, opponent);
	}
}

Mercenary::Mercenary(std::unique_ptr<Weapon> weapon) : Character(120, 0.2, 0, "Mercenary", std::move(weapon)) {}

void Mercenary::Attack(Character& target) const
{
	Character* opponent = GameManager::GetInstance()->GetOpponent(this);
	if (opponent)
	{
		weapon->Attack(characterName, opponent);
	}
}
