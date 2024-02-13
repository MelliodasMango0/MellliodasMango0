#ifndef NAMEDPLACE_H
#define NAMEDPLACE_H

#include <iostream>
#include <string>


class NamedPlace {
public:
    int code;
    std::string state;
    std::string name;
    int population;
    double area;
    double latitude;
    double longitude;
    int intersectionCode;
    float distance;

    NamedPlace(int code, const std::string& state, const std::string& name, int population, double area,
          double latitude, double longitude, int intersectionCode, float distance);

    static NamedPlace* parseLine(const std::string& line);

    void printPlace() const;
};

#endif // NAMEDPLACE_H
