#include "Logger.h"

void Logger::OnNotify(Event event, const std::string& context, std::optional<int> value)
{
    std::string prefix = context.empty() ? "[LOG]" : "[LOG] " + context + ":";

    switch (event)
    {
    case Event::StateChange:
        std::cout << prefix << " State changed." << std::endl;
        break;
    case Event::TakeDamage:
        std::cout << prefix << " Took damage. Remaining health: " << value.value_or(0) << std::endl;
        break;
    case Event::Dodge:
        std::cout << prefix << " Dodged an attack." << std::endl;
        break;
    case Event::Attack:
        std::cout << prefix << " Performed an attack for " << value.value_or(0) << " damage." << std::endl;
        break;
    case Event::Die:
        std::cout << prefix << " Character has died." << std::endl;
        break;
    default:
        std::cout << prefix << " Unknown event occurred." << std::endl;
        break;
    }
}