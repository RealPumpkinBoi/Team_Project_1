#include "../include/Event.h"

//Constructor
Event::Event(int id,
		int cap,
		const std::string& n,
		const std::string& desc,
        const std::string& d,
		const std::string& t,
		const std::string& loc)
	//Constructor - Member initializer list
    : eventId(id), capacity(cap), registeredCount(0), name(n),
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
