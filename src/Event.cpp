#include "Event.h"

#include <iostream>
#include <stdexcept>

Event::Event(const std::string& eventId,
             const std::string& name,
             const std::string& description,
             const std::string& date,
             const std::string& time,
             const std::string& location,
             int maxCapacity,
             const std::string& organizerId)
    : eventId(eventId),
      name(name),
      description(description),
      date(date),
      time(time),
      location(location),
      maxCapacity(maxCapacity),
      organizerId(organizerId) {

    if (eventId.find_first_not_of(" \t\r\n") == std::string::npos) {
        throw std::invalid_argument("Event ID cannot be blank.");
    }

    if (name.find_first_not_of(" \t\r\n") == std::string::npos) {
        throw std::invalid_argument("Event name cannot be blank.");
    }

    if (maxCapacity <= 0) {
        throw std::invalid_argument("Event capacity must be positive.");
    }
}

const std::string& Event::getEventId() const {
    return eventId;
}

const std::string& Event::getName() const {
    return name;
}

const std::string& Event::getDescription() const {
    return description;
}

const std::string& Event::getDate() const {
    return date;
}

const std::string& Event::getTime() const {
    return time;
}

const std::string& Event::getLocation() const {
    return location;
}

int Event::getMaxCapacity() const {
    return maxCapacity;
}

const std::string& Event::getOrganizerId() const {
    return organizerId;
}

std::string Event::getEventType() const {
    return "General";
}

void Event::displayDetails() const {
    std::cout << "Event ID: " << eventId << '\n'
              << "Type: " << getEventType() << '\n'
              << "Name: " << name << '\n'
              << "Description: " << description << '\n'
              << "Date: " << date << '\n'
              << "Time: " << time << '\n'
              << "Location: " << location << '\n'
              << "Maximum capacity: " << maxCapacity << '\n'
              << "Organizer ID: " << organizerId << '\n';
}