#pragma once

#include "Observer.h"

// Prints every character event to stdout. Plug-and-play: just subscribe it
// to any Character with AddObserver().
class Logger : public Observer
{
public:
    void OnNotify(Event event, const std::string& context, std::optional<int> value) override;
};