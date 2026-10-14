#include "EventManager.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <utility>

namespace {
    std::string toLower(std::string text) {
        std::transform(text.begin(), text.end(), text.begin(),
            [](unsigned char ch) {
                return static_cast<char>(std::tolower(ch));
            });

        return text;
    }
}

bool EventManager::addEvent(std::unique_ptr<Event> event) {
    if (!event) {
        return false;
    }

    if (findEventById(event->getEventId()) != nullptr) {
        return false;
    }

    events.push_back(std::move(event));
    return true;
}

Event* EventManager::findEventById(int eventId) {
    for (const auto& event : events) {
        if (event->getEventId() == eventId) {
            return event.get();
        }
    }

    return nullptr;
}

const Event* EventManager::findEventById(int eventId) const {
    for (const auto& event : events) {
        if (event->getEventId() == eventId) {
            return event.get();
        }
    }

    return nullptr;
}

void EventManager::displayEvent(int eventId) const {
    const Event* event = findEventById(eventId);

    if (event == nullptr) {
        std::cout << "Event not found.\n";
        return;
    }

    event->displayDetails();
}

void EventManager::displayAllEvents() const {
    if (events.empty()) {
        std::cout << "No events available.\n";
        return;
    }

    for (const auto& event : events) {
        event->displayDetails();
        std::cout << "------------------------------\n";
    }
}

void EventManager::searchEventsByName(
    const std::string& keyword) const {

    if (keyword.find_first_not_of(" \t\r\n") == std::string::npos) {
        std::cout << "Please enter an event name to search.\n";
        return;
    }

    const std::string searchText = toLower(keyword);
    bool found = false;

    for (const auto& event : events) {
        if (toLower(event->getName()).find(searchText)
            != std::string::npos) {

            event->displayDetails();
            std::cout << "------------------------------\n";
            found = true;
        }
    }

    if (!found) {
        std::cout << "No matching events found.\n";
    }
}