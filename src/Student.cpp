#include "Student.h"

#include <iostream>
#include <string>

Student::Student(const std::string& name, 
                 const std::string& id, 
                 const std::string& email, 
                 const std::string& major)
        : studentName(name), studentID(id), studentEmail(email), studentMajor(major) {}

Student::~Student() {}

// Getters
std::string Student::getName() const {
    return studentName;
}
std::string Student::getId() const {
    return studentID;
}
std::string Student::getEmail() const {
    return studentEmail;
}
std::string Student::getMajor() const {
    return studentMajor;
}

// Setters
void Student::setName(const std::string& name) {
    studentName = name;
}
void Student::setId(const std::string& id) {
    studentID = id;
}
void Student::setEmail(const std::string& email) {
    studentEmail = email;
}
void Student::setMajor(const std::string& major) {
    studentMajor = major;
}

// Display
void Student::displayStudentDetails() const {
    std::cout << "Student Name: " << studentName << std::endl;
    std::cout << "Student ID: " << studentID << std::endl;
    std::cout << "Student Email: " << studentEmail << std::endl;
    std::cout << "Student Major: " << studentMajor << std::endl;
}

