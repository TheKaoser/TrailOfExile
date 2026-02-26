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

		const auto& spearCfg = config.GetWeapon("Spear");
		const auto& crossbowCfg = config.GetWeapon("Crossbow");
		const auto& huntressCfg = config.GetCharacter("Huntress");
		const auto& mercenaryCfg = config.GetCharacter("Mercenary");

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

		// Subscribe the logger so we get combat output.
		huntress->AddObserver(&logger);
		mercenary->AddObserver(&logger);

		gameManager.CreateCharacter(huntress);
		gameManager.CreateCharacter(mercenary);

		gameManager.RunGame();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return 0;
}
