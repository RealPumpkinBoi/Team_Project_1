# Campus Event Management System

## 1. Project Overview

The Campus Event Management System is a terminal based C++ application developed as a team project for Object Oriented Programming.

The system allows users to manage students, create and search campus events, manage organizers, and register students for events.

The project demonstrates object-oriented programming concepts such as encapsulation, inheritance, polymorphism, and composition, along with collaborative development using Git and GitHub.

## 2. Team Members and Contributions

| Team Member | Primary Responsibilities |
|---|---|
| Alex Waszkiewicz | Repository setup, pull request reviews, and EventSystem development |
| Marina Tribolet | Registration system, duplicate registration prevention, capacity validation, cancellation, and registration functionality |
| Haneef Md | EventManager, event subclasses, Create/View/Search Event features, input validation, testing, and integration |
| Michelle | UML diagram, FileManager, organizer menu integration, and merge conflict resolution |
| Pablo | Event base class, SocialEvent, menu integration, and abstract class adjustments |
| Morgan Saldana | Organizer class and organizer management integration |
| Caden | Student class, student management, and initial main menu implementation |

## 3. Features

The application provides a menu-driven interface with the following operations:

1. Add Student
2. View Students
3. Create Event
4. View Events
5. Search Events
6. Register Student for Event
7. Cancel Registration
8. View Student Registrations
9. View Event Attendees
10. View Organizers
11. System Reports (not yet implemented)
0. Exit

The registration system prevents duplicate active registrations and checks event capacity before accepting new registrations.

The application supports Academic, Club, Career, and Social event types.

## 4. Class Design

| Class | Responsibility |
|---|---|
| Student | Stores student information |
| Organizer | Stores organizer details |
| Event | Abstract base class for events |
| AcademicEvent | Academic event details |
| ClubEvent | Club event details |
| CareerEvent | Career event details |
| SocialEvent | Social event details |
| EventManager | Stores, searches, and displays events |
| Registration | Connects students and events |
| EventSystem | Manages registrations and cancellations |
| FileManager | Provides student file-saving and loading methods |

The project uses inheritance for different event types and polymorphism through virtual functions.

Additional architecture details are available in `docs/DESIGN.md`, and the UML diagram is located in `docs/UML.pdf`.

## 5. Building the Application

Requirements:

- C++17-compatible compiler
- Git (to clone the repository)

Clone the repository:

```bash
git clone https://github.com/RealPumpkinBoi/Team_Project_1.git
cd Team_Project_1
```

Compile using g++:

```bash
g++ -std=c++17 -Iinclude src/*.cpp -o CampusEventSystem
```

## 6. Running the Application

On macOS or Linux:

```bash
./CampusEventSystem
```

On Windows, when compiled as an executable:

```powershell
.\CampusEventSystem.exe
```

After launching, select an option from the console menu and follow the prompts.

For example, add a student, create an event, and then register that student for the event.

## 7. Data Storage

The project uses text files for data persistence.

Student records are currently written to `students.txt` in the following format:

```text
studentID:name:email:major
```

Student information is loaded from this file when the application starts.

The FileManager also contains separate student save/load methods, but these use a different file format and still need to be standardized with the main application.

Events, organizers, and registrations are currently maintained in memory and are not fully persisted between application sessions.

## 8. Known Limitations

- Event, organizer, and registration data persistence is incomplete.
- Student file storage uses inconsistent formats in different implementations.
- System Reports is present in the menu but has not yet been implemented.
- Organizer-to-event associations are not fully integrated.
- Complete integration and end-to-end testing are still needed.

## Additional Documentation

- `docs/DESIGN.md` — Technical design and class relationships
- `docs/UML.pdf` — UML class diagram
- GitHub pull requests — Development history and team contributions
