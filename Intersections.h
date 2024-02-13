// Intersections.hpp

#ifndef Intersections_h
#define Intersections_h

#include <iostream>
#include <string>
#include <vector>
#include "Connections.h"

class Intersection {
public:
    
    float longitude;
    float latitude;
    float dist_from_place; // in miles
    std::string nearest_place;
    std::string state;
    int number;

    std::vector<Connection> connections;

    Intersection(float longi, float lat, float dist, const std::string np, const std::string st) {
        longitude = longi;
        latitude = lat;
        dist_from_place = dist;
        nearest_place = np;
        state = st;
    }

    // Parse a line to create an Intersection object
    static Intersection parse(const std::string &line);

    // Add a connection to the Intersection
    void add_connection(const Connection &connection);

    // Overload the << operator to print an Intersection object
    friend std::ostream& operator<<(std::ostream& os, const Intersection& intersection);
};

#endif /* Intersections_hpp */
