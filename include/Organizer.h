#ifndef ORGANIZER_H
#define ORGANIZER_H

#include <string>

class Organizer 
{
private:
    std::string organizerID;
    std::string name;
    std::string email;
    std::string department;

public:
    Organizer();
    Organizer(const std::string& id, const std::string& name, 
              const std::string& email, const std::string& department);
    ~Organizer();

    // Accessors
    std::string getOrganizerID() const;
    std::string getName() const;
    std::string getEmail() const;
    std::string getDepartment() const;

    // Mutators
    void setOrganizerID(const std::string& id);
    void setName(const std::string& name);
    void setEmail(const std::string& email);
    void setDepartment(const std::string& department);

    // Operations & Persistence
    void display() const;
    std::string serialize() const;
    static Organizer deserialize(const std::string& line);
};

#endif
