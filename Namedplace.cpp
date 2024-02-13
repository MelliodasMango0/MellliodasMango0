#include "NamedPlace.h"

NamedPlace::NamedPlace(int code, const std::string& state, const std::string& name, int population, double area,
      double latitude, double longitude, int intersectionCode, float distance)
    : code(code), state(state), name(name), population(population), area(area),
      latitude(latitude), longitude(longitude), intersectionCode(intersectionCode), distance(distance) {}

NamedPlace* NamedPlace::parseLine(const std::string &line) {
    int code = std::stoi(line.substr(0, 8));
    std::string state = line.substr(8, 2);

    // Trim leading spaces from the name field because the names have leading spaces
    std::string name = line.substr(10, 48);
    name = name.substr(name.find_first_not_of(' '), name.find_last_not_of(' ') + 1);
    int population = std::stoi(line.substr(58, 8));
    double area = std::stod(line.substr(66, 15));
    double latitude = std::stod(line.substr(81, 9));
    double longitude = std::stod(line.substr(90, 11));
    int intersectionCode = std::stoi(line.substr(101, 5));
    float distance = std::stof(line.substr(106, 8));

    return new NamedPlace(code, state, name, population, area, latitude, longitude, intersectionCode, distance);
}

void NamedPlace::printPlace() const {
    std::cout << "Code: " << code << std::endl;
    std::cout << "State: " << state << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Population: " << population << std::endl;
    std::cout << "Area: " << area << " square miles" << std::endl;
    std::cout << "Latitude: " << latitude << " degrees North" << std::endl;
    std::cout << "Longitude: " << longitude << " degrees East" << std::endl;
    std::cout << "Intersection Code: " << intersectionCode << std::endl;
    std::cout << "Distance to Intersection: " << distance << " miles" << std::endl;
}
