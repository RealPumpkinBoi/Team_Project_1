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
        outFile << student.getName() << "," << student.getId() << std::endl;
    }
}

void FileManager::loadStudents(std::vector<Student>& students) {
    std::ifstream inFile("students.txt");

    if (!inFile) {
        std::cerr << "Error opening file for reading." << std::endl;
        return;
    }

    std::string name;
    std::string idString;

    while (std::getline(inFile, name, ',') &&
           std::getline(inFile, idString)) {

        unsigned int id = std::stoul(idString);

        students.emplace_back(name, "", "", id);
    }
}
