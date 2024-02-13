// Intersections.cpp

#include "Intersections.h"

// Parse a line to create an Intersection object
Intersection Intersection::parse(const std::string &line) {
    double longi = stof(line.substr(0, 9));
    double lat = stof(line.substr(9, 10));
    double dist = stof(line.substr(19, 8));
    std::string st = line.substr(28, 2);
    std::string np = line.substr(31, std::string::npos);
    return Intersection(longi, lat, dist, np, st);
}

// Add a connection to the Intersection
void Intersection::add_connection(const Connection &connection) {
    connections.push_back(connection);
}

// Overload the << operator to print an Intersection object
std::ostream& operator<<(std::ostream& os, const Intersection& intersection) {
    os << "Longitude: " << intersection.longitude << std::endl;
    os << "Latitude: " << intersection.latitude << std::endl;
    os << "Distance from place: " << intersection.dist_from_place << " miles" << std::endl;
    os << "State: " << intersection.state << std::endl;
    os << "Nearest place: " << intersection.nearest_place << std::endl;
    return os;
}
