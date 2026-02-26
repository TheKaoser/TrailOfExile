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
	if (characters.size() < 2)
	{
		throw std::runtime_error("Not enough characters to start the game. At least 2 characters are required.");
	}

	std::cout << "The following characters are fighting:\n";
	for (const auto& character : characters)
	{
		std::cout << "- " << character->GetName() << " with " << character->GetHealth() << " health.\n";
	}
	std::cout << "Let the combat begin!\n";
	std::cout << "---------------------\n\n";

	do
	{
		Update();
		std::cout << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(1));
	} while (!IsGameOver());
}

void GameManager::Update()
{
	// Each character targets the next one in the list (wraps around).
	// Skip characters that were knocked out earlier this tick.
	for (size_t i = 0; i < characters.size(); ++i)
	{
		if (characters[i]->GetHealth() <= 0) continue;

		size_t targetIndex = (i + 1) % characters.size();
		Character* opponent = characters[targetIndex].get();
		double randomValue = GetRandomDouble(0.0, 1.0);
		characters[i]->Update(randomValue, opponent);
	}

	CheckDefeatedCharacters();
}

// Erase-remove idiom — drop anyone at 0 hp after all characters have acted.
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

bool GameManager::IsGameOver() const noexcept
{
	return characters.size() <= 1;
}

std::shared_ptr<Character> GameManager::GetWinner() const noexcept
{
	if (characters.size() == 1)
	{
		return characters.front();
	}
	return nullptr;
}

double GameManager::GetRandomDouble(double min, double max)
{
	std::uniform_real_distribution<> dist(min, max);
	return dist(gen);
}