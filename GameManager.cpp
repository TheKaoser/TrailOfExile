#include "GameManager.h"
#include "Character.h"
#include <algorithm>
#include <iostream>
#include <thread>

GameManager::GameManager() : gen(std::random_device{}()) {}

GameManager& GameManager::GetInstance()
{
	static GameManager instance;
	return instance;
}

void GameManager::CreateCharacter(std::shared_ptr<Character> character)
{
	characters.push_back(std::move(character));
}

void GameManager::RunGame()
{
	std::cout << "The following characters are fighting:" << std::endl;
	for (const auto& character : characters)
	{
		std::cout << "- " << character->GetName() << " with " << character->GetHealth() << " health." << std::endl;
	}
	std::cout << "Let the combat begin!" << std::endl;
	std::cout << "---------------------\n" << std::endl;

	do
	{
		Update();
		std::cout << std::endl;
	} while (!GetWinner());
}

void GameManager::Update()
{
	if (characters.size() < 2)
	{
		throw std::runtime_error("Not enough characters to start the game. At least 2 characters are required.");
	}

	for (size_t i = 0; i < characters.size(); ++i)
	{
		size_t targetIndex = (i + 1) % characters.size();
		Character* opponent = characters[targetIndex].get();
		double randomValue = GetRandomDouble(0.0, 1.0);
		characters[i]->Update(randomValue, opponent);
	}

	CheckDefeatedCharacters();

	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void GameManager::CheckDefeatedCharacters()
{
	characters.erase(
		std::remove_if(
			characters.begin(),
			characters.end(),
			[](const std::shared_ptr<Character>& character)
			{
				return character->GetHealth() <= 0;
			}),
		characters.end());
}

std::shared_ptr<Character> GameManager::GetWinner() const
{
	if (characters.size() == 1)
	{
		return characters.front();
	}
	return nullptr; // No winner
}

double GameManager::GetRandomDouble(double min, double max)
{
	std::uniform_real_distribution<> dist(min, max);
	return dist(gen);
}