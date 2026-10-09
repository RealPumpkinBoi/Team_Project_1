#ifndef EVENT_H
#define EVENT_H

#include <string>


class Event 
{
private:

	/*********************************************************
	 * eventId 	-------- Event's ID # ----------------- Int
	 * capacity -------- Event's capacity ------------- Int
	 * name ------------ Event Name ------------------- string
	 * description ----- Event's description ---------- string
	 * date ------------ Event's meeting Date --------- string
	 * time ------------ Event's meeting time --------- string
	 * location -------- Event's location ------------- string
	 **********************************************************/
    int eventId;
    int capacity;
    std::string name;
    std::string description;
    std::string date;
    std::string time;
    std::string location;

public:
    //Constructor - no default at the moment
    Event(int id,
    	  int cap,
    	const std::string& n,
		const std::string& desc,
        const std::string& d,
		const std::string& t,
        const std::string& loc);

    //I(Pablo) assumed we would only need getters to display information.
    //Setters can be implemented if advised
    int getEventId() const;
    int getCapacity() const;
    std::string getName() const;
    std::string getDescription() const;
    std::string getDate() const;
    std::string getTime() const;
    std::string getLocation() const;

};

#endif
