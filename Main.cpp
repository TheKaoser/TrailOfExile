#include "GameManager.h"
#include "Logger.h"
#include "Character.h"
#include "ConfigLoader.h"
#include <iostream>

int main()
{
	try
	{
		ConfigLoader config("GameConfig.cfg");

		const auto& spearCfg     = config.GetWeapon("Spear");
		const auto& crossbowCfg  = config.GetWeapon("Crossbow");
		const auto& staffCfg     = config.GetWeapon("Staff");
		const auto& flamingCfg   = config.GetEnchantment("Flaming");
		const auto& venomCfg     = config.GetEnchantment("Venom");
		const auto& huntressCfg  = config.GetCharacter("Huntress");
		const auto& mercenaryCfg = config.GetCharacter("Mercenary");
		const auto& witchCfg     = config.GetCharacter("Witch");

		GameManager& gameManager = GameManager::GetInstance();

		// Logger lives on the stack — it just needs to outlive the characters.
		Logger logger;

		auto huntress = std::make_shared<Huntress>(
			huntressCfg.health, huntressCfg.attackProbability, huntressCfg.dodgeProbability,
			std::make_unique<Spear>(spearCfg.baseDamage, spearCfg.damageVariance,
				spearCfg.critChance, spearCfg.critMultiplier));

		auto mercenary = std::make_shared<Mercenary>(
			mercenaryCfg.health, mercenaryCfg.attackProbability, mercenaryCfg.dodgeProbability,
			std::make_unique<Crossbow>(crossbowCfg.baseDamage, crossbowCfg.damageVariance,
				crossbowCfg.pierceChance));

		// Decorators compose: the Witch's staff deals fire damage and has a
		// chance to apply venom — each enchantment wraps the previous weapon.
		auto witchWeapon = std::make_unique<VenomEnchantment>(
			std::make_unique<FlamingEnchantment>(
				std::make_unique<Staff>(staffCfg.baseDamage, staffCfg.damageVariance),
				flamingCfg.bonusDamage),
			venomCfg.procChance, venomCfg.bonusDamage);

		auto witch = std::make_shared<Witch>(
			witchCfg.health, witchCfg.attackProbability, witchCfg.dodgeProbability,
			std::move(witchWeapon));

		// Subscribe the logger so we get combat output.
		huntress->AddObserver(&logger);
		mercenary->AddObserver(&logger);
		witch->AddObserver(&logger);

		gameManager.CreateCharacter(huntress);
		gameManager.CreateCharacter(mercenary);
		gameManager.CreateCharacter(witch);

		gameManager.RunGame();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return 0;
}
