#include "SocialEvent.h"

#include <iostream>
#include <string>

int main() {

private:
    std::string type;

public: 
    SocialEvent(const std::string& name;
                const std:string& id;
                const std::string& date;
                const std::string& location;
                const std::string& description;
                int capacity;
                const std::string& type)
    : Event(name, id, date, location, description, capacity), type(type) {}

    // Getters
    std::string getType() const {
        return type;
    
    // Setters
    void setType (const std::string& type) {
        this->type = type;
    }

    // Display
    void displayEventDetails() const {
        Event::displayEventDetails();
        std::cout << "Type: " << type << std::endl;
        


}