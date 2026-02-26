# Trail of Exile
Trail of Exile is a tick-based arena combat simulation where three characters - each with a unique class, weapon, and stat spread - fight until only one is left standing. It was created to showcase clean C++17 code, solid architecture, data-driven design, and strong use of object-oriented programming principles.

<br>

**Characters**

- **Huntress** - High agility, armed with a Spear that can land critical strikes.
- **Mercenary** - Tanky bruiser with a Crossbow whose bolts pierce through dodge.
- **Witch** - Glass cannon wielding a Venomous Flaming Staff (enchantment decorators stacked on a base weapon).

<br>

**Key Features & Patterns**

Singleton Pattern: Ensures only one Manager instance controls the game flow.

Component Pattern: Weapons are modular components attached to characters.

State Pattern: Characters use a state machine for clean and modular behavior management.

Decorator Pattern: Weapon enchantments wrap a base weapon and layer additional effects (e.g. fire damage, venom procs). Decorators compose freely - any number can be stacked.

Observer Pattern: The logger is subscribed to the characters to log their behaviours.

Polymorphism: Characters and weapons extend shared base classes, allowing flexible and scalable behavior.

Data-Driven Config: All stats, damage values, and enchantment parameters are loaded from an external config file - no recompilation needed to rebalance.

<br>

**Focus**

Extensibility: New characters, weapons, enchantments, or behavior states can be added easily.

Modularity: Clear separation of combat, state handling, and game management systems.

Simplicity: Game state is computed fresh each tick, keeping logic straightforward and predictable.

Best Practices: Emphasis on clean code, maintainable structure, and common design patterns.
