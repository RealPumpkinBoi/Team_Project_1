#ifndef EVENT_H
#define EVENT_H

class Event {
private:
    int eventId;
    int capacity;

public:
    Event(int eventId, int capacity);

    int getEventId() const;
    int getCapacity() const;
};

#endif