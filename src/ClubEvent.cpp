#include "ClubEvent.h"

#include <iostream>

ClubEvent::ClubEvent(
    int eventId,
    int capacity,
    const std::string& name,
    const std::string& description,
    const std::string& date,
    const std::string& time,
    const std::string& location,
    const std::string& clubName
)
    : Event(eventId, capacity, name, description,
            date, time, location),
      clubName(clubName) {
}

const std::string& ClubEvent::getClubName() const {
    return clubName;
}

std::string ClubEvent::getEventType() const {
    return "Club";
}

void ClubEvent::displayDetails() const {
    Event::displayDetails();

    std::cout << "Club name: " << clubName << '\n';
}