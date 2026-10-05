#include "../include/Registration.h"

Registration::Registration(Student* student, Event* event,
                           const std::string& registrationDate)
    : student(student),
      event(event),
      registrationDate(registrationDate),
      status("Active") {
}

Student* Registration::getStudent() const {
    return student;
}

Event* Registration::getEvent() const {
    return event;
}

std::string Registration::getRegistrationDate() const {
    return registrationDate;
}

std::string Registration::getStatus() const {
    return status;
}

void Registration::cancel() {
    status = "Cancelled";
}