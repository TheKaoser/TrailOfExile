#pragma once

#include <vector>
#include <memory>
#include <random>

class Character;

// Singleton that owns the character roster and drives the main game loop.
// Each tick it rolls random values, passes them to characters, and cleans
// up anyone who has been knocked out.
class GameManager
{
private:
	std::vector<std::shared_ptr<Character>> characters;
	std::mt19937 gen;

	GameManager();

public:
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;

	static GameManager& GetInstance();
	void CreateCharacter(std::shared_ptr<Character> character);
	void RunGame();
	void Update(int tick);
	bool IsGameOver() const noexcept;
	std::shared_ptr<Character> GetWinner() const noexcept;

	double GetRandomDouble(double min = 0.0, double max = 1.0);

private:
	void CheckDefeatedCharacters();
};
