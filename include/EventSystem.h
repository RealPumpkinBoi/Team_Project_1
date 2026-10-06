#ifndef EVENT_SYSTEM_H
#define EVENT_SYSTEM_H

#include <vector>
#include "Registration.h"

class EventSystem {
private:
    std::vector<Registration> registrations;

public:
    bool isAlreadyRegistered(Student* student, Event* event) const;

    bool isEventFull(Event* event) const;

    bool registerStudent(Student* student, Event* event,
                     const std::string& registrationDate);

    bool cancelRegistration(Student* student, Event* event);

    std::vector<Event*> getEventsForStudent(Student* student) const;

    std::vector<Student*> getStudentsForEvent(Event* event) const;
};

#endif