#ifndef LOGGER_H
#define LOGGER_H

#include "Observer.h"
#include <iostream>

class Logger : public Observer
{
public:
    void OnNotify(Event event, const std::string& context = "", std::optional<int> value = std::nullopt) override;
};

#endif // LOGGER_H