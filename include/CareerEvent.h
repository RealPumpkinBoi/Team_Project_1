
#ifndef CAREER_EVENT_H
#define CAREER_EVENT_H

#include "Event.h"
#include <string>

class CareerEvent : public Event {
private:
    std::string companyName;
    std::string recruiterName;

public:
    CareerEvent(
        int eventId,
        int capacity,
        const std::string& name,
        const std::string& description,
        const std::string& date,
        const std::string& time,
        const std::string& location,
        const std::string& companyName,
        const std::string& recruiterName
    );

    const std::string& getCompanyName() const;
    const std::string& getRecruiterName() const;

    std::string getEventType() const override;
    void displayDetails() const override;
};

#endif
