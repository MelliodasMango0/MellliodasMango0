#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

#include "Intersections.h"
#include "Connections.h"
#include "HashTable.h"
#include "Minheap.h"


// File paths for intersection and connections data
const std::string intersection_file = "/home/www/class/een318/intersections.txt";
const std::string connections_file = "/home/www/class/een318/connections.txt";
const std::string named_places_file = "/home/www/class/een318/named-places.txt";

// Constants for mathematical operations
const double pi = acos(-1.0);
const std::string dirs[] = { "N", "NE", "E", "SE", "S", "SW", "W", "NW", "N" };


// Function to calculate the direction between two coordinates
std::string dirfromto(double longitude1, double latitude1,
                      double longitude2, double latitude2) {
    double d = atan2(longitude2 - longitude1, latitude2 - latitude1) * 180.0 / pi + 22.5;
    if (d < 0)
        d += 360.0;
    int n = static_cast<int>(d / 45.0);
    return dirs[n];
}

std::vector<Intersection*> dijkstra(const std::vector<Intersection>& intersections, const std::vector<Connection>& connections, Intersection* startIntersection, Intersection* endIntersection) {

    std::vector<Intersection*> shortestPath;
    std::vector<float> distance(intersections.size(), std::numeric_limits<float>::infinity());
    std::vector<int> previous(intersections.size(), -1);
    std::vector<bool> visited(intersections.size(), false);

    Minheap minHeap;

    // Find the index of the start and end intersections
    int startIntersectionIndex = startIntersection->number;
    int endIntersectionIndex = endIntersection->number;

    // Initialize the distance of the start intersection to 0
    distance[startIntersectionIndex] = 0.0f;
    minHeap.push(0.0f, const_cast<Intersection*>(&intersections[startIntersectionIndex]));
    visited[startIntersectionIndex] = true;

    while (!minHeap.empty()) {
        node current(0.0, nullptr);
        minHeap.pop(current);
        Intersection *currentIntersection = current.data;
        int currentIntersectionIndex = currentIntersection->number;

        float currentDistance = current.prio;

        // Check if the current intersection is the destination
        if (currentIntersectionIndex == endIntersectionIndex) {
            // Reconstruct the shortest path from end to start
            int intersectionIndex = endIntersectionIndex;
            while (intersectionIndex != startIntersectionIndex) {
                shortestPath.push_back(const_cast<Intersection*>(&intersections[intersectionIndex]));
                intersectionIndex = previous[intersectionIndex];
            }
            shortestPath.push_back(const_cast<Intersection*>(&intersections[startIntersectionIndex]));
            std::reverse(shortestPath.begin(), shortestPath.end());
            break;
        }

        // Explore neighbors (connections) of the current intersection
        for (const Connection& connection : connections) {
            int neighborIntersectionIndex = -1;

            // Determine the neighbor intersection
            if (connection.intersectionA == currentIntersection->number) {
                neighborIntersectionIndex = connection.intersectionB;
            } else if (connection.intersectionB == currentIntersection->number) {
                neighborIntersectionIndex = connection.intersectionA;
            }

            // Check if the neighbor intersection was found
            if (neighborIntersectionIndex != -1) {
                float edgeWeight = connection.length;

                // Calculate the new distance from the start to the neighbor through the current intersection
                float newDistance = currentDistance + edgeWeight;

                // If the new distance is shorter than the previously recorded distance, update it
                if (newDistance < distance[neighborIntersectionIndex]) {
                    distance[neighborIntersectionIndex] = newDistance;
                    previous[neighborIntersectionIndex] = currentIntersectionIndex;

                    // If the neighbor is not in the min-heap, add it to the heap, and mark it as visited
                    if (visited[neighborIntersectionIndex] == false) {
                        visited[neighborIntersectionIndex] = true;
                        minHeap.push(newDistance, const_cast<Intersection*>(&intersections[neighborIntersectionIndex]));
                    }
                    // Otherwise, just change the priority
                    else minHeap.decreasePriority(const_cast<Intersection*>(&intersections[neighborIntersectionIndex]), newDistance);
                }
            }
        }
    }

    return shortestPath; //contains sequence of intersection pointers representing the intersections in the shortest path
}


void getUserInput(NamedPlace* &selected_place, const HashTable &places_hash, const std::string &prompt) {
    std::string city, state;
    
    while (true) {
        std::cout << prompt << ": ";
        getline(std::cin, city);

        std::vector<NamedPlace*> possibilities = places_hash.searchPossibilities(city);

        if (possibilities.empty()) {
            std::cout << city << " not found\n";
            continue;
        } else {
            std::cout << possibilities.size() << " possibilities: ";
            for (const NamedPlace* place : possibilities) {
                std::cout << place->state << " ";
            }
            std::cout << "\n";

            std::cout << "Enter the state: ";
            getline(std::cin, state);

            selected_place = places_hash.searchPlace(city, state);

            if (selected_place == nullptr) {
                std::cout << city << " not found in the named places.\n";
                continue;
            } else {
//                state = selected_place->state;
//                std::cout << "Place is " << selected_place->name << ", " << state << ", pop "
//                          << selected_place->population << " (" << selected_place->latitude << ", "
//                          << selected_place->longitude << "), closest intersection "
//                          << selected_place->intersectionCode << "\n";
                break;
            }
        }
    }
}

void navigate(const NamedPlace* startingPlace, const NamedPlace* endingPlace, const std::vector<Intersection*>& route) {
    const Intersection* start = route[0];
    const Intersection* end = route[route.size() - 1];

    // Print info about the starting place
    std::string direction1 = dirfromto(start->longitude, start->latitude, startingPlace->longitude, startingPlace->latitude);
    std::cout << "Starting point is intersection #" << start->number << ", " << start->dist_from_place << " miles " << direction1 << " of " << startingPlace->name << " " << startingPlace->state << ", where ";
    for (int i = 0; i < start->connections.size(); i++) {
        std::cout << start->connections[i].name;
        if (i == start->connections.size() - 1) std::cout << " meet\n";
        else std::cout << " and ";
    }

    float totalDistance = 0;
    const Connection* previousRoad = nullptr;
    bool firstInstruction = true;

    // Print step-by-step directions
    for (int i = 1; i < route.size(); i++) {
        const Intersection* currInt = route[i];
        const Intersection* prevInt = route[i - 1];
        const Connection* roadTaken = nullptr;

        // Find the road taken from current intersection to the next intersection
        for (const Connection& conn : currInt->connections) {
            if ((conn.intersectionA == prevInt->number && conn.intersectionB == currInt->number) ||
                (conn.intersectionB == prevInt->number && conn.intersectionA == currInt->number)) {
                roadTaken = &conn;
                break;
            }
        }

        if (roadTaken != nullptr) {
            if (previousRoad == nullptr || roadTaken->name != previousRoad->name) {
                if (!firstInstruction) {
                    std::cout << "\nthen ";
                } else {
                    firstInstruction = false;
                }

                std::string direction = dirfromto(prevInt->longitude, prevInt->latitude, currInt->longitude, currInt->latitude);
                std::cout << "take " << roadTaken->name << " " << direction << " " << roadTaken->length << " miles to intersection #" << currInt->number << ", " << currInt->dist_from_place << " miles from " << currInt->nearest_place << ", "  << currInt->state;
            }
            totalDistance += roadTaken->length;
            previousRoad = roadTaken;
        }
    }

    // Print info about the destination
//    std::string direction2 = dirfromto(end->longitude, end->latitude, endingPlace->longitude, endingPlace->latitude);
//    std::cout << "\n\nDestination is intersection #" << end->number << ", " << end->dist_from_place << " miles " << direction2 << " of " << endingPlace->name << " " << endingPlace->state << "\n";
//    
//    std::cout << "where " << endingPlace->name << " and " << previousRoad->name << " meet\n";
    
    // Print total miles traveled
    std::cout << "\nTotal " << totalDistance << " miles\n";
}




//function to read the namedplaces file and populate the hash table
void readNamedPlace(const std::string &filename, HashTable& places_hash)
{
    std::ifstream named_place_input(filename);
    if (!named_place_input){
        std::cerr << "Failed to open named places file." << std::endl;
        exit(1);
    }
    
//    HashTable places_hash;

    std::string nline;
    while (getline(named_place_input, nline)) {
//        std::cout << nline <<std::endl;
        NamedPlace *place = NamedPlace::parseLine(nline);
        Pentry *place_entry = new Pentry(place);
        places_hash.insert(place_entry);
    }
    
}

// Function to read intersection data from a file
void readIntersections(const std::string& filename, std::vector<Intersection>& intersections) 
{
    std::ifstream intersection_input(filename);
    if (!intersection_input) {
        std::cerr << "Failed to open intersection file." << std::endl;
        exit(1);
    }

    std::string iline;

    int intersectionNumber = 0;
    while (getline(intersection_input, iline)) {
        Intersection an_intersection = Intersection::parse(iline);
        an_intersection.number = intersectionNumber;
        intersections.push_back(an_intersection);
        intersectionNumber++;
        
        //std::cout << "Parsed Intersection: " << an_intersection << std::endl;
    }

    intersection_input.close();
}

// Function to read connection data from a file
void readConnections(const std::string& filename, std::vector<Connection>& connections) {
    std::ifstream connections_input(filename);
    if (!connections_input) {
        std::cerr << "Failed to open connections file." << std::endl;
        exit(1);
    }

    std::string cline;

    while (getline(connections_input, cline)) {
        connections.push_back(Connection::parse(cline));
    }

    connections_input.close();
}

int main(int argc, const char * argv[]) {
    std::vector<Intersection> intersections;
    std::vector<Connection> connections;

    // File paths for intersection and connections data
    const std::string intersection_file = "/home/www/class/een318/intersections.txt";
    const std::string connections_file = "/home/www/class/een318/connections.txt";
    const std::string named_places_file = "/home/www/class/een318/named-places.txt";

    // Read and populate intersections
    readIntersections(intersection_file, intersections);

    // Read and populate connections
    readConnections(connections_file, connections);

    // Build the graph structure
    for (const Connection &connection : connections) {
        int intersectionA = connection.intersectionA;
        int intersectionB = connection.intersectionB;

        // Find the Intersection objects corresponding to intersectionA and intersectionB
        Intersection &intersectionObjA = intersections[intersectionA];
        Intersection &intersectionObjB = intersections[intersectionB];

        // Add intersectionB to the connected intersections of intersectionA
        intersectionObjA.add_connection(connection);

        // Add intersectionA to the connected intersections of intersectionB
        intersectionObjB.add_connection(connection);
    }

    // Create and populate the HashTable with named places
    HashTable places_hash;
    readNamedPlace(named_places_file, places_hash);

    NamedPlace* startingPlace = nullptr;
    NamedPlace* endingPlace = nullptr;

       getUserInput(startingPlace, places_hash, "Enter the starting city");
       getUserInput(endingPlace, places_hash, "Enter the destination city");

       // Find the corresponding Intersection objects for the selected source and destination places
       Intersection* source_intersection = nullptr;
       Intersection* dest_intersection = nullptr;

       for (int i = 0; i < intersections.size(); i++) {
           if (intersections[i].number == startingPlace->intersectionCode) {
               source_intersection = &intersections[i];
           }
           if (intersections[i].number == endingPlace->intersectionCode) {
               dest_intersection = &intersections[i];
           }
       }

       if (source_intersection && dest_intersection) {
           // Calculate the shortest path from the source to the destination
           std::vector<Intersection*> shortest_path = dijkstra(intersections, connections, source_intersection, dest_intersection);
           
           if (!shortest_path.empty()) {
               // Call the navigate function to provide directions
               navigate(startingPlace, endingPlace, shortest_path);
           } else {
               std::cout << "No path found from the source to the destination." << std::endl;
           }
       } else {
           std::cout << "Source or destination intersection not found." << std::endl;
       }

       return 0;
   }
