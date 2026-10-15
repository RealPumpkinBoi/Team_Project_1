#include "CareerEvent.h"

#include <iostream>

CareerEvent::CareerEvent(
    int eventId,
    int capacity,
    const std::string& name,
    const std::string& description,
    const std::string& date,
    const std::string& time,
    const std::string& location,
    const std::string& companyName,
    const std::string& recruiterName
)
    : Event(eventId, capacity, name, description,
            date, time, location),
      companyName(companyName),
      recruiterName(recruiterName) {
}

const std::string& CareerEvent::getCompanyName() const {
    return companyName;
}

const std::string& CareerEvent::getRecruiterName() const {
    return recruiterName;
}

std::string CareerEvent::getEventType() const {
    return "Career";
}

void CareerEvent::displayDetails() const {
    Event::displayDetails();

    std::cout << "Company: " << companyName << '\n'
              << "Recruiter: " << recruiterName << '\n';
}