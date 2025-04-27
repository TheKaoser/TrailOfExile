#ifndef GameManager_H
#define GameManager_H

#include <vector>
#include <memory>
#include <unordered_map>
#include <random>

class Character;

class GameManager
{
private:
	std::vector<std::shared_ptr<Character>> characters;
	mutable std::unordered_map<Character*, Character*> opponents;
	mutable bool opponentsNeedUpdate;

	std::mt19937 gen;
	std::uniform_real_distribution<> dis;

	void RecalculateOpponents() const;

	GameManager();

public:
	static GameManager* GetInstance();
	void CreateCharacter(std::shared_ptr<Character> character);
	void RunGame();
	void Update();
	Character* GetOpponent(const Character* character) const;
	void CheckDefeatedCharacters();
	std::shared_ptr<Character> GetWinner() const;

	double GetRandomDouble(double min = 0.0, double max = 1.0);
};

#endif // GameManager_H
