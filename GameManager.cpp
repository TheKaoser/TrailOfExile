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
		std::cout << "- " << character->GetName() << " (" << character->GetWeaponName() << ") with " << character->GetHealth() << " health.\n";
	}
	std::cout << "Let the combat begin!\n";
	std::cout << "---------------------\n\n";

	int tick = 1;
	do
	{
		std::cout << "--- Tick " << tick << " ---\n";
		Update(tick);
		std::cout << '\n';
		++tick;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	} while (!IsGameOver());

	auto winner = GetWinner();
	if (winner)
	{
		std::cout << winner->GetName() << " wins with " << winner->GetHealth() << " health remaining!\n";
	}
	else
	{
		std::cout << "No winner could be determined.\n";
	}
}

void GameManager::Update(int tick)
{
	// Each character targets the next one in the list (wraps around).
	// Skip characters that were knocked out earlier this tick.
	for (size_t i = 0; i < characters.size(); ++i)
	{
		if (characters[i]->GetHealth() <= 0) continue;

		size_t targetIndex = (i + 1) % characters.size();
		Character* opponent = characters[targetIndex].get();
		characters[i]->Update(gen, opponent);
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

