#include <iostream>

#include "AirlineReservationSystem.h"
//#include "../AirlineReservationSystem.h"

/*
 * Case 1 : Default constructor; print.
 */
int main() {

    std::cout << "-> Creating an airline reservation system instance with default constructor." << std::endl;

    AirlineReservationSystem ars;

    std::cout << "-> Printing the system." << std::endl;

    ars.print();

    return 0;
}
