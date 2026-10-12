#include "EventSystem.h"

#include <iostream>
#include <memory>

int main() {
    EventSystem system;

    bool added = system.addEvent(std::make_unique<Event>(
        "E001",
        "Introduction to Robotics",
        "Learn the basics of robotics.",
        "2026-10-15",
        "14:00",
        "Engineering Building 201",
        30,
        "O001"
    ));

    std::cout << "Event added: "
              << (added ? "Yes" : "No") << "\n\n";

    bool duplicateAdded = system.addEvent(std::make_unique<Event>(
        "E001",
        "Duplicate Event",
        "This should not be added.",
        "2026-10-16",
        "10:00",
        "Room 101",
        20,
        "O001"
    ));

    std::cout << "Duplicate rejected: "
              << (!duplicateAdded ? "Yes" : "No") << "\n\n";

    std::cout << "=== All Events ===\n";
    system.displayAllEvents();

    std::cout << "\n=== Find E001 ===\n";
    system.displayEvent("E001");

    std::cout << "\n=== Search: ROBOT ===\n";
    system.searchEventsByName("ROBOT");

    std::cout << "\n=== Missing Event ===\n";
    system.displayEvent("E999");

    return 0;
}