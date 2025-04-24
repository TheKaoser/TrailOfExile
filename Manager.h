#ifndef MANAGER_H
#define MANAGER_H

#include <vector>
#include <memory>
#include <unordered_map>

class Character;

class Manager
{
private:
	std::vector<std::shared_ptr<Character>> characters;
	std::unordered_map<Character*, Character*> opponents;

	Manager();

public:
	static Manager* GetInstance();
	void CreateCharacter(std::shared_ptr<Character> character);
	void RunGame();
	void Update();
	Character* GetOpponent(Character* character) const;
	void CleanCharacters();
	std::shared_ptr<Character> GetWinner() const;
};

#endif // MANAGER_H
