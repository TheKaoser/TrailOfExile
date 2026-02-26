#include "Character.h"

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

// Prevent duplicate subscriptions — same observer won't be added twice.
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
	// The current state decides whether damage is absorbed (e.g. dodging).
	if (state->ResistsDamage())
	{
		NotifyObservers(Event::Dodge);
		return;
	}

	health = std::max(0, health - damage);
	NotifyObservers(Event::TakeDamage, health);

	if (health == 0)
	{
		NotifyObservers(Event::Die);
	}
}

int Character::GetHealth() const noexcept
{
	return health;
}

double Character::GetAttackProbability() const noexcept
{
	return attackProbability;
}

double Character::GetDodgeProbability() const noexcept
{
	return dodgeProbability;
}

const std::string& Character::GetName() const noexcept
{
	return characterName;
}

// Called once per tick by the GameManager. The random value drives the
// state-machine transition so that randomness is injected from outside.
void Character::Update(double randomValue, Character* opponent)
{
	std::unique_ptr<State> nextState = state->GetNextState(*this, randomValue);
	if (nextState)
	{
		state = std::move(nextState);
		state->Enter(*this, opponent);
		NotifyObservers(Event::StateChange);
	}
	state->Update(*this);
}

void Character::Attack(Character* opponent) const
{
	if (opponent)
	{
		int damage = weapon->GetDamage();
		NotifyObservers(Event::Attack, damage);
		weapon->Attack(opponent);
	}
}

// Huntress — 100 hp, 50% attack, 40% dodge
Huntress::Huntress(std::unique_ptr<Weapon> weapon) : Character(100, 0.5, 0.4, "Huntress", std::move(weapon)) {}

// Mercenary — 120 hp, 20% attack, 0% dodge
Mercenary::Mercenary(std::unique_ptr<Weapon> weapon) : Character(120, 0.2, 0, "Mercenary", std::move(weapon)) {}