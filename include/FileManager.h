#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <string>

class Student;
class Event;
class Organizer;
class Registration;

class FileManager {

public:
    static void saveStudents(const std::vector<Student>& students);
	static void saveStudent(const Student student);
    static void loadStudents(std::vector<Student>& students);
};

#endif
