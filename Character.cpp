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

void Character::NotifyObservers(Event event, std::optional<int> value) const
{
	for (Observer* observer : observers)
	{
		observer->OnNotify(event, characterName, value);
	}
}

void Character::AddObserver(Observer* observer)
{
	if (std::find(observers.begin(), observers.end(), observer) == observers.end())
	{
		observers.push_back(observer);
	}
}

void Character::RemoveObserver(Observer* observer)
{
	observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Character::TakeDamage(int damage)
{
	if (state->ResistsDamage())
	{
		NotifyObservers(Event::Dodge);
		return;
	}

	health -= damage;
	if (health < 0) health = 0;
	NotifyObservers(Event::TakeDamage, health);

	if (health == 0)
	{
		NotifyObservers(Event::Die);
	}
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

void Character::Attack() const
{
	Character* opponent = GameManager::GetInstance()->GetOpponent(this);
	if (opponent)
	{
		int damage = weapon->GetDamage();
		NotifyObservers(Event::Attack, damage);
		weapon->Attack(characterName, opponent);
	}
}

Huntress::Huntress(std::unique_ptr<Weapon> weapon) : Character(100, 0.5, 0.4, "Huntress", std::move(weapon)) {}

Mercenary::Mercenary(std::unique_ptr<Weapon> weapon) : Character(120, 0.2, 0, "Mercenary", std::move(weapon)) {}