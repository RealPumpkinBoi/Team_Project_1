#ifndef CLUBEVENT_H
#define CLUBEVENT_H

#include "Event.h"
#include <string>

class ClubEvent : public Event {
private:
    std::string clubName;

public:
    ClubEvent(
        const std::string& eventId,
        const std::string& name,
        const std::string& description,
        const std::string& date,
        const std::string& time,
        const std::string& location,
        int maxCapacity,
        const std::string& organizerId,
        const std::string& clubName
    );

    const std::string& getClubName() const;

    std::string getEventType() const override;
    void displayDetails() const override;
};

#endif