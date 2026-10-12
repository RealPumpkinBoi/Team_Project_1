#include "EventSystem.h"
#include "AcademicEvent.h"
#include "ClubEvent.h"
#include "CareerEvent.h"

#include <memory>

int main() {
    EventSystem system;

    system.addEvent(std::make_unique<AcademicEvent>(
        "A001", "Introduction to Robotics",
        "Learn robotics basics.", "2026-10-15", "14:00",
        "Engineering Building 201", 30, "O001",
        "Engineering", "Dr. Chen"
    ));

    system.addEvent(std::make_unique<ClubEvent>(
        "C001", "Coding Club Meeting",
        "Practice programming together.", "2026-10-16", "15:00",
        "Computer Lab 101", 25, "O002",
        "Coding Club"
    ));

    system.addEvent(std::make_unique<CareerEvent>(
        "R001", "Technology Career Fair",
        "Meet recruiters.", "2026-10-17", "10:00",
        "Student Center", 100, "O003",
        "Example Tech", "Jordan Lee"
    ));

    system.displayAllEvents();

    return 0;
}