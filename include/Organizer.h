#ifndef ORGANIZER_H
#define ORGANIZER_H

class Organizer 
{
private:
    char organizerID[32];
    char name[64];
    char email[64];
    char department[64];

public:
    Organizer();
    Organizer(const char* id, const char* name, const char* email, const char* dept);
    ~Organizer();

    // Accessors
    const char* getOrganizerID() const;
    const char* getName() const;
    const char* getEmail() const;
    const char* getDepartment() const;

    // Mutators
    void setOrganizerID(const char* id);
    void setName(const char* name);
    void setEmail(const char* email);
    void setDepartment(const char* department);

    // Display & Serialization
    void display() const;
    void serialize(char* buffer, int bufferSize) const;
    static Organizer deserialize(const char* line);
};

#endif // ORGANIZER_H
