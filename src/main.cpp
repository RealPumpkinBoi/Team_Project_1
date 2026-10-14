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
    int choice = 12;

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
                loadStudents("students.txt");

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
                loadStudents("students.txt");

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
            // Register Student for Event
        }
        else if (choice == 7)
        {
            // Cancel Registration
        }
        else if (choice == 8)
        {
            // View Student Registrations
        }
        else if (choice == 9)
        {
            // View Event Attendees
        }
        else if (choice == 10)
        {
            // View Organizers
        }
        else if (choice == 11)
        {
            // System Reports
        }
    }

    return 0;
}