#include "GameManager.h"
#include "Logger.h"
#include "Character.h"
#include <iostream>

int main()
{
	try
	{
		GameManager* GameManager = GameManager::GetInstance();
		Logger logger;

		auto huntress = std::make_shared<Huntress>(std::make_unique<Spear>());
		auto mercenary = std::make_shared<Mercenary>(std::make_unique<Crossbow>());

		huntress->AddObserver(&logger);
		mercenary->AddObserver(&logger);

		GameManager->CreateCharacter(huntress);
		GameManager->CreateCharacter(mercenary);

		GameManager->RunGame();

		auto winner = GameManager->GetWinner();
		if (winner)
		{
			std::cout << "The winner is " << winner->GetName() << " with " << winner->GetHealth() << " health remaining!" << std::endl;
		}
		else
		{
			std::cout << "No winner could be determined." << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
