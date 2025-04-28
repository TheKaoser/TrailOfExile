#include "GameManager.h"
#include "Character.h"
#include <iostream>
#include <thread>

GameManager::GameManager() : opponentsNeedUpdate(false), gen(std::random_device{}()), dis(0.0, 1.0) {}

GameManager* GameManager::GetInstance()
{
	static GameManager instance;
	return &instance;
}

void GameManager::CreateCharacter(std::shared_ptr<Character> character)
{
	characters.push_back(character);
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
		opponents[characters[i].get()] = characters[targetIndex].get();
	}

	for (const auto& character : characters)
	{
		character->Update();
	}
	CheckDefeatedCharacters();

	std::this_thread::sleep_for(std::chrono::seconds(1));
}

Character* GameManager::GetOpponent(const Character* character) const
{
	if (opponentsNeedUpdate)
	{
		RecalculateOpponents();
		opponentsNeedUpdate = false;
	}

	auto it = opponents.find(const_cast<Character*>(character));
	if (it != opponents.end())
	{
		return it->second;
	}
	return nullptr;
}

void GameManager::RecalculateOpponents() const
{
	opponents.clear(); // Clear the existing map
	for (size_t i = 0; i < characters.size(); ++i)
	{
		size_t targetIndex = (i + 1) % characters.size();
		opponents[characters[i].get()] = characters[targetIndex].get();
	}
}

void GameManager::CheckDefeatedCharacters()
{
	characters.erase(
		std::remove_if(
			characters.begin(),
			characters.end(),
			[&](const std::shared_ptr<Character>& character)
			{
				if (character->GetHealth() <= 0)
				{
					opponentsNeedUpdate = true;
					return true; // Mark for removal
				}
				return false; // Keep in the list
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
	std::uniform_real_distribution<> customDis(min, max);
	return customDis(gen);
}