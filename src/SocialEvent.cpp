
#include "SocialEvent.h"
#include <iostream>

// Constructor
SocialEvent::SocialEvent(int id,
                         int cap,
                         const std::string& n,
                         const std::string& desc,
                         const std::string& d,
                         const std::string& t,
                         const std::string& loc,
                         bool food,
                         const std::string& activity)
    : Event(id, cap, n, desc, d, t, loc),
      providesFood(food),
      mainActivity(activity)
{
}

// Return event type
std::string SocialEvent::getEventType() const
{
    return "Networking Day";
}

// Display event details
void SocialEvent::displayDetails() const
{
    Event::displayDetails();

    std::cout << "Food Provided: "
              << (providesFood ? "Yes" : "No") << '\n'
              << "Main Activity: " << mainActivity << '\n';
}
