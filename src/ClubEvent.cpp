#include "ClubEvent.h"

#include <iostream>

ClubEvent::ClubEvent(
    const std::string& eventId,
    const std::string& name,
    const std::string& description,
    const std::string& date,
    const std::string& time,
    const std::string& location,
    int maxCapacity,
    const std::string& organizerId,
    const std::string& clubName
)
    : Event(eventId, name, description, date, time,
            location, maxCapacity, organizerId),
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