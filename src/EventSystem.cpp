#include "../include/EventSystem.h"
#include "../include/Event.h"

bool EventSystem::isAlreadyRegistered(Student* student, Event* event) const {
    for (const Registration& registration : registrations) {
        if (registration.getStudent() == student &&
            registration.getEvent() == event &&
            registration.getStatus() == "Active") {
            return true;
        }
    }

    return false;
}

bool EventSystem::isEventFull(Event* event) const {
    if (event == nullptr) {
        return true;
    }

    int activeRegistrations = 0;

    for (const Registration& registration : registrations) {
        if (registration.getEvent() == event &&
            registration.getStatus() == "Active") {
            activeRegistrations++;
        }
    }

    return activeRegistrations >= event->getCapacity();
}

bool EventSystem::registerStudent(Student* student, Event* event,
                                  const std::string& registrationDate) {

    // Make sure the student and event exist
    if (student == nullptr || event == nullptr) {
        return false;
    }

    // Prevent duplicate registration
    if (isAlreadyRegistered(student, event)) {
        return false;
    }

    // Prevent registration if the event is full
    if (isEventFull(event)) {
        return false;
    }

    registrations.emplace_back(student, event, registrationDate);

    return true;
}

bool EventSystem::cancelRegistration(Student* student, Event* event) {
    if (student == nullptr || event == nullptr) {
        return false;
    }

    for (Registration& registration : registrations) {
        if (registration.getStudent() == student &&
            registration.getEvent() == event &&
            registration.getStatus() == "Active") {

            registration.cancel();
            return true;
        }
    }

    return false;
}

std::vector<Event*> EventSystem::getEventsForStudent(Student* student) const {
    std::vector<Event*> events;

    for (const Registration& registration : registrations) {
        if (registration.getStudent() == student &&
            registration.getStatus() == "Active") {
            events.push_back(registration.getEvent());
        }
    }
    return events;
}

std::vector<Student*> EventSystem::getStudentsForEvent(Event* event) const {
    std::vector<Student*> students;

    for (const Registration& registration : registrations) {
        if (registration.getEvent() == event &&
            registration.getStatus() == "Active") {
            students.push_back(registration.getStudent());
        }
    }
    return students;
}