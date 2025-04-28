# Trail of Exile
Trail of Exile is a project where two or more characters, each from a selected class with a specific weapon and stats like attack probability and dodge probability, compete to be the last one standing in the arena. It was created to showcase clean code, solid architecture, efficient data handling through caching, and strong use of object-oriented programming principles like polymorphism.

<br><br>

🛠 Key Features & Patterns

Singleton Pattern: Ensures only one Manager instance controls the game flow.

Component Pattern: Weapons are modular components attached to characters.

State Pattern: Characters use a state machine for clean and modular behavior management.

Timed Update: The Manager’s Update method handles periodic global logic.

Polymorphism: Characters and weapons extend shared base classes, allowing flexible and scalable behavior.

Observer Pattern: The logger is suscribed to the characters to log their behaviours.

<br><br>

🔍 Focus

Extensibility: New characters, weapons, or behavior states can be added easily.

Modularity: Clear separation of combat, state handling, and game management systems.

Efficiency: Cached frequently accessed data to reduce redundant calculations and improve performance.

Best Practices: Emphasis on clean code, maintainable structure, and common design patterns.
