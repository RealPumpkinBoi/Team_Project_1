#ifndef ACADEMICEVENT_H
#define ACADEMICEVENT_H

#include "Event.h"
#include <string>

class AcademicEvent : public Event {
private:
    std::string department;
    std::string speaker;

public:
    AcademicEvent(
        const std::string& eventId,
        const std::string& name,
        const std::string& description,
        const std::string& date,
        const std::string& time,
        const std::string& location,
        int maxCapacity,
        const std::string& organizerId,
        const std::string& department,
        const std::string& speaker
    );

    const std::string& getDepartment() const;
    const std::string& getSpeaker() const;

    std::string getEventType() const override;
    void displayDetails() const override;
};

#endif