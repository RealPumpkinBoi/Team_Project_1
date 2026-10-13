#ifndef Student_H
#define Student_H

#include <string>
#include <iostream>

class Student
{
private:
	std::string studentName;
	std::string email;
	std::string major;
	unsigned int id;
public:
	// Constructor
	Student(const std::string& name, const std::string& email, const std::string& major, unsigned int id);

	// Getters
	std::string getName() const;
	std::string getEmail() const;
	std::string getMajor() const;
	unsigned int getId() const;



};

#endif
