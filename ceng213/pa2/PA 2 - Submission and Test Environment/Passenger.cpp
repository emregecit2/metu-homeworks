#include "Passenger.h"
#define min(a,b) (a<b?a:b)

Passenger::Passenger(std::string firstname, std::string lastname) {
    this->firstname = firstname;
    this->lastname = lastname;
}

const std::string &Passenger::getFirstname() const {
    return firstname;
}

const std::string &Passenger::getLastname() const {
    return lastname;
}

bool Passenger::operator<(const Passenger &rhs) const {
    for(int i=0; i < min(lastname.size(), rhs.lastname.size()); i++){
        if(lastname[i]!=rhs.lastname[i]){
            return lastname[i] < rhs.lastname[i];
        }
    }
    for(int i=0; i < min(firstname.size(), rhs.firstname.size()); i++){
        if(firstname[i]!=rhs.firstname[i]){
            return firstname[i] < rhs.firstname[i];
        }
    }
}

bool Passenger::operator>(const Passenger &rhs) const {
    return rhs < *this;
}

bool Passenger::operator==(const Passenger &rhs) const {
    return firstname == rhs.firstname && lastname == rhs.lastname;
}

bool Passenger::operator!=(const Passenger &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Passenger &passenger) {
    os << "Passenger(firstname: " << passenger.firstname;
    os << ", lastname: " << passenger.lastname << ")";
    return os;
}
