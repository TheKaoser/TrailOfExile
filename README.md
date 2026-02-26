# Trail of Exile

A tick-based arena combat simulation where three characters - each from a Path of Exile 2 class with a unique weapon and stat spread - fight until only one remains. Built as a portfolio piece to demonstrate clean C++17, data-driven design, and a handful of classic design patterns working together.

<br>

## Characters

| Character | Weapon | Role |
|-----------|--------|------|
| **Huntress** | Spear | Agile fighter. Good attack and dodge rates, lower health. Spear crits deal double damage. |
| **Mercenary** | Crossbow | Tanky bruiser. Large health pool, slow attacks, cannot dodge. Crossbow bolts can pierce through dodge. |
| **Witch** | Venomous Flaming Staff | Glass cannon. High attack rate, moderate dodge, low health. Staff is enchanted with flat fire damage and a chance-based venom proc. |

<br>

## Design Patterns

**Singleton** - One GameManager instance owns the character roster and drives the tick loop.

**State Machine** - Each character runs through IdleState, DodgingState, and AttackingState. Transitions are probability-driven, keeping all state logic self-contained.

**Observer** - Logger subscribes to each character and reacts to combat events (Attack, TakeDamage, Dodge, Die). No game logic lives in the logger.

**Component** - Weapons are modular objects attached to characters. Swapping or extending them requires no changes to Character.

**Decorator** - Weapon enchantments wrap a base weapon and layer extra behaviour on top. The Witch's staff is a VenomEnchantment wrapping a FlamingEnchantment wrapping a plain Staff - each decorator adds its modifier and delegates the rest down the chain. New enchantments can be composed freely without modifying existing classes.

**Polymorphism** - Character and Weapon both have subclass hierarchies. Adding a new class or weapon type means extending the hierarchy, not touching existing code.

<br>

## Data-Driven Config

All stats live in GameConfig.cfg - no recompilation needed to rebalance:

```ini
[Weapon:Spear]
BaseDamage = 12
DamageVariance = 6
CritChance = 0.25
CritMultiplier = 2.0

[Enchantment:Venom]
ProcChance = 0.35
BonusDamage = 8

[Character:Witch]
Health = 80
AttackProbability = 0.6
DodgeProbability = 0.2
```

<br>

## Sample Output

```
The following characters are fighting:
- Huntress (Spear) with 100 health.
- Mercenary (Crossbow) with 120 health.
- Witch (Venomous Flaming Staff) with 80 health.
Let the combat begin!
---------------------

--- Tick 3 ---
  [COMBAT] Huntress: Attacked Mercenary for 18 damage.
  [COMBAT] Mercenary: Took damage. Health: 102
  [COMBAT] Mercenary: Attacked Witch for 22 damage.
  [COMBAT] Witch: Took damage. Health: 58
  [COMBAT] Witch: Attacked Huntress (venom!) for 28 damage.
  [COMBAT] Huntress: Took damage. Health: 72

--- Tick 6 ---
  [COMBAT] Witch: Attacked Huntress for 20 damage.
  [COMBAT] Huntress: Dodged an attack.

--- Tick 19 ---
  [COMBAT] Mercenary: Piercing shot on Witch for 23 damage.
  [COMBAT] Witch: Took damage. Health: 0
  [DEATH]  Witch: Has been defeated.

--- Tick 44 ---
  [COMBAT] Huntress: Critical strike on Mercenary for 26 damage.
  [COMBAT] Mercenary: Took damage. Health: 0
  [DEATH]  Mercenary: Has been defeated.

Huntress wins with 15 health remaining!
```

<br>

## Build

**MSBuild (Visual Studio 2022)**
```
MSBuild CodingSample.sln /p:Configuration=Debug /p:Platform=x64
x64\Debug\CodingSample.exe
```

**CMake**
```
cmake -B build
cmake --build build
```

> GameConfig.cfg must be in the same directory as the executable.
