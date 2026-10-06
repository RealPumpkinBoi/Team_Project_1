#include "Student.h"

Student(const std::string& name, const std::string& email, const std::string& major, unsigned int id)
{
	studentName = name;
	this->email = email;
	this->major = major;
	this->id = id;
}

std::string Student::getName() const
{
	return studentName;
}
std::string Student::getEmail() const
{
	return email;
}
std:string Student::getMajor() const
{
	return major;
}
unsigned int Student::getId() const
{
	return id;
}
