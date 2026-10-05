#include "../include/Event.h"

Event::Event(int eventId, int capacity)
    : eventId(eventId), capacity(capacity) {
}

int Event::getEventId() const {
    return eventId;
}

int Event::getCapacity() const {
    return capacity;
}