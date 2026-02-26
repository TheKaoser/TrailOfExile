#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <vector>
#include <memory>
#include <random>

class Character;

class GameManager
{
private:
	std::vector<std::shared_ptr<Character>> characters;
	std::mt19937 gen;

	GameManager();

public:
	static GameManager& GetInstance();
	void CreateCharacter(std::shared_ptr<Character> character);
	void RunGame();
	void Update();
	void CheckDefeatedCharacters();
	std::shared_ptr<Character> GetWinner() const;

	double GetRandomDouble(double min = 0.0, double max = 1.0);
};

#endif // GAME_MANAGER_H
