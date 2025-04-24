#ifndef CHARACTER_H
#define CHARACTER_H

#include <memory>
#include <string>
#include "State.h"
#include "Weapon.h"
#include <random>

class Manager;

class Character
{
protected:
	int health;
	std::unique_ptr<State> state;
	double attackProbability;
	double dodgeProbability;
	std::string characterName;

	// Random number generator
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_real_distribution<> dis;

public:
	explicit Character(int initialHealth, double attackProb, double dodgeProb, const std::string& name);
	virtual ~Character() = default;

	virtual void Attack(Character& target) const = 0;
	void TakeDamage(int damage);
	int GetHealth() const;
	double GetAttackProbability() const;
	double GetDodgeProbability() const;
	const std::string& GetName() const;
	void Update();
	void ChangeState(std::unique_ptr<State> newState);
	State* GetState() const;
};

class Huntress : public Character
{
private:
	std::unique_ptr<Weapon> weapon;

public:
	Huntress();
	void Attack(Character& target) const override;
};

class Mercenary : public Character
{
private:
	std::unique_ptr<Weapon> weapon;

public:
	Mercenary();
	void Attack(Character& target) const override;
};

#endif // CHARACTER_H
