#include "AirlineReservationSystem.h"

void AirlineReservationSystem::addPassenger(const std::string &firstname, const std::string &lastname) {
    passengers.insert(Passenger(firstname, lastname));
}

Passenger *AirlineReservationSystem::searchPassenger(const std::string &firstname, const std::string &lastname) {
    return &passengers.search(Passenger(firstname, lastname))->data;
}

void AirlineReservationSystem::addFlight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity) {
    flights.insert(Flight(flightCode, departureTime, arrivalTime, departureCity, arrivalCity, economyCapacity, businessCapacity));
}

std::vector<Flight *> AirlineReservationSystem::searchFlight(const std::string &departureCity, const std::string &arrivalCity) {
    std::vector<Flight *> v;
    for(BSTNode<Flight> *curr = flights.getRoot(); curr; curr=flights.getSuccessor(curr, preorder)){
        if(curr->data.getDepartureCity()==departureCity && curr->data.getArrivalCity()==arrivalCity){
            v.push_back(&curr->data);
        }
    }
    return v;
}

void AirlineReservationSystem::issueTicket(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    for(BSTNode<Flight> *curr = flights.getRoot(); curr; curr=flights.getSuccessor(curr, preorder)){
        if(curr->data.getFlightCode()==flightCode){
            curr->data.addTicket(Ticket(searchPassenger(firstname, lastname), &curr->data, ticketType));
            break;
        }
    }
}


void AirlineReservationSystem::saveFreeTicketRequest(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    for(BSTNode<Flight> *curr = flights.getRoot(); curr; curr=flights.getSuccessor(curr, preorder)){
        if(curr->data.getFlightCode()==flightCode){
            freeTicketRequests.enqueue(Ticket(searchPassenger(firstname, lastname), &curr->data, ticketType));
            break;
        }
    }
}

void AirlineReservationSystem::executeTheFlight(const std::string &flightCode) {
    int len = freeTicketRequests.size();
    for(BSTNode<Flight> *curr = flights.getRoot(); curr; curr=flights.getSuccessor(curr, preorder)){
        if(curr->data.getFlightCode()==flightCode){
            Flight &flight = curr->data;
            flight.setCompleted(true);
            for(int i=0; i<len; i++){
                Ticket ticket = freeTicketRequests.dequeue();
                if(!(ticket.getFlight()->getFlightCode()==flightCode && flight.addTicket(ticket))){
                    freeTicketRequests.enqueue(ticket);
                }
            }
            break;
        }
    }
}

void AirlineReservationSystem::print() const {
    std::cout << "# Printing the airline reservation system ..." << std::endl;

    std::cout << "# Passengers:" << std::endl;
    passengers.print(inorder);

    std::cout << "# Flights:" << std::endl;
    flights.print(inorder);

    std::cout << "# Free ticket requests:" << std::endl;
    freeTicketRequests.print();

    std::cout << "# Printing is done." << std::endl;
}