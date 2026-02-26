#include "Logger.h"
#include <iostream>

void Logger::OnNotify(Event event, const std::string& context, std::optional<int> value)
{
    std::string prefix = context.empty() ? "[LOG]" : "[LOG] " + context + ":";

    switch (event)
    {
    case Event::StateChange:
        std::cout << prefix << " State changed.\n";
        break;
    case Event::TakeDamage:
        std::cout << prefix << " Took damage. Remaining health: " << value.value_or(0) << '\n';
        break;
    case Event::Dodge:
        std::cout << prefix << " Dodged an attack.\n";
        break;
    case Event::Attack:
        std::cout << prefix << " Performed an attack for " << value.value_or(0) << " damage.\n";
        break;
    case Event::Die:
        std::cout << prefix << " Character has died.\n";
        break;
    default:
        std::cout << prefix << " Unknown event occurred.\n";
        break;
    }
}