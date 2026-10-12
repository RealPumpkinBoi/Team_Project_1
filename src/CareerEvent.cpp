#include "CareerEvent.h"

#include <iostream>

CareerEvent::CareerEvent(
    const std::string& eventId,
    const std::string& name,
    const std::string& description,
    const std::string& date,
    const std::string& time,
    const std::string& location,
    int maxCapacity,
    const std::string& organizerId,
    const std::string& companyName,
    const std::string& recruiterName
)
    : Event(eventId, name, description, date, time,
            location, maxCapacity, organizerId),
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