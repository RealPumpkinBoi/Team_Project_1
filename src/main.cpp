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

// Existing student file loader.
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

// Read a positive integer using the entire input line.
bool readEventNumber(const string& prompt, int& value)
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

        if ((input >> number) && !(input >> extra) && number > 0)
        {
            value = number;
            return true;
        }

        cout << "Please enter a positive whole number.\n";
    }
}

// Read a required text field.
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

// Read the main menu selection, including 0 for Exit.
bool readMenuChoice(int& choice)
{
    string line;

    while (true)
    {
        cout << "Enter Selection: ";

        if (!getline(cin, line))
            return false;

        istringstream input(line);
        int number;
        char extra;

        if ((input >> number) && !(input >> extra) &&
            number >= 0 && number <= 11)
        {
            choice = number;
            return true;
        }

        cout << "Please enter a whole number from 0 to 11.\n";
    }
}

bool createEventMenu(EventManager& eventManager)
{
    int eventType;
    int eventId;
    int capacity;

    string name;
    string description;
    string date;
    string time;
    string location;

    cout << "\n=== Create Event ===\n"
         << "1. Academic Event\n"
         << "2. Club Event\n"
         << "3. Career Event\n"
         << "4. Social Event\n";

    while (true)
    {
        if (!readEventNumber("Enter event type: ", eventType))
            return false;

        if (eventType <= 4)
            break;

        cout << "Please choose an event type from 1 to 4.\n";
    }

    if (!readEventNumber("Enter Event ID: ", eventId))
        return false;

    if (eventManager.findEventById(eventId) != nullptr)
    {
        cout << "That Event ID is already in use.\n\n";
        return true;
    }

    if (!readEventText("Event name: ", name))
        return false;

    if (!readEventText("Description: ", description))
        return false;

    if (!readEventText("Date (YYYY-MM-DD): ", date))
        return false;

    if (!readEventText("Time (HH:MM): ", time))
        return false;

    if (!readEventText("Location: ", location))
        return false;

    if (!readEventNumber("Maximum capacity: ", capacity))
        return false;

    unique_ptr<Event> event;

    if (eventType == 1)
    {
        string department;
        string speaker;

        if (!readEventText("Department: ", department))
            return false;

        if (!readEventText("Speaker: ", speaker))
            return false;

        event = make_unique<AcademicEvent>(
            eventId, capacity, name, description,
            date, time, location, department, speaker);
    }
    else if (eventType == 2)
    {
        string clubName;

        if (!readEventText("Club name: ", clubName))
            return false;

        event = make_unique<ClubEvent>(
            eventId, capacity, name, description,
            date, time, location, clubName);
    }
    else if (eventType == 3)
    {
        string companyName;
        string recruiterName;

        if (!readEventText("Company name: ", companyName))
            return false;

        if (!readEventText("Recruiter name: ", recruiterName))
            return false;

        event = make_unique<CareerEvent>(
            eventId, capacity, name, description,
            date, time, location, companyName, recruiterName);
    }
    else
    {
        int foodChoice;
        string mainActivity;

        cout << "Food provided:\n"
             << "1. Yes\n"
             << "2. No\n";

        while (true)
        {
            if (!readEventNumber("Enter Selection: ", foodChoice))
                return false;

            if (foodChoice <= 2)
                break;

            cout << "Please choose 1 for Yes or 2 for No.\n";
        }

        if (!readEventText("Main activity: ", mainActivity))
            return false;

        bool providesFood = (foodChoice == 1);

        event = make_unique<SocialEvent>(
            eventId, capacity, name, description,
            date, time, location, providesFood, mainActivity);
    }

    if (eventManager.addEvent(std::move(event)))
        cout << "Event successfully created.\n\n";
    else
        cout << "Event could not be added.\n\n";

    return true;
}

bool viewEventsMenu(const EventManager& eventManager)
{
    int viewChoice;

    cout << "\n=== View Events ===\n"
         << "1. Find Event by ID\n"
         << "2. View All Events\n";

    if (!readEventNumber("Enter Selection: ", viewChoice))
        return false;

    if (viewChoice == 1)
    {
        int eventId;

        if (!readEventNumber("Enter Event ID: ", eventId))
            return false;

        eventManager.displayEvent(eventId);
    }
    else if (viewChoice == 2)
    {
        eventManager.displayAllEvents();
    }
    else
    {
        cout << "Invalid selection.\n";
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
    // One collection shared by Create, View, and Search.
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

        if (!readMenuChoice(choice))
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
                 << "2. View All Students\n"
                 << "Enter Selection: ";

            while (true)
            {
                if (cin >> viewChoice)
                {
                    cin.ignore(
                        numeric_limits<streamsize>::max(), '\n');

                    if (viewChoice >= 1 && viewChoice <= 2)
                        break;
                }
                else
                {
                    if (cin.eof())
                        return 0;

                    cin.clear();
                    cin.ignore(
                        numeric_limits<streamsize>::max(), '\n');
                }

                cout << "Invalid selection.\nEnter Selection: ";
            }

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