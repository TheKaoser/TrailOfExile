#include "ConfigLoader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

static std::string Trim(const std::string& str)
{
	size_t start = str.find_first_not_of(" \t\r\n");
	size_t end = str.find_last_not_of(" \t\r\n");
	return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

ConfigLoader::ConfigLoader(const std::string& filepath)
{
	std::ifstream file(filepath);
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open config file: " + filepath);
	}

	std::string line;
	std::string sectionType;
	std::string sectionName;

	while (std::getline(file, line))
	{
		line = Trim(line);
		if (line.empty() || line[0] == '#') continue;

		// Section header: [Type:Name]
		if (line.front() == '[' && line.back() == ']')
		{
			std::string header = line.substr(1, line.size() - 2);
			size_t colon = header.find(':');
			if (colon == std::string::npos)
			{
				throw std::runtime_error("Invalid section header (expected [Type:Name]): " + line);
			}
			sectionType = Trim(header.substr(0, colon));
			sectionName = Trim(header.substr(colon + 1));

			if (sectionType == "Weapon")
			{
				weapons[sectionName].name = sectionName;
			}
			else if (sectionType == "Character")
			{
				characters[sectionName].name = sectionName;
			}
			else if (sectionType == "Enchantment")
			{
				enchantments[sectionName].name = sectionName;
			}
			else
			{
				throw std::runtime_error("Unknown section type: " + sectionType);
			}
			continue;
		}

		// Key = Value
		size_t eq = line.find('=');
		if (eq == std::string::npos) continue;

		std::string key = Trim(line.substr(0, eq));
		std::string val = Trim(line.substr(eq + 1));

		if (sectionType == "Weapon")
		{
			auto& w = weapons[sectionName];
			if      (key == "BaseDamage")      w.baseDamage = std::stoi(val);
			else if (key == "DamageVariance")  w.damageVariance = std::stoi(val);
			else if (key == "CritChance")      w.critChance = std::stod(val);
			else if (key == "CritMultiplier")  w.critMultiplier = std::stod(val);
			else if (key == "PierceChance")    w.pierceChance = std::stod(val);
		}
		else if (sectionType == "Character")
		{
			auto& c = characters[sectionName];
			if      (key == "Health")              c.health = std::stoi(val);
			else if (key == "AttackProbability")   c.attackProbability = std::stod(val);
			else if (key == "DodgeProbability")    c.dodgeProbability = std::stod(val);
		}
		else if (sectionType == "Enchantment")
		{
			auto& e = enchantments[sectionName];
			if      (key == "BonusDamage") e.bonusDamage = std::stoi(val);
			else if (key == "ProcChance")  e.procChance = std::stod(val);
		}
	}
}

const WeaponConfig& ConfigLoader::GetWeapon(const std::string& name) const
{
	auto it = weapons.find(name);
	if (it == weapons.end())
	{
		throw std::runtime_error("Weapon not found in config: " + name);
	}
	return it->second;
}

const CharacterConfig& ConfigLoader::GetCharacter(const std::string& name) const
{
	auto it = characters.find(name);
	if (it == characters.end())
	{
		throw std::runtime_error("Character not found in config: " + name);
	}
	return it->second;
}

const EnchantmentConfig& ConfigLoader::GetEnchantment(const std::string& name) const
{
	auto it = enchantments.find(name);
	if (it == enchantments.end())
	{
		throw std::runtime_error("Enchantment not found in config: " + name);
	}
	return it->second;
}
