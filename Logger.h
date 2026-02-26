#ifndef LOGGER_H
#define LOGGER_H

#include "Observer.h"

class Logger : public Observer
{
public:
    void OnNotify(Event event, const std::string& context, std::optional<int> value) override;
};

#endif // LOGGER_H