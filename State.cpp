#include "State.h"
#include "Character.h"
#include <iostream>

State::State(int durationTicks) : duration(durationTicks), elapsedTicks(0) {}

void State::Update(Character& character)
{
	++elapsedTicks;
}

bool State::IsFinished() const
{
	return elapsedTicks >= duration;
}

IdleState::IdleState() : State(0) {}

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

DodgingState::DodgingState() : State(1) {}

std::unique_ptr<State> DodgingState::GetNextState(Character& character, double randomValue)
{
	if (IsFinished())
	{
		return std::make_unique<IdleState>();
	}
	return nullptr;
}

AttackingState::AttackingState() : State(2) {}

void AttackingState::Enter(Character& character)
{
	character.Attack();
}

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
