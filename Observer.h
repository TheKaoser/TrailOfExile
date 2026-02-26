#pragma once

#include "Event.h"
#include <string>
#include <optional>

// Interface for anything that wants to react to character events (logging, UI, etc.).
class Observer
{
public:
    virtual ~Observer() = default;

    virtual void OnNotify(Event event, const std::string& context, std::optional<int> value, const std::string& detail) = 0;
};