#ifndef CHARACTER_H
#define CHARACTER_H

#include <memory>
#include <string>
#include "State.h"
#include "Weapon.h"

class GameManager;

class Character
{
protected:
	int health;
	std::unique_ptr<State> state;
	std::unique_ptr<Weapon> weapon;
	double attackProbability;
	double dodgeProbability;
	std::string characterName;

public:
	explicit Character(int initialHealth, double attackProb, double dodgeProb, const std::string& name, std::unique_ptr<Weapon> weapon);
	virtual ~Character() = default;

	virtual void Attack(Character& target) const = 0;
	void TakeDamage(int damage);
	int GetHealth() const;
	double GetAttackProbability() const;
	double GetDodgeProbability() const;
	const std::string& GetName() const;
	void Update();
};

class Huntress : public Character
{
public:
	Huntress(std::unique_ptr<Weapon> weapon);
	void Attack(Character& target) const override;
};

class Mercenary : public Character
{
public:
	Mercenary(std::unique_ptr<Weapon> weapon);
	void Attack(Character& target) const override;
};

#endif // CHARACTER_H
