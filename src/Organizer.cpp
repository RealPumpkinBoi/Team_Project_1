#include "../include/Organizer.h"
#include <iostream>
#include <sstream>

Organizer::Organizer() 
    : organizerID(""), name(""), email(""), department("") {}

Organizer::Organizer(const std::string& id, const std::string& name, 
                     const std::string& email, const std::string& department)
    : organizerID(id), name(name), email(email), department(department) {}

Organizer::~Organizer() {}

std::string Organizer::getOrganizerID() const 
{
    return organizerID;
}

std::string Organizer::getName() const 
{
    return name;
}

std::string Organizer::getEmail() const 
{
    return email;
}

std::string Organizer::getDepartment() const 
{
    return department;
}

void Organizer::setOrganizerID(const std::string& id)
{
    organizerID = id;
}

void Organizer::setName(const std::string& n) 
{
    name = n;
}

void Organizer::setEmail(const std::string& e)
{
    email = e;
}

void Organizer::setDepartment(const std::string& dept)
{
    department = dept;
}

void Organizer::display() const 
{
    std::cout << "ID: " << organizerID 
              << " | Name: " << name 
              << " | Email: " << email 
              << " | Dept: " << department << std::endl;
}

std::string Organizer::serialize() const
{
    return organizerID + "|" + name + "|" + email + "|" + department;
}

Organizer Organizer::deserialize(const std::string& line) 
{
    std::stringstream ss(line);
    std::string id, n, e, dept;

    std::getline(ss, id, '|');
    std::getline(ss, n, '|');
    std::getline(ss, e, '|');
    std::getline(ss, dept, '|');

    return Organizer(id, n, e, dept);
}
