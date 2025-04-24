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

void IdleState::Update(Character& character)
{
	std::cout << character.GetName() << " does nothing." << std::endl;
}

void IdleState::HandleInput(Character& character, double randomValue)
{
	if (randomValue < character.GetAttackProbability())
	{
		character.ChangeState(std::make_unique<AttackingState>());
	}
	else if (randomValue < character.GetAttackProbability() + character.GetDodgeProbability())
	{
		character.ChangeState(std::make_unique<DodgingState>());
		std::cout << character.GetName() << " is dodging." << std::endl;
	}
}

DodgingState::DodgingState() : State(1) {}

void DodgingState::HandleInput(Character& character, double randomValue)
{
	if (IsFinished())
	{
		character.ChangeState(std::make_unique<IdleState>());
	}
}

AttackingState::AttackingState() : State(2) {}

void AttackingState::Enter(Character& character)
{
	character.Attack(character);
}

void AttackingState::HandleInput(Character& character, double randomValue)
{
	if (IsFinished())
	{
		character.ChangeState(std::make_unique<IdleState>());
	}
	else if (randomValue < character.GetDodgeProbability())
	{
		character.ChangeState(std::make_unique<DodgingState>());
		std::cout << character.GetName() << " canceled the attacking animation and is dodging." << std::endl;
	}
}
