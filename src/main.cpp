#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

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

using namespace std;

// Helper Functions


int main()
{
	//Create an instance of EventManager
	EventManager eventManager;

	int choice = 12;
	while (choice > 0)
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
			<< "0. Exit\n\n"
			<< "Enter Selection: ";
		cin >> choice;
		while (choice > 11 || choice < 0)
		{
			cout << "Invalid selection.\n\nEnter Selection: ";
			cin >> choice;
		}
		if (choice == 1)
		{
			string name;
			string email;
			string major;
			unsigned int id;
			bool idCheck = false;
			vector<Student> students = loadStudents("students.txt");

			// Prompt for student data
			cout << "Enter Student Name: ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, name);

			cout << "Enter Student Email: ";
			getline(cin, email);

			cout << "Enter Student Major: ";
			getline(cin, major);

			cout << "Enter Student ID: ";
			while (!(cin >> id))
			{
				cout << "Invalid input. Please enter a valid Student ID: ";
				cin.clear();
			}

			// Check for existing ID
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
				cout << "That Student ID is already in use.\n\n\n";
			}
			else
			{
				ofstream outFile("students.txt", ios::app);
				if (outFile.is_open())
				{
					outFile << id << ":" << name << ":" << email << ":" << major << "\n";
					outFile.close();
					cout << "Student successfully added.\n\n\n";
				}
			}
			
		}
		else if (choice == 2)
		{
			int viewChoice = 0;
			vector<Student> students = loadStudents("students.txt");
			cout << "1. Find by ID\n"
				<< "2. View All Students\n"
				<< "Enter Selection: ";
			cin >> viewChoice;

			while (viewChoice > 2 || viewChoice < 1)
			{
				cout << "Invalid selection.\n\nEnter Selection: ";
				cin >> viewChoice;
			}

			if (viewChoice == 1)
			{
				unsigned int searchId;
				bool found = false;
				cout << "Enter Student ID: ";
				while (!(cin >> searchId))
				{
					cout << "Invalid input. Please enter a valid Student ID: ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
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
					cout << "Student with ID " << searchId << " not found.\n\n";
				}
			}

			if (viewChoice == 2)
			{
				cout << "All Students:\n";
				for (const auto& student : students)
				{
					cout << "ID: " << student.getId() << "\n"
						<< "Name: " << student.getName() << "\n"
						<< "Email: " << student.getEmail() << "\n"
						<< "Major: " << student.getMajor() << "\n\n";
				}
				cout << "\n\n";
			}
		}
		else if (choice == 3)
		{
			// Base Event variables
			int eventId;
			int	capacity;
			string name;
			string description;
			string  date;
			string time; 
			string location;

			cout << "Enter Event ID: ";
			while (!(cin >> eventId))
			{
				cout << "Invalid input. Please enter a valid Event ID: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			cout << "Enter Event Capacity: ";
			while (!(cin >> capacity))
			{
				cout << "Invalid input. Please enter a valid Capacity: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			// Clear buffer before reading strings
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "Enter Event Name: ";
			getline(cin, name);

			cout << "Enter Event Description: ";
			getline(cin, description);

			cout << "Enter Event Date: ";
			getline(cin, date);

			cout << "Enter Event Time: ";
			getline(cin, time);

			cout << "Enter Event Location: ";
			getline(cin, location);

			/*With base information collected, now we can ask for the derived
			class information based on the event type*/

			// Determine Derived Event Type
			int eventType = 0;
			cout << "\nSelect Event Type:\n"
				<< "1. Academic Event\n"
				<< "2. Club Event\n"
				<< "3. Career Event\n"
				<< "4. Social Event\n"
				<< "Enter Selection: ";
			cin >> eventType;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			std::unique_ptr<Event> newEvent = nullptr;

			if (eventType == 1)
			{
				string department;
				string speaker;
				cout << "Enter Department: ";
				getline(cin, department);
				cout << "Enter Speaker: ";
				getline(cin, speaker);
				// Create AcademicEvent and assign to newEvent
				newEvent = make_unique<AcademicEvent>(eventId, capacity, name, description, date, time, location, department, speaker);
			}
			else if (eventType == 2)
			{
				string clubName;
				cout << "Enter Club Name: ";
				getline(cin, clubName);
				// Create ClubEvent and assign to newEvent
				newEvent = make_unique<ClubEvent>(eventId, capacity, name, description, date, time, location, clubName);
			}
			else if (eventType == 3)
			{
				string company;
				string recruiter;
				cout << "Enter Company Name: ";
				getline(cin, company);
				cout << "Enter Recruiter Name: ";
				getline(cin, recruiter);
				// Create CareerEvent and assign to newEvent
				newEvent = make_unique<CareerEvent>(eventId, capacity, name, description, date, time, location, company, recruiter);
			}
			else if (eventType == 4)
			{
				int foodInput;
				bool foodProvided;
				string activity;

				cout << "Is food provided? (1 for Yes, 0 for No): ";
				while (!(cin >> foodInput) || (foodInput != 0 && foodInput != 1))
				{
					cout << "Invalid input. Please enter 1 for Yes or 0 for No: ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				foodProvided = (foodInput == 1);

				// Clear buffer before reading the string
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				cout << "Enter Main Activity: ";
				getline(cin, activity);

				newEvent = make_unique<SocialEvent>(eventId, capacity, name, description, date, time, location, foodProvided, activity);
			}
			else
			{
				cout << "Invalid Event Type selected.\n\n";
			}

			// Pass ownership to EventManager
			if (newEvent)
			{
				if (eventManager.addEvent(std::move(newEvent)))
				{
					cout << "Event successfully created and added!\n\n";
				}
				else
				{
					cout << "Failed to add event. An event with ID " << eventId << " may already exist.\n\n";
				}
			}
		}
		else if (choice == 4)
		{
			// View Events
		}
		else if (choice == 5)
		{
			// Search Events
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
