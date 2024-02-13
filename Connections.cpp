// Connections.cpp

#include "Connections.h"

// Constructor with default values
Connection::Connection(const std::string n, const std::string c, int intA, int intB, double len)
    : name(n), code(c), intersectionA(intA), intersectionB(intB), length(len) {}

Connection Connection::parse(const std::string &line) {
    Connection connection;
    std::istringstream iss(line);
    iss >> connection.name >> connection.code >> connection.intersectionA >> connection.intersectionB >> connection.length;
    return connection;
}

// Overload the << operator to print a Connection object for debugging
std::ostream& operator<<(std::ostream& os, const Connection& connection) {
    os << "Name: " << connection.name << std::endl;
    os << "Code: " << connection.code << std::endl;
    os << "IntersectionA: " << connection.intersectionA << std::endl;
    os << "IntersectionB: " << connection.intersectionB << std::endl;
    os << "Length: " << connection.length << " miles" << std::endl;
    return os;
}
