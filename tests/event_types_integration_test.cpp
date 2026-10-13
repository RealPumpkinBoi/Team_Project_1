#include "EventManager.h"
#include "AcademicEvent.h"
#include "ClubEvent.h"
#include "CareerEvent.h"

#include <cassert>
#include <iostream>
#include <memory>

int main() {
    EventManager manager;

    bool academicAdded = manager.addEvent(
        std::make_unique<AcademicEvent>(
            101, 30,
            "Introduction to Robotics",
            "Learn robotics basics.",
            "2026-10-15", "14:00",
            "Engineering Building 201",
            "Engineering", "Dr. Chen"
        )
    );

    bool clubAdded = manager.addEvent(
        std::make_unique<ClubEvent>(
            102, 25,
            "Coding Club Meeting",
            "Practice programming together.",
            "2026-10-16", "15:00",
            "Computer Lab 101",
            "Coding Club"
        )
    );

    bool careerAdded = manager.addEvent(
        std::make_unique<CareerEvent>(
            103, 100,
            "Technology Career Fair",
            "Meet recruiters.",
            "2026-10-17", "10:00",
            "Student Center",
            "Example Tech", "Jordan Lee"
        )
    );

    assert(academicAdded);
    assert(clubAdded);
    assert(careerAdded);

    const Event* academic = manager.findEventById(101);
    const Event* club = manager.findEventById(102);
    const Event* career = manager.findEventById(103);

    assert(academic != nullptr);
    assert(club != nullptr);
    assert(career != nullptr);

    assert(academic->getEventType() == "Academic");
    assert(club->getEventType() == "Club");
    assert(career->getEventType() == "Career");

    manager.displayAllEvents();

    std::cout << "\nAll event type assertions passed.\n";
    return 0;
}