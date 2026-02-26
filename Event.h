#pragma once

// All events a Character can broadcast to its observers.
enum class Event
{
    StateChange,
    TakeDamage,
    Dodge,
    Attack,
    Die
};