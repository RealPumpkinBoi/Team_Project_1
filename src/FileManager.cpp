#include "FileManager.h"
#include "Student.h"

#include <fstream>
#include <iostream>

void FileManager::saveStudents(const std::vector<Student>& students) {
    std::ofstream outFile("students.txt");
    if (!outFile) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }

    for (const auto& student : students) {
        outFile << student.getId() << ":" << student.getName() << ":" << student.getEmail() << ":" << student.getMajor() << std::endl;
    }
    outFile.close();
}

void FileManager::saveStudent(const Student student) {
    std::ofstream outFile("students.txt");
    if (!outFile) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }

    outFile << student.getId() << ":" << student.getName() << ":" << student.getEmail() << ":" << student.getMajor() << std::endl;

    outFile.close();
}

void FileManager::loadStudents(std::vector<Student>& students) {
    std::ifstream inFile("students.txt");

    if (!inFile) {
        std::cerr << "Error opening file for reading." << std::endl;
        return;
    }

    std::string name;
	std::string email;
	std::string major;
    std::string idString;

    while (std::getline(inFile, idString, ':') &&
           std::getline(inFile, name, ':') &&
           std::getline(inFile, email, ':') &&
           std::getline(inFile, major)) {

        unsigned int id = std::stoul(idString);

        students.emplace_back(name, email, major, id);
    }
    inFile.close();
}
