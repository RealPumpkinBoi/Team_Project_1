# Campus Event Management System — Technical Design

## 1. Project Overview

The Campus Event Management System is a C++ application designed to manage students, campus events, organizers, and event registrations.

The project demonstrates object-oriented programming principles, including encapsulation, inheritance, polymorphism, composition, and relationships between objects.

The system is divided into classes with separate responsibilities, allowing team members to develop components independently and integrate them through GitHub.

**Development status:** The application compiles and launches. Student management and event creation have been connected to the main menu. Other features, including registration menu integration, reports, and complete data persistence, are still being developed.

## 2. Class Design

| Class           | Responsibility                                                                                      |
| --------------- | --------------------------------------------------------------------------------------------------- |
| `Student`       | Stores student ID, name, email, and major.                                                          |
| `Organizer`     | Stores organizer information, including ID, name, email, and department.                            |
| `Event`         | Abstract base class containing information shared by all event types.                               |
| `AcademicEvent` | Represents academic events with department and speaker information.                                 |
| `ClubEvent`     | Represents club events with a club name.                                                            |
| `CareerEvent`   | Represents career events with company and recruiter information.                                    |
| `SocialEvent`   | Represents social events with food availability and a main activity.                                |
| `Registration`  | Represents the relationship between a student and an event, including registration date and status. |
| `EventManager`  | Manages event storage, ID validation, searching, and display.                                       |
| `EventSystem`   | Manages registrations, cancellations, duplicate checks, capacity checks, and registration lookups.  |
| `FileManager`   | Provides file-saving and loading functionality; currently implemented for student records only.     |

## 3. Object-Oriented Design

### Encapsulation

Classes use private data members and public methods to provide controlled access to object information.

For example, the `Student` class stores student information privately and provides getter methods to retrieve individual fields.

### Inheritance

The `Event` class serves as the base class for four specialized event types:

- `AcademicEvent`
- `ClubEvent`
- `CareerEvent`
- `SocialEvent`

Each derived class extends the common event information with attributes specific to its event type.

This structure reduces duplication and allows additional event types to be introduced without redesigning the entire event model.

### Abstract Classes and Method Overriding

`Event` is an abstract class because `getEventType()` is a pure virtual function.

Each concrete event subclass must implement this method.

Subclasses also provide specialized display behavior so that their additional attributes can be presented alongside shared event information.

### Polymorphism

The application uses polymorphism to manage different event types through base-class pointers.

`EventManager` stores event objects in a collection of `std::unique_ptr<Event>`.

This allows academic, club, career, and social events to be stored together while preserving their specialized behavior.

When a virtual method is called through an `Event` pointer, C++ selects the appropriate overridden implementation based on the object's actual type.

### Composition and Ownership

`EventManager` owns its event objects through `std::unique_ptr<Event>`.

This provides automatic lifetime management and avoids the need to manually delete events.

`EventSystem` contains a collection of `Registration` objects. Each registration holds references through pointers to existing `Student` and `Event` objects.

The registration system does not own those student or event objects. Their lifetime must therefore be managed by the application.

## 4. Relationships Between Classes

The system contains several important relationships:

**Student and Registration:** A student may have multiple registrations.

**Event and Registration:** An event may have multiple registered students.

**Registration:** Connects a student with an event and tracks registration status.

**EventManager and Event:** The manager owns and manages a collection of events.

**EventSystem and Registration:** The registration system manages a collection of registration records.

**Event inheritance:** AcademicEvent, ClubEvent, CareerEvent, and SocialEvent inherit from Event.

Organizer associations with events remain an area for further integration.

## 5. Registration System

The `EventSystem` class manages event registrations.

The `registerStudent()` method checks that both object pointers are valid, prevents duplicate active registrations, and verifies that the event has available capacity.

When all checks pass, a registration object is created.

The `cancelRegistration()` method locates an active registration and changes its status to canceled.

The system also provides methods to retrieve:

- All events registered by a particular student.
- All students registered for a particular event.

These functions are implemented in the registration system but still need to be connected to the console menu.

## 6. Data Storage and Persistence

The project uses text files for application data storage.

The current implementation supports writing student records and loading them from a file.

However, student persistence is implemented in two places using different formats. These implementations must be standardized before final integration.

Complete persistence for events, organizers, and registrations is still required.

When implemented, loading must reconstruct the relationships between students, events, and registrations using valid object references rather than pointers saved directly to files.

## 7. Project Organization

The repository separates interfaces, implementations, documentation, and data.

| Directory  | Purpose                                              |
| ---------- | ---------------------------------------------------- |
| `include/` | C++ class declarations and header files.             |
| `src/`     | Class implementations and application entry point.   |
| `data/`    | Text files intended for persistent application data. |
| `docs/`    | Technical design documentation and UML materials.    |
| `tests/`   | Development and integration tests.                   |

The project uses C++17 and can be compiled using:

```bash
g++ -std=c++17 -Iinclude src/*.cpp -o CampusEventSystem
```

## 8. Technical Challenges and Design Decisions

### Integrating Independently Developed Components

Different team members developed the student, event, registration, and persistence components in parallel.

One integration challenge is connecting these independently developed classes through a shared console interface without duplicating business logic.

### Managing Object Lifetimes

The registration system references existing Student and Event objects.

Because raw pointers are used for registration relationships, the application must ensure those objects remain valid throughout their registrations.

### Supporting Multiple Event Types

The team used an abstract Event base class and derived event classes rather than storing every event type in one large class.

This supports extensibility and reduces duplication.

### Maintaining Consistent Persistence

Student data currently has inconsistent serialization formats in different parts of the application.

A shared format and centralized persistence strategy are needed to ensure that saved records can be loaded reliably.

## 9. Team Contributions

| Team Member      | Contributions                                                                                                                                        |
| ---------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------- |
| Alex Waszkiewicz | Repository setup, PR reviews, and EventSystem development.                                                                                           |
| Marina Tribolet  | Registration system implementation, including duplicate registration prevention, capacity validation, cancellation, and registration lookup methods. |
| Michelle         | To be confirmed.                                                                                                                                     |
| Haneef Md        | To be confirmed.                                                                                                                                     |
| Pablo            | To be confirmed.                                                                                                                                     |
| Morgan Saldana   | To be confirmed.                                                                                                                                     |
| Caden            | Student model, student registration functionality, and initial main menu implementation.                                                             |

Team responsibilities should be reviewed and updated to reflect the final merged contributions.

## 10. Remaining Development Work

The following work remains before final submission:

- Connect event display and searching to the menu.
- Integrate registration and cancellation menu operations.
- Integrate registration and attendee views.
- Complete organizer management.
- Implement at least three reports.
- Standardize and complete file persistence.
- Improve input validation and error handling.
- Complete and verify the UML class diagram.
- Perform integrated application testing.
- Prepare the final team demonstration.

This documentation should be updated as functionality is completed to ensure that it accurately represents the submitted application.
