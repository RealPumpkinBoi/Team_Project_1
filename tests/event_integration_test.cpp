#include "EventManager.h"
#include "EventSystem.h"
#include "AcademicEvent.h"


#include <cassert>
#include <iostream>
#include <memory>

int main() {
    EventManager manager;
    EventSystem registrations;

    bool added = manager.addEvent(std::make_unique<AcademicEvent>(
        101, 30,
        "Introduction to Robotics",
        "Learn robotics basics.",
        "2026-10-15", "14:00",
        "Engineering Building 201",
        "Engineering", "Dr. Smith"
    ));
    assert(added);

    bool duplicateAdded = manager.addEvent(std::make_unique<AcademicEvent>(
        101, 20,
        "Duplicate Event",
        "Should not be added.",
        "2026-10-16", "10:00",
        "Room 101",
        "Engineering", "Dr. Smith"
    ));
    assert(!duplicateAdded);

    Event* event = manager.findEventById(101);
    assert(event != nullptr);
    assert(event->getCapacity() == 30);
    assert(manager.findEventById(999) == nullptr);

    // Check compatibility with the existing registration system.
    assert(!registrations.isEventFull(event));
    assert(registrations.getStudentsForEvent(event).empty());

    bool registered = registrations.registerStudent(
        nullptr, event, "2026-10-12"
    );
    assert(!registered);

    std::cout << "=== Event Details ===\n";
    manager.displayEvent(101);

    std::cout << "\n=== Search: ROBOT ===\n";
    manager.searchEventsByName("ROBOT");

    std::cout << "\nAll assertions passed.\n";
    return 0;
}
