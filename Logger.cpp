#include "Logger.h"
#include <iostream>

void Logger::OnNotify(Event event, const std::string& context, std::optional<int> value, const std::string& detail)
{
    switch (event)
    {
    case Event::StateChange:
        std::cout << "  [STATE]  " << context << ": Entered " << detail << " state.\n";
        break;
    case Event::TakeDamage:
        std::cout << "  [COMBAT] " << context << ": Took damage. Health: " << value.value_or(0) << '\n';
        break;
    case Event::Dodge:
        std::cout << "  [COMBAT] " << context << ": Dodged " << detail << ".\n";
        break;
    case Event::Attack:
        std::cout << "  [COMBAT] " << context << ": Attacked " << detail << " for " << value.value_or(0) << " damage.\n";
        break;
    case Event::Die:
        std::cout << "  [DEATH]  " << context << ": Has been defeated.\n";
        break;
    default:
        std::cout << "  [LOG]    " << context << ": Unknown event.\n";
        break;
    }
}