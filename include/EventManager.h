#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include "Event.h"

#include <memory>
#include <string>
#include <vector>

class EventManager {
private:
    std::vector<std::unique_ptr<Event>> events;

public:
    bool addEvent(std::unique_ptr<Event> event);

    Event* findEventById(int eventId);
    const Event* findEventById(int eventId) const;

    void displayEvent(int eventId) const;
    void displayAllEvents() const;
    void searchEventsByName(const std::string& keyword) const;

    const std::vector<std::unique_ptr<Event>>& getEvents() const;
};

#endif