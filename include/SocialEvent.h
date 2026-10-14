#ifndef SOCIALEVENT_H
#define SOCIALEVENT_H

#include "Event.h"
#include <string>

class SocialEvent : public Event
{
private:
    bool providesFood;
    std::string mainActivity;

public:
    // Constructor passes base variables to Event, and initializes new variables
    SocialEvent(int id,                     // ID
		        int cap,                    // Capacity
                const std::string& n,       // Name
                const std::string& desc,    // Description
                const std::string& d,       // Date
                const std::string& t,       // Time
                const std::string& loc,     // Location
                bool food,                  // Indicates if food is provided
                const std::string& activity // Main activity for the social event
                );

    // Required to fulfill the base class contract
    std::string getEventType() const override;

    // Overriding to add the new attributes to the output
    void displayDetails() const override;
};

#endif