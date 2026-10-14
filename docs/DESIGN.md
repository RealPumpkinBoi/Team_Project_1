# Design

Design notes for the Campus Event System. See `UML.pdf` for the class diagram.


## What the program does

It's a menu program for campus events. You can add students, create events,
sign students up for events, and cancel sign-ups. Everything gets saved to
text files so nothing is lost.


## The classes and what each one does

| Class | What it does |
|---|---|
| `Student` | Stores one student: ID, name, email, major. |
| `Organizer` | Stores one organizer: ID, name, email, department. |
| `Event` | The basic event: ID, name, description, date, time, place, how many people can come. |
| `AcademicEvent` | An event that also has a department and a speaker. |
| `ClubEvent` | An event that also has a club name. |
| `CareerEvent` | An event that also has a company and a recruiter. |
| `SocialEvent` | An event that also says if there's food and what the main activity is. |
| `Registration` | Says "this student is signed up for this event", plus the date and whether it's still active or cancelled. |
| `EventManager` | Keeps the list of all events. Adds, finds, shows and searches them. |
| `EventSystem` | Keeps the list of all sign-ups. Signs students up, cancels, and shows who's going where. |
| `FileManager` | TODO: saves and loads everything from files. |

## Who did what

| Member | What they worked on |
|---|---|
| Alex Waszkiewicz | Set up files, reviewed PRs, worked on the EventSystem files |
| Marina Tribolet |  |
| Michelle | E |
| Haneef Md | |
| Pablo |  |
| Morgan Saldana |  |
| Caden | Set up Student.h, Student.cpp, Student Registration, and the foundations for Main.cpp |


