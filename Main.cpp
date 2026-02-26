#include "GameManager.h"
#include "Logger.h"
#include "Character.h"
#include <iostream>

int main()
{
	try
	{
		GameManager& gameManager = GameManager::GetInstance();

		// Logger lives on the stack — it just needs to outlive the characters.
		Logger logger;

		auto huntress = std::make_shared<Huntress>(std::make_unique<Spear>());
		auto mercenary = std::make_shared<Mercenary>(std::make_unique<Crossbow>());

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
