#include "Manager.h"
#include "Character.h"
#include <iostream>

int main()
{
	try
	{
		Manager* manager = Manager::GetInstance();

		auto huntress = std::make_shared<Huntress>();
		auto mercenary = std::make_shared<Mercenary>();

		manager->CreateCharacter(huntress);
		manager->CreateCharacter(mercenary);

		manager->RunGame();

		auto winner = manager->GetWinner();
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
