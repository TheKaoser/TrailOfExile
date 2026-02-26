#pragma once

#include <string>
#include <unordered_map>

struct WeaponConfig
{
	std::string name;
	int baseDamage = 0;
	int damageVariance = 0;
	double critChance = 0.0;
	double critMultiplier = 1.0;
	double pierceChance = 0.0;
};

struct CharacterConfig
{
	std::string name;
	int health = 0;
	double attackProbability = 0.0;
	double dodgeProbability = 0.0;
};

// Reads an INI-style config file and exposes weapon/character definitions.
// Keeps game balance data out of the source code so designers can iterate
// without recompiling.
class ConfigLoader
{
public:
	explicit ConfigLoader(const std::string& filepath);

	const WeaponConfig& GetWeapon(const std::string& name) const;
	const CharacterConfig& GetCharacter(const std::string& name) const;

private:
	std::unordered_map<std::string, WeaponConfig> weapons;
	std::unordered_map<std::string, CharacterConfig> characters;
};
