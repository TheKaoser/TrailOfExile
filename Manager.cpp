#include "Manager.h"
#include "Character.h"
#include <iostream>
#include <thread>

Manager::Manager() = default;

Manager* Manager::GetInstance()
{
	static Manager instance;
	return &instance;
}

void Manager::CreateCharacter(std::shared_ptr<Character> character)
{
	characters.push_back(character);
}

void Manager::RunGame()
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

void Manager::Update()
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
	CleanCharacters();

	std::this_thread::sleep_for(std::chrono::seconds(2));
}

Character* Manager::GetOpponent(Character* character) const
{
	auto it = opponents.find(character);
	if (it != opponents.end())
	{
		return it->second;
	}
	return nullptr;
}

void Manager::CleanCharacters()
{
	characters.erase(
		std::remove_if(
			characters.begin(),
			characters.end(),
			[&](const std::shared_ptr<Character>& character)
			{
				if (character->GetHealth() <= 0)
				{
					std::cout << character->GetName() << " has been defeated and is removed from the game." << std::endl;
					return true; // Mark for removal
				}
				return false; // Keep in the list
			}),
		characters.end());
}

std::shared_ptr<Character> Manager::GetWinner() const
{
	if (characters.size() == 1)
	{
		return characters.front();
	}
	return nullptr; // No winner
}
