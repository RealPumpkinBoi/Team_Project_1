#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <string>

class Student;
class Event;

class Registration {
private:
    Student* student;
    Event* event;
    std::string registrationDate;
    std::string status;

public:
    Registration(Student* student, Event* event,
                 const std::string& registrationDate);

    Student* getStudent() const;
    Event* getEvent() const;
    std::string getRegistrationDate() const;
    std::string getStatus() const;

    void cancel();
};

#endif