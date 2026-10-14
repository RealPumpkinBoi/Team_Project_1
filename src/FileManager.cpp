#include "FileManager.h"
#include "Student.h"
#include "Organizer.h"

#include <fstream>
#include <iostream>
#include <string>

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

std::vector<Student> FileManager::loadStudentsFromFile(const std::string& filename) {
    std::vector<Student> students;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file for reading." << std::endl;
        return students;
    }

    std::string name;
    std::string idString;

    while (std::getline(file, name, ',') &&
           std::getline(file, idString)) {

        unsigned int id = std::stoul(idString);

        students.emplace_back(name, "", "", id);
    }

    file.close();

    return students;
}

std::vector<Organizer> FileManager::loadOrganizersFromFile(
    const std::string& filename)
{
    std::vector<Organizer> organizers;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Error opening organizer file.\n";
        return organizers;
    }

    std::string line;

    while (std::getline(file, line))
    {
        if (!line.empty())
        {
            organizers.push_back(Organizer::deserialize(line));
        }
    }

    return organizers;
}