#include "Character.h"

Character::Character(int initialHealth, double attackProb, double dodgeProb, const std::string& name, std::unique_ptr<Weapon> weapon)
	: health(initialHealth), attackProbability(attackProb), dodgeProbability(dodgeProb),
	characterName(name), weapon(std::move(weapon))
{
	state = std::make_unique<IdleState>();
}

void Character::NotifyObservers(Event event, std::optional<int> value, const std::string& detail) const
{
	for (Observer* observer : observers)
	{
		observer->OnNotify(event, characterName, value, detail);
	}
}

// Prevent duplicate subscriptions — same observer won't be added twice.
void Character::AddObserver(Observer* observer)
{
	if (std::find(observers.begin(), observers.end(), observer) == observers.end())
	{
		observers.push_back(observer);
	}
}

void Character::RemoveObserver(Observer* observer)
{
	observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Character::TakeDamage(int damage, bool piercing)
{
	// Piercing attacks bypass dodge entirely.
	if (!piercing && state->ResistsDamage())
	{
		NotifyObservers(Event::Dodge, std::nullopt, "an attack");
		return;
	}

	health = std::max(0, health - damage);
	NotifyObservers(Event::TakeDamage, health);

	if (health == 0)
	{
		NotifyObservers(Event::Die);
	}
}

int Character::GetHealth() const noexcept
{
	return health;
}

double Character::GetAttackProbability() const noexcept
{
	return attackProbability;
}

double Character::GetDodgeProbability() const noexcept
{
	return dodgeProbability;
}

const std::string& Character::GetName() const noexcept
{
	return characterName;
}

// Called once per tick by the GameManager. The RNG is stored temporarily so
// that Attack() can draw damage rolls without threading it through State.
void Character::Update(std::mt19937& rng, Character* opponent)
{
	activeRng = &rng;

	std::uniform_real_distribution<> dist(0.0, 1.0);
	double randomValue = dist(rng);

	std::unique_ptr<State> nextState = state->GetNextState(*this, randomValue);
	if (nextState)
	{
		state = std::move(nextState);
		state->Enter(*this, opponent);
		NotifyObservers(Event::StateChange, std::nullopt, state->GetName());
	}
	state->Update(*this);

	activeRng = nullptr;
}

const char* Character::GetWeaponName() const noexcept
{
	return weapon->GetName();
}

void Character::Attack(Character* opponent) const
{
	if (opponent && activeRng)
	{
		auto result = weapon->ComputeAttack(*activeRng);

		// Build a descriptive string for the log.
		std::string desc;
		if (result.critical)       desc = "Critical strike on ";
		else if (result.piercing)  desc = "Piercing shot on ";
		else                       desc = "Attacked ";
		desc += opponent->GetName();

		// Append any enchantment proc info (e.g. "(venom!)").
		if (!result.enchantEffect.empty())
		{
			desc += " " + result.enchantEffect;
		}

		NotifyObservers(Event::Attack, result.damage, desc);
		opponent->TakeDamage(result.damage, result.piercing);
	}
}

Huntress::Huntress(int hp, double atkProb, double dodgeProb, std::unique_ptr<Weapon> weapon)
	: Character(hp, atkProb, dodgeProb, "Huntress", std::move(weapon)) {}

Mercenary::Mercenary(int hp, double atkProb, double dodgeProb, std::unique_ptr<Weapon> weapon)
	: Character(hp, atkProb, dodgeProb, "Mercenary", std::move(weapon)) {}

Witch::Witch(int hp, double atkProb, double dodgeProb, std::unique_ptr<Weapon> weapon)
	: Character(hp, atkProb, dodgeProb, "Witch", std::move(weapon)) {}