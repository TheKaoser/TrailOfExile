#ifndef OBSERVER_H
#define OBSERVER_H

#include "Event.h"
#include <string>
#include <optional>

class Observer
{
public:
    virtual ~Observer() = default;

    virtual void OnNotify(Event event, const std::string& context, std::optional<int> value) = 0;
};

#endif // OBSERVER_H