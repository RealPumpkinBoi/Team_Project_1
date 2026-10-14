#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Organizer.h"
#include "Student.h"

#include <vector>
#include <string>

class Student;
class Event;
class Organizer;
class Registration;

class FileManager {

public:
    static void saveStudents(const std::vector<Student>& students);
    static void loadStudents(std::vector<Student>& students);

    static std::vector<Student> loadStudentsFromFile(const std::string& filename);
    static std::vector<Organizer> loadOrganizersFromFile(const std::string& filename);
};

#endif
