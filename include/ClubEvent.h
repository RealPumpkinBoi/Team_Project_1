#ifndef CLUB_EVENT_H
#define CLUB_EVENT_H

#include "Event.h"

class ClubEvent : public Event {

private:
    std::string clubName;
    
public:

    // Constructor
    ClubEvent(const std::string& name,
              const std::string& id,
              const std::string& date,
              const std::string& location,
              const std::string& description,
              int capacity,
              const std::string& clubName); 
    
    // Getters
    std::string getClubName() const;

    // Setters
    void setClubName(const std::string& clubName);

    // Display
    void displayDetails() const override;
};

#endif // CLUB_EVENT_H