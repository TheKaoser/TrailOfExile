#pragma once

#include <algorithm>
#include <memory>
#include <random>
#include <string>
#include <vector>
#include <optional>
#include "State.h"
#include "Weapon.h"
#include "Observer.h"

// Base class for every combatant. Owns a weapon and a state-machine that
// drives its behaviour each tick. Observers are notified of every gameplay
// event so the game logic stays decoupled from presentation.
class Character
{
protected:
	int health;
	std::unique_ptr<State> state;
	std::unique_ptr<Weapon> weapon;
	double attackProbability;
	double dodgeProbability;
	std::string characterName;

	// Set during Update() so Attack() can draw random values without
	// threading the RNG parameter through the entire State hierarchy.
	std::mt19937* activeRng = nullptr;

	std::vector<Observer*> observers;
	void NotifyObservers(Event event, std::optional<int> value = std::nullopt, const std::string& detail = "") const;

public:
	Character(int initialHealth, double attackProb, double dodgeProb, const std::string& name, std::unique_ptr<Weapon> weapon);
	virtual ~Character() = default;

	virtual void Attack(Character* opponent) const;
	void TakeDamage(int damage, bool piercing = false);
	int GetHealth() const noexcept;
	double GetAttackProbability() const noexcept;
	double GetDodgeProbability() const noexcept;
	const std::string& GetName() const noexcept;
	void Update(std::mt19937& rng, Character* opponent);

	const char* GetWeaponName() const noexcept;

	void AddObserver(Observer* observer);
	void RemoveObserver(Observer* observer);
};

// High agility class — good attack and dodge rates but lower health.
class Huntress : public Character
{
public:
	Huntress(int hp, double atkProb, double dodgeProb, std::unique_ptr<Weapon> weapon);
};

// Tanky class — large health pool, slower attacks, cannot dodge.
class Mercenary : public Character
{
public:
	Mercenary(int hp, double atkProb, double dodgeProb, std::unique_ptr<Weapon> weapon);
};

// Glass cannon — low health, high attack frequency, moderate dodge.
class Witch : public Character
{
public:
	Witch(int hp, double atkProb, double dodgeProb, std::unique_ptr<Weapon> weapon);
};
