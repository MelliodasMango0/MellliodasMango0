// Connections.hpp

#ifndef Connections_h
#define Connections_h

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class Connection {
public:
    std::string name;
    std::string code;
    int intersectionA, intersectionB;
    double length;

    // Constructor with default values
    Connection(const std::string n = "", const std::string c = "", int intA = 0, int intB = 0, double len = 0.0);

    // Parse a line to create a Connection object
    static Connection parse(const std::string &line);

    // Overload the << operator to print a Connection object for debugging
    friend std::ostream& operator<<(std::ostream& os, const Connection& connection);
};

#endif /* Connections_hpp */
