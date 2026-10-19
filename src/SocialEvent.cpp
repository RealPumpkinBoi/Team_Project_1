#include "SocialEvent.h"

#include <iostream>

// Call the base Event constructor in the initializer list, then initialize derived members
SocialEvent::SocialEvent(int id,                     // ID
                         int cap,                    // Capacity
                         const std::string& n,       // Name
                         const std::string& desc,    // Description
                         const std::string& d,       // Date
                         const std::string& t,       // Time
                         const std::string& loc,     // Location
                         bool food,                  // Indicates if food is provided
                         const std::string& activity // Main activity for the social event
                        )
    : Event(id, cap, n, desc, d, t, loc), providesFood(food), mainActivity(activity)
{
}

// Implementing the pure virtual function
std::string SocialEvent::getEventType() const
{
    return "Networking Day";
}

void SocialEvent::displayDetails() const
{
    // 1. Call the base class method to print ID, Name, Date, Capacity, etc.
    Event::displayDetails();

    // 2. Print the unique details for this specific derived class
    std::cout << "Food Provided: " << (providesFood ? "Yes" : "No") << '\n'
              << "Main Activity: " << mainActivity << '\n';
}