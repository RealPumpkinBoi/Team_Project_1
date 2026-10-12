#ifndef EVENT_H
#define EVENT_H

#include <string>

class Event {
private:
    std::string eventId;
    std::string name;
    std::string description;
    std::string date;
    std::string time;
    std::string location;
    int maxCapacity;
    std::string organizerId;

public:
    Event(const std::string& eventId,
          const std::string& name,
          const std::string& description,
          const std::string& date,
          const std::string& time,
          const std::string& location,
          int maxCapacity,
          const std::string& organizerId);

    virtual ~Event() = default;

    const std::string& getEventId() const;
    const std::string& getName() const;
    const std::string& getDescription() const;
    const std::string& getDate() const;
    const std::string& getTime() const;
    const std::string& getLocation() const;
    int getMaxCapacity() const;
    const std::string& getOrganizerId() const;

    virtual std::string getEventType() const;
    virtual void displayDetails() const;
};

#endif