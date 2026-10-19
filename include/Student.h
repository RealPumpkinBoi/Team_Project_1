
#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
private:
    std::string studentName;
    std::string email;
    std::string major;
    unsigned int id;

public:
    Student(const std::string& name,
            const std::string& email,
            const std::string& major,
            unsigned int id);

    std::string getName() const;
    std::string getEmail() const;
    std::string getMajor() const;
    unsigned int getId() const;
};

#endif
