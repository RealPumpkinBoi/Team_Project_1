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
vector<Student> loadStudentsFromFile(const string& filename)
{
	vector<Student> students;
	ifstream file(filename);
	if (file.is_open())
	{
		string line;
		while (getline(file, line))
		{
			if (line.empty()) continue;
			size_t pos1 = line.find(':');
			size_t pos2 = line.find(':', pos1 + 1);
			size_t pos3 = line.find(':', pos2 + 1);
			if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos)
				continue; // Skip malformed lines
			unsigned int id = static_cast<unsigned int>(stoul(line.substr(0, pos1)));
			string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
			string email = line.substr(pos2 + 1, pos3 - pos2 - 1);
			string major = line.substr(pos3 + 1);
			students.emplace_back(name, email, major, id);
		}
		file.close();
	}
	return students;
}


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
			vector<Student> students = loadStudentsFromFile("students.txt");

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
				else
				{
					cout << "Error opening file for writing.\n\n\n";
				}
			}
			
		}
		else if (choice == 2)
		{
			int viewChoice = 0;
			vector<Student> students = loadStudentsFromFile("students.txt");
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
