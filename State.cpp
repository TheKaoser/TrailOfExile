#include "State.h"
#include "Character.h"

void State::Update(Character& character)
{
	++elapsedTicks;
}

bool State::IsFinished() const noexcept
{
	return elapsedTicks >= duration;
}

// Idle: pick action based on probability bands
// [0 .. attackProb) -> attack, [attackProb .. attackProb+dodgeProb) -> dodge, else stay idle
std::unique_ptr<State> IdleState::GetNextState(Character& character, double randomValue)
{
	if (randomValue < character.GetAttackProbability())
	{
		return std::make_unique<AttackingState>();
	}
	else if (randomValue < character.GetAttackProbability() + character.GetDodgeProbability())
	{
		return std::make_unique<DodgingState>();
	}
	return nullptr;
}

std::unique_ptr<State> DodgingState::GetNextState(Character& character, double randomValue)
{
	if (IsFinished())
	{
		return std::make_unique<IdleState>();
	}
	return nullptr;
}

void AttackingState::Enter(Character& character, Character* opponent)
{
	character.Attack(opponent);
}

// While attacking, the character can still roll a dodge to cancel the remaining wind-down.
std::unique_ptr<State> AttackingState::GetNextState(Character& character, double randomValue)
{
	if (IsFinished())
	{
		return std::make_unique<IdleState>();
	}
	else if (randomValue < character.GetDodgeProbability())
	{
		return std::make_unique<DodgingState>();
	}
	return nullptr;
}
