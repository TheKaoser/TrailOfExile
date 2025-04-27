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

	virtual std::unique_ptr<State> GetNextState(Character& character, double randomValue) = 0;
	virtual void Enter(Character& character) {};
	virtual void Update(Character& character);
	bool IsFinished() const;
};

class IdleState : public State
{
public:
	IdleState();
	std::unique_ptr<State> GetNextState(Character& character, double randomValue) override;
	void Update(Character& character) override;
};

class DodgingState : public State
{
public:
	DodgingState();
	std::unique_ptr<State> GetNextState(Character& character, double randomValue) override;
};

class AttackingState : public State
{
public:
	AttackingState();
	std::unique_ptr<State> GetNextState(Character& character, double randomValue) override;
	void Enter(Character& character) override;
};

#endif // STATE_H
