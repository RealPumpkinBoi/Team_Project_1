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
#include "Event.h"
#include "ClubEvent.h"
#include "CareerEvent.h"
#include "AcademicEvent.h"

using namespace std;

// Helper Functions



int main()
{
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
			ifstream file("students.txt");

			// Read existing records if students.txt exists
			vector<unsigned int> students;
			if (file.is_open())
			{
				string fileLine;
				while (getline(file, fileLine))
				{
					if (fileLine.empty()) continue;

					// Extract the ID: handles lines formatted as "ID:name:email:major"
					size_t colonPos = fileLine.find(':');
					string idToken = (colonPos != string::npos) ? fileLine.substr(0, colonPos) : fileLine;

					try
					{
						unsigned int existingId = static_cast<unsigned int>(stoul(idToken));
						students.push_back(existingId);
					}
					catch (const exception&)
					{
						// Skip invalid/unparseable lines
						continue;
					}
				}
				file.close();
			}

			// Prompt for student data
			cout << "Enter Student Name: ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, name);

			cout << "Enter Student ID: ";
			while (!(cin >> id))
			{
				cout << "Invalid input. Please enter a valid Student ID: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			// Check for existing ID
			for (size_t i = 0; i < students.size(); i++)
			{
				if (students[i].getId() == id)
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
				else
				{
					cout << "Error opening file for writing.\n\n\n";
				}
			}
			
		}
		else if (choice == 2)
		{
			// View Students
		}
		else if (choice == 3)
		{
			// Create Event
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
