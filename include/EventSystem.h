#ifndef EVENTSYSTEM_H
#define EVENTSYSTEM_H

#include "Event.h"
#include <memory>
#include <string>
#include <vector>

class EventSystem {
private:
    std::vector<std::unique_ptr<Event>> events;

public:
    bool addEvent(std::unique_ptr<Event> event);

    const Event* findEventById(const std::string& eventId) const;

    void displayEvent(const std::string& eventId) const;

    void displayAllEvents() const;

    void searchEventsByName(const std::string& keyword) const;
};

#endif