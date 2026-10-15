#ifndef CLUB_EVENT_H
#define CLUB_EVENT_H

#include "Event.h"
#include <string>

class ClubEvent : public Event {
private:
    std::string clubName;

public:
    ClubEvent(
        int eventId,
        int capacity,
        const std::string& name,
        const std::string& description,
        const std::string& date,
        const std::string& time,
        const std::string& location,
        const std::string& clubName
    );

    const std::string& getClubName() const;

    std::string getEventType() const override;
    void displayDetails() const override;
};

#endif