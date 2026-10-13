#include "AcademicEvent.h"

#include <iostream>

AcademicEvent::AcademicEvent(
    int eventId,
    int capacity,
    const std::string& name,
    const std::string& description,
    const std::string& date,
    const std::string& time,
    const std::string& location,
    const std::string& department,
    const std::string& speaker
)
    : Event(eventId, capacity, name, description,
            date, time, location),
      department(department),
      speaker(speaker) {
}

const std::string& AcademicEvent::getDepartment() const {
    return department;
}

const std::string& AcademicEvent::getSpeaker() const {
    return speaker;
}

std::string AcademicEvent::getEventType() const {
    return "Academic";
}

void AcademicEvent::displayDetails() const {
    Event::displayDetails();

    std::cout << "Department: " << department << '\n'
              << "Speaker: " << speaker << '\n';
}