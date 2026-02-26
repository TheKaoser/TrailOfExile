#ifndef CHARACTER_H
#define CHARACTER_H

#include <memory>
#include <string>
#include <vector>  
#include <optional>
#include "State.h"
#include "Weapon.h"
#include "Observer.h"

class Character
{
protected:
	int health;
	std::unique_ptr<State> state;
	std::unique_ptr<Weapon> weapon;
	double attackProbability;
	double dodgeProbability;
	std::string characterName;

	std::vector<Observer*> observers;
	void NotifyObservers(Event event, std::optional<int> value = std::nullopt) const;

public:
	explicit Character(int initialHealth, double attackProb, double dodgeProb, const std::string& name, std::unique_ptr<Weapon> weapon);
	virtual ~Character() = default;

	virtual void Attack(Character* opponent) const;
	void TakeDamage(int damage);
	int GetHealth() const;
	double GetAttackProbability() const;
	double GetDodgeProbability() const;
	const std::string& GetName() const;
	void Update(double randomValue, Character* opponent);

	void AddObserver(Observer* observer);
	void RemoveObserver(Observer* observer);
};

class Huntress : public Character
{
public:
	Huntress(std::unique_ptr<Weapon> weapon);
};

class Mercenary : public Character
{
public:
	Mercenary(std::unique_ptr<Weapon> weapon);
};

#endif // CHARACTER_H
