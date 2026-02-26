#pragma once

#include <memory>
#include <string>

class Character;

// Each state has a tick-based duration. Characters transition between states
// based on probability rolls (see GetNextState). Override Enter() to fire
// one-shot logic when the state begins (e.g. dealing damage on attack).
class State
{
protected:
	int duration;
	int elapsedTicks;

public:
	explicit constexpr State(int durationTicks) noexcept : duration(durationTicks), elapsedTicks(0) {}
	virtual ~State() = default;

	virtual const char* GetName() const noexcept = 0;
	virtual std::unique_ptr<State> GetNextState(Character& character, double randomValue) = 0;
	virtual void Enter(Character& character, Character* opponent = nullptr) {}
	virtual void Update(Character& character);
	bool IsFinished() const noexcept;
	virtual bool ResistsDamage() const noexcept { return false; }
};

// Waiting for the next action. Duration is 0, so a transition is picked immediately.
class IdleState : public State
{
public:
	constexpr IdleState() noexcept : State(0) {}
	const char* GetName() const noexcept override { return "Idle"; }
	std::unique_ptr<State> GetNextState(Character& character, double randomValue) override;
};

// Actively evading. While in this state, all incoming damage is negated.
class DodgingState : public State
{
public:
	constexpr DodgingState() noexcept : State(1) {}
	const char* GetName() const noexcept override { return "Dodging"; }
	std::unique_ptr<State> GetNextState(Character& character, double randomValue) override;
	bool ResistsDamage() const noexcept override { return true; }
};

// Performing an attack. Damage is dealt on Enter(), then the character
// is locked into the animation for the remaining ticks.
class AttackingState : public State
{
public:
	constexpr AttackingState() noexcept : State(2) {}
	const char* GetName() const noexcept override { return "Attacking"; }
	std::unique_ptr<State> GetNextState(Character& character, double randomValue) override;
	void Enter(Character& character, Character* opponent) override;
};
