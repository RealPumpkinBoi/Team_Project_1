#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {

private:
    std::string studentName;
    std::string studentID;
    std::string studentEmail;
    std::string studentMajor;

public:
    Student(const std::string& name, const std::string& id, const std::string& email, const std::string& major);
    ~Student();

    // Getters
    std::string getName() const;
    std::string getId() const;
    std::string getEmail() const;
    std::string getMajor() const;

    // Setters
    void setName(const std::string& name);
    void setId(const std::string& id);
    void setEmail(const std::string& email);
    void setMajor(const std::string& major);

    // Display
    void displayStudentDetails() const;
};

#endif // STUDENT_H