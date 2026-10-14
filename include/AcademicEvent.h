#ifndef ACADEMIC_EVENT_H
#define ACADEMIC_EVENT_H

#include "Event.h"

#include <iostream>
#include <string>

class AcademicEvent : public Event {

private:
    std::string department;
    std::string speaker;

public:
    AcademicEvent(const std::string& name,
                  const std::string& id,
                  const std::string& date,
                  const std::string& location,
                  const std::string& description,
                  int capacity,
                  const std::string& department,
                  const std::string& speaker);
    
    // Getters
    std::string getDepartment() const;
    std::string getSpeaker() const;

    // Setters
    void setDepartment(const std::string& department);
    void setSpeaker(const std::string& speaker);

    // Display
    void displayDetails() const override;
};

#endif // ACADEMIC_EVENT_H
                  