#ifndef STATE_H
#define STATE_H

#include <memory>
#include <string>

class Character;

class State
{
protected:
	int duration;
	int elapsedTicks;

public:
	explicit State(int durationTicks);
	virtual ~State() = default;

	virtual void Enter(Character& character) {};
	virtual void HandleInput(Character& character, double randomValue) = 0;
	virtual void Update(Character& character);
	bool IsFinished() const;
};

class IdleState : public State
{
public:
	IdleState();
	void HandleInput(Character& character, double randomValue) override;
	void Update(Character& character) override;
};

class DodgingState : public State
{
public:
	DodgingState();
	void HandleInput(Character& character, double randomValue) override;
};

class AttackingState : public State
{
public:
	AttackingState();
	void Enter(Character& character) override;
	void HandleInput(Character& character, double randomValue) override;
};

#endif // STATE_H
