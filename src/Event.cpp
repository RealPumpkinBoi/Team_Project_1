#include "../include/Event.h"
#include <iostream>

//Constructor
Event::Event(int id,
		int cap,
		const std::string& n,
		const std::string& desc,
        const std::string& d,
		const std::string& t,
		const std::string& loc)
	//Constructor - Member initializer list
    : eventId(id), capacity(cap), name(n),
      description(desc), date(d), time(t), location(loc)
{

}

// Getters
int Event::getEventId() const {
    return eventId;
}

int Event::getCapacity() const {
    return capacity;
}

std::string Event::getName() const
{
    return name;
}

std::string Event::getDescription() const
{
    return description;
}

std::string Event::getDate() const
{
    return date;
}

std::string Event::getTime() const
{
    return time;
}

std::string Event::getLocation() const
{
    return location;
}
/* Since Event is an abstract class, we cannot provide a default implementation
for getEventType() here.
Each derived class must implement this method to specify its own event type.
------------Commented out to avoid compilation errors - Start-----------------
std::string Event::getEventType() const 
{
    return "General";
}
------------Commented out to avoid compilation errors - End----------------*/

void Event::displayDetails() const {
    std::cout << "Event ID: " << getEventId() << '\n'
              << "Type: " << getEventType() << '\n'
              << "Name: " << getName() << '\n'
              << "Description: " << getDescription() << '\n'
              << "Date: " << getDate() << '\n'
              << "Time: " << getTime() << '\n'
              << "Location: " << getLocation() << '\n'
              << "Maximum capacity: " << getCapacity() << '\n';
}