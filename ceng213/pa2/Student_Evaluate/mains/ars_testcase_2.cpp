#include <iostream>

#include "AirlineReservationSystem.h"
//#include "../AirlineReservationSystem.h"

/*
 * Case 2 : Default constructor; addPassenger; print.
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

    std::cout << "-> Printing the system." << std::endl;

    ars.print();

    return 0;
}
