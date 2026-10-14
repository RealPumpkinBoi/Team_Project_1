#ifndef CAREEREVENT_H
#define CAREEREVENT_H

#include "Event.h"

#include <string>

class CareerEvent : public Event {

private:
    std::string companyName;
    std::string recruiterName;

public:
    CareerEvent(const std::string& name, 
                const std::string& id,
                const std::string& date,
                const std::string& location,        
                const std::string& description,
                int capacity,
                const std::string& companyName,
                const std::string& recruiterName);

    // Getters
    std::string getCompanyName() const;
    std::string getRecruiterName() const;

    // Setters
    void setCompanyName(const std::string& companyName);
    void setRecruiterName(const std::string& recruiterName);

    // Display
    void displayDetails() const override;
};

#endif // CAREEREVENT_H