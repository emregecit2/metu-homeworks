#include <iostream>

#include "AirlineReservationSystem.h"
//#include "../AirlineReservationSystem.h"

/*
 * Case 7 : Default constructor; addPassenger, addFlight, saveFreeTicketRequest; print.
 */
int main() {

    std::cout << "-> Creating an airline reservation system instance with default constructor." << std::endl;

    AirlineReservationSystem ars;

    std::cout << "-> Making some passenger insertions to the system." << std::endl;

    ars.addPassenger("jack", "sophia");
    ars.addPassenger("archie", "rosie");
    ars.addPassenger("harry", "isabella");
    ars.addPassenger("oscar", "lily");
    ars.addPassenger("leo", "ivy");
    ars.addPassenger("kate", "sophia");

    std::cout << "-> Making some flight insertions to the system." << std::endl;

    ars.addFlight("DS7050", "20/12/2021 10:00", "20/12/2021 11:30", "Ankara", "Istanbul", 200, 10);
    ars.addFlight("DS7030", "20/12/2021 11:00", "20/12/2021 12:30", "Ankara", "Brussels", 200, 10);
    ars.addFlight("DS7070", "20/12/2021 12:00", "20/12/2021 13:30", "Ankara", "Amsterdam", 200, 10);
    ars.addFlight("DS7040", "20/12/2021 13:00", "20/12/2021 14:30", "Ankara", "London", 200, 10);
    ars.addFlight("DS7060", "20/12/2021 14:00", "20/12/2021 15:30", "Ankara", "Rome", 200, 10);
    ars.addFlight("DS7020", "20/12/2021 15:00", "20/12/2021 16:30", "Ankara", "London", 100, 5);
    ars.addFlight("DS7080", "20/12/2021 16:00", "20/12/2021 17:30", "Ankara", "London", 50, 0);

    std::cout << "-> Saving some free ticket requests." << std::endl;

    ars.saveFreeTicketRequest("jack", "sophia", "DS7050", economy);
    ars.saveFreeTicketRequest("archie", "rosie", "DS7040", economy);
    ars.saveFreeTicketRequest("harry", "isabella", "DS7040", economy);
    ars.saveFreeTicketRequest("oscar", "lily", "DS7080", economy);
    ars.saveFreeTicketRequest("leo", "ivy", "DS7080", economy);
    ars.saveFreeTicketRequest("kate", "sophia", "DS7080", business);

    std::cout << "-> Printing the system." << std::endl;

    ars.print();

    return 0;
}
