#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <sstream>
#include <memory>
#include <utility>

#include "Student.h"
#include "Registration.h"
#include "Organizer.h"
#include "FileManager.h"
#include "EventSystem.h"
#include "EventManager.h"
#include "Event.h"
#include "ClubEvent.h"
#include "CareerEvent.h"
#include "AcademicEvent.h"
#include "SocialEvent.h"

using namespace std;

vector<Student> loadStudentsFromFile(const string& filename)
{
    vector<Student> students;
    ifstream file(filename);

    if (file.is_open())
    {
        string line;

        while (getline(file, line))
        {
            if (line.empty())
                continue;

            size_t pos1 = line.find(':');
            size_t pos2 = line.find(':', pos1 + 1);
            size_t pos3 = line.find(':', pos2 + 1);

            if (pos1 == string::npos ||
                pos2 == string::npos ||
                pos3 == string::npos)
            {
                continue;
            }

            unsigned int id =
                static_cast<unsigned int>(stoul(line.substr(0, pos1)));

            string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string email = line.substr(pos2 + 1, pos3 - pos2 - 1);
            string major = line.substr(pos3 + 1);

            students.emplace_back(name, email, major, id);
        }
    }

    return students;
}

// Read an integer within an allowed range.
// Rejects trailing text, overflow, and out-of-range values.
bool readInteger(
    const string& prompt,
    int& value,
    int minimum,
    int maximum)
{
    string line;

    while (true)
    {
        cout << prompt;

        if (!getline(cin, line))
            return false;

        istringstream input(line);
        int number;
        char extra;

        if ((input >> number) && !(input >> extra) &&
            number >= minimum && number <= maximum)
        {
            value = number;
            return true;
        }

        cout << "Please enter a whole number from "
             << minimum << " to " << maximum << ".\n";
    }
}

bool readEventNumber(const string& prompt, int& value)
{
    return readInteger(
        prompt, value, 1, numeric_limits<int>::max());
}

bool readEventText(const string& prompt, string& value)
{
    while (true)
    {
        cout << prompt;

        if (!getline(cin, value))
            return false;

        if (value.find_first_not_of(" \t\r\n") != string::npos)
            return true;

        cout << "This field cannot be blank.\n";
    }
}

bool createEventMenu(EventManager& eventManager)
{
    int eventId;
    int capacity;
    int eventType;

    string name;
    string description;
    string date;
    string time;
    string location;

    cout << "\n=== Create Event ===\n";

    // Collect the shared event information first.
    if (!readEventNumber("Enter Event ID: ", eventId))
        return false;

    if (eventManager.findEventById(eventId) != nullptr)
    {
        cout << "That Event ID is already in use.\n\n";
        return true;
    }

    if (!readEventNumber("Enter Event Capacity: ", capacity))
        return false;

    if (!readEventText("Enter Event Name: ", name))
        return false;

    if (!readEventText("Enter Event Description: ", description))
        return false;

    if (!readEventText("Enter Event Date (YYYY-MM-DD): ", date))
        return false;

    if (!readEventText("Enter Event Time (HH:MM): ", time))
        return false;

    if (!readEventText("Enter Event Location: ", location))
        return false;

    cout << "\nSelect Event Type:\n"
         << "1. Academic Event\n"
         << "2. Club Event\n"
         << "3. Career Event\n"
         << "4. Social Event\n";

    if (!readInteger("Enter Selection: ", eventType, 1, 4))
        return false;

    unique_ptr<Event> newEvent;

    if (eventType == 1)
    {
        string department;
        string speaker;

        if (!readEventText("Enter Department: ", department))
            return false;

        if (!readEventText("Enter Speaker: ", speaker))
            return false;

        newEvent = make_unique<AcademicEvent>(
            eventId, capacity, name, description,
            date, time, location, department, speaker);
    }
    else if (eventType == 2)
    {
        string clubName;

        if (!readEventText("Enter Club Name: ", clubName))
            return false;

        newEvent = make_unique<ClubEvent>(
            eventId, capacity, name, description,
            date, time, location, clubName);
    }
    else if (eventType == 3)
    {
        string company;
        string recruiter;

        if (!readEventText("Enter Company Name: ", company))
            return false;

        if (!readEventText("Enter Recruiter Name: ", recruiter))
            return false;

        newEvent = make_unique<CareerEvent>(
            eventId, capacity, name, description,
            date, time, location, company, recruiter);
    }
    else
    {
        int foodInput;
        string activity;

        if (!readInteger(
                "Is food provided? (1 for Yes, 0 for No): ",
                foodInput, 0, 1))
        {
            return false;
        }

        if (!readEventText("Enter Main Activity: ", activity))
            return false;

        bool foodProvided = (foodInput == 1);

        newEvent = make_unique<SocialEvent>(
            eventId, capacity, name, description,
            date, time, location, foodProvided, activity);
    }

    // Pass ownership to the shared event collection.
    if (eventManager.addEvent(std::move(newEvent)))
    {
        cout << "Event successfully created and added!\n\n";
    }
    else
    {
        cout << "Failed to add event. An event with ID "
             << eventId << " may already exist.\n\n";
    }

    return true;
}

bool viewEventsMenu(const EventManager& eventManager)
{
    int viewChoice;

    cout << "\n=== View Events ===\n"
         << "1. Find Event by ID\n"
         << "2. View All Events\n";

    if (!readInteger("Enter Selection: ", viewChoice, 1, 2))
        return false;

    if (viewChoice == 1)
    {
        int eventId;

        if (!readEventNumber("Enter Event ID: ", eventId))
            return false;

        eventManager.displayEvent(eventId);
    }
    else
    {
        eventManager.displayAllEvents();
    }

    cout << '\n';
    return true;
}

bool searchEventsMenu(const EventManager& eventManager)
{
    string keyword;

    cout << "\n=== Search Events ===\n";

    if (!readEventText(
            "Enter all or part of an event name: ", keyword))
    {
        return false;
    }

    eventManager.searchEventsByName(keyword);
    cout << '\n';

    return true;
}

int main()
{
    // Keep the same event collection throughout the menu session.
    EventManager eventManager;
    vector<Registration> registrations;
    vector<Student> students = loadStudentsFromFile("students.txt");
    int choice = 12;

    cout << "========================================\n"
         << "     CAMPUS EVENT MANAGEMENT SYSTEM     \n"
         << "========================================\n"
         << endl;

    while (choice != 0)
    {
        cout << "1. Add Student\n"
             << "2. View Students\n"
             << "3. Create Event\n"
             << "4. View Events\n"
             << "5. Search Events\n"
             << "6. Register Student for Event\n"
             << "7. Cancel Registration\n"
             << "8. View Student Registrations\n"
             << "9. View Event Attendees\n"
             << "10. View Organizers\n"
             << "11. System Reports\n"
             << "0. Exit\n\n";

        if (!readInteger("Enter Selection: ", choice, 0, 11))
            break;

        if (choice == 1)
        {
            string name;
            string email;
            string major;
            unsigned int id;
            bool idCheck = false;

            vector<Student> students =
                loadStudentsFromFile("students.txt");

            // Menu input has already consumed the newline.
            cout << "Enter Student Name: ";
            if (!getline(cin, name))
                return 0;

            cout << "Enter Student Email: ";
            if (!getline(cin, email))
                return 0;

            cout << "Enter Student Major: ";
            if (!getline(cin, major))
                return 0;

            cout << "Enter Student ID: ";

            while (!(cin >> id))
            {
                if (cin.eof())
                    return 0;

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Invalid input. Please enter a valid Student ID: ";
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            for (const auto& student : students)
            {
                if (student.getId() == id)
                {
                    idCheck = true;
                    break;
                }
            }

            if (idCheck)
            {
                cout << "That Student ID is already in use.\n\n";
            }
            else
            {
                ofstream outFile("students.txt", ios::app);

                if (outFile.is_open())
                {
                    outFile << id << ":" << name << ":"
                            << email << ":" << major << "\n";

                    outFile.close();
                    cout << "Student successfully added.\n\n";
                }
                else
                {
                    cout << "Error opening file for writing.\n\n";
                }
            }
        }
        else if (choice == 2)
        {
            int viewChoice = 0;

            vector<Student> students =
                loadStudentsFromFile("students.txt");

            cout << "1. Find by ID\n"
                 << "2. View All Students\n";

            if (!readInteger("Enter Selection: ", viewChoice, 1, 2))
                return 0;

            if (viewChoice == 1)
            {
                unsigned int searchId;
                bool found = false;

                cout << "Enter Student ID: ";

                while (!(cin >> searchId))
                {
                    if (cin.eof())
                        return 0;

                    cin.clear();
                    cin.ignore(
                        numeric_limits<streamsize>::max(), '\n');

                    cout << "Invalid input. "
                         << "Please enter a valid Student ID: ";
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                for (const auto& student : students)
                {
                    if (student.getId() == searchId)
                    {
                        cout << "Student Found:\n"
                             << "ID: " << student.getId() << "\n"
                             << "Name: " << student.getName() << "\n"
                             << "Email: " << student.getEmail() << "\n"
                             << "Major: " << student.getMajor() << "\n\n";

                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    cout << "Student with ID " << searchId
                         << " not found.\n\n";
                }
            }
            else
            {
                cout << "All Students:\n";

                for (const auto& student : students)
                {
                    cout << "ID: " << student.getId() << "\n"
                         << "Name: " << student.getName() << "\n"
                         << "Email: " << student.getEmail() << "\n"
                         << "Major: " << student.getMajor() << "\n\n";
                }

                cout << '\n';
            }
        }
        else if (choice == 3)
        {
            if (!createEventMenu(eventManager))
                return 0;
        }
        else if (choice == 4)
        {
            if (!viewEventsMenu(eventManager))
                return 0;
        }
        else if (choice == 5)
        {
            if (!searchEventsMenu(eventManager))
                return 0;
        }
        else if (choice == 6)
        {
           int studentID;
           int eventID;

           cout << "\n=== Register Student for Event ===\n";

           if (!readEventNumber("Enter Student ID: ", studentID))
               return 0;

            if (!readEventNumber("Enter Event ID: ", eventID))
                return 0;
            
            Student* selectedStudent = nullptr;

            for (auto& student : students)
            {
                if (student.getId() == static_cast<unsigned int>(studentID))
                {
                    selectedStudent = &student;
                    break;
                }
            }

            if (selectedStudent == nullptr)
            {
                string registrationDate;

                cout << "Student with ID " << studentID << " not found.\n";
                return 0;
            }

            // Check if the event exists
            Event* event = eventManager.findEventById(eventID);

            if (event == nullptr)
            {
                cout << "Event with ID " << eventID << " not found.\n";
                return 0;
            }

            string registrationDate;

            if (!readEventText("Enter Registration Date (YYYY-MM-DD): ", registrationDate))
            {
                return 0;
            }

            registrations.emplace_back(selectedStudent, event, registrationDate);

            cout << "Student with ID " << studentID
                 << " successfully registered for Event ID "
                 << eventID << ".\n\n";
        }
        else if (choice == 7)
        {
            int studentID;
            int eventID;

            bool found = false;

            cout << "\n===== Cancel Registration =====\n";

            if (!readEventNumber("Enter Student ID: ", studentID))
                return 0;
            
            if (!readEventNumber("Enter Event ID: ", eventID))
                return 0;

            for (auto& registration : registrations)
            {
                Student* student = registration.getStudent();
                Event* event = registration.getEvent();

                if (student != nullptr && event != nullptr &&
                    student->getId() == static_cast<unsigned int>(studentID) &&
                    event->getEventId() == eventID &&
                    registration.getStatus() == "Active") {

                    registration.cancel();

                    cout << "Registration cancelled successfully for Student ID"
                         << studentID
                         << "!\n\n";

                    found = true;
                    break;
                }
            }

            if (!found) {
            cout << "No active registration found for Student ID "
                << studentID
                << ".\n\n";
            }
        }
        
        else if (choice == 8)
        {
            int studentID;
            bool found = false;

            cout << "\n=== View Student Registrations ===\n";

            if (!readEventNumber("Enter Student ID: ", studentID))
                return 0;

            cout << "\nRegistered Events:\n";

            for (const auto& registration : registrations)
            {
                Student* student = registration.getStudent();
                Event* event = registration.getEvent();

                if (student != nullptr && event != nullptr &&
                    student->getId() == static_cast<unsigned int>(studentID))
                {
                    cout << "Event ID: " << event->getEventId() << "\n"
                         << "Event Name: " << event->getName() << "\n"
                         << "Registration Date: "
                         << registration.getRegistrationDate() << "\n"
                         << "Status: " << registration.getStatus() << "\n\n";

                    found = true;
                }
            }

            if (!found)
            {
                cout << "No registrations found for Student ID "
                     << studentID << ".\n\n";
            }
           
        }
        else if (choice == 9)
        {
            int eventID;

            bool found = false;

            cout << "\n=== View Event Attendees ===\n";

            if (!readEventNumber("Enter Event ID: ", eventID))
                return 0;

            Event* event = eventManager.findEventById(eventID);

            if (event == nullptr)
            {
                cout << "Event with ID " << eventID << " not found.\n";
                return 0;
            }

            for (const auto& registration : registrations)
            {
                Event* registeredEvent = registration.getEvent();
                Student* student = registration.getStudent();

                if (student != nullptr && registeredEvent != nullptr &&
                    registeredEvent->getEventId() == eventID)
                {
                    cout << "Student ID: " << student->getId() << "\n"
                         << "Student Name: " << student->getName() << "\n"
                         << "Registration Date: "
                         << registration.getRegistrationDate() << "\n"
                         << "Status: " << registration.getStatus() << "\n\n";

                    found = true;
                }
            }

            if (!found)
            {
                cout << "No attendees found for Event ID " << eventID << ".\n\n";
            }
        }
        else if (choice == 10)
        {
            int viewOrganizerChoice;

            cout << "\n===== View Organizers =====\n"
                 << "1. Find Organizer by ID\n"
                 << "2. View All Organizers\n";

            if (!readInteger("Enter Selection: ", viewOrganizerChoice, 1, 2))
                return 0;

            if (viewOrganizerChoice == 1)
            {
                string organizerID;
                bool found = false;

                if (!readEventText("Enter Organizer ID: ", organizerID))
                    return 0;

                vector<Organizer> organizers =
                    FileManager::loadOrganizersFromFile("organizers.txt");

                for (const auto& organizer : organizers)
                {
                    if (organizer.getOrganizerID() == organizerID)
                    {
                        cout << "Organizer Found:\n"
                             << "ID: " << organizer.getOrganizerID() << "\n"
                             << "Name: " << organizer.getName() << "\n"
                             << "Email: " << organizer.getEmail() << "\n\n"
                             << "Department: " << organizer.getDepartment() << "\n\n";

                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    cout << "Organizer with ID " << organizerID
                         << " not found.\n\n";
                }
            }
            else
            {
                vector<Organizer> organizers =
                    FileManager::loadOrganizersFromFile("organizers.txt");

                if (organizers.empty())
                {
                    cout << "No organizers found.\n\n";
                    continue;
                }

                cout << "All Organizers:\n";

                for (const auto& organizer : organizers)
                {
                    cout << "ID: " << organizer.getOrganizerID() << "\n"
                         << "Name: " << organizer.getName() << "\n"
                         << "Email: " << organizer.getEmail() << "\n\n";
                }

                cout << '\n';
            }
        }
        else if (choice == 11)
        {
            int ReportChoice;

            cout << "\n===== System Reports =====\n"
                 << "1. Event Report\n"
                 << "2. Student Report\n"
                 << "3. Registration Report\n";

            if (!readInteger("Enter Selection: ", ReportChoice, 1, 3))
                return 0;

            if (ReportChoice == 1)
            {
                cout << "\n=== Event Report ===\n";

                if (eventManager.getEvents().empty())
                {
                    cout << "No events available.\n\n";
                }
                else
                {
                    for (const auto& event : eventManager.getEvents())
                    {
                        int count = 0;

                        for (const auto& registration : registrations)
                        {
                            Event* registeredEvent = registration.getEvent();

                            if (registeredEvent != nullptr &&
                                registeredEvent->getEventId() == event->getEventId())
                            {
                                count++;
                            }
                        }

                        cout << "Event ID: " << event->getEventId() << "\n"
                             << "Event Name: " << event->getName() << "\n"
                             << "Capacity: " << event->getCapacity() << "\n"
                             << "Remaining Seats: " << (event->getCapacity() - count) << "\n\n";
                    }
                }
            }

            else if (ReportChoice == 2)
            {
                cout << "\n=== Student Report ===\n";

                vector<Student> students =
                    loadStudentsFromFile("students.txt");

                if (students.empty())
                {
                    cout << "No students available.\n\n";
                }
                else
                {
                    for (const auto& student : students)
                    {
                        int count = 0;

                        for (const auto& registration : registrations)
                        {
                            Student* registeredStudent = registration.getStudent();

                            if (registeredStudent != nullptr &&
                                registeredStudent->getId() == student.getId() &&
                                registration.getStatus() == "Active")
                            {
                                count++;
                            }
                        }

                        cout << "Student ID: " << student.getId() << "\n"
                             << "Name: " << student.getName() << "\n"
                             << "Email: " << student.getEmail() << "\n"
                             << "Major: " << student.getMajor() << "\n"
                             << "Registered Events: " << count << "\n\n";
                    }
                }
            }
            else if (ReportChoice == 3)
            {
                cout << "\n=== Registration Report ===\n";

                if (registrations.empty())
                {
                    cout << "No registrations available.\n\n";
                }
                else
                {
                    for (const auto& registration : registrations)
                    {
                        Student* student = registration.getStudent();
                        Event* event = registration.getEvent();

                        if (student != nullptr && event != nullptr)
                        {
                            cout << "Student ID: " << student->getId() << "\n"
                                 << "Student Name: " << student->getName() << "\n"
                                 << "Event ID: " << event->getEventId() << "\n"
                                 << "Event Name: " << event->getName() << "\n"
                                 << "Registration Date: "
                                 << registration.getRegistrationDate() << "\n"
                                 << "Status: " << registration.getStatus() << "\n\n";
                        }
                    }
                }
            }
        }
    }

    return 0;
}