# Shortest Path Finder Across USA

## Overview
This project implements a comprehensive system for managing geospatial data structures, designed for efficient handling of connections, intersections, and named locations within a mapping or routing application context. Utilizing advanced data structures like hash tables and min-heaps, the system is optimized for rapid data retrieval and manipulation, essential for applications requiring quick access to geospatial information.

## Components

- Connections: Manages the relationships between various entities, facilitating the representation of pathways or links in a network.
- HashTable: Implements a hash table for efficient data storage and retrieval, optimized for operations such as insertion, deletion, and lookup.
- Intersections: Handles geographic intersection points, enabling the processing and manipulation of cross-point data within a spatial context.
- NamedPlace: Manages locations with specific identifiers, supporting operations related to the storage and retrieval of labeled places.
- MinHeap: Utilizes a min-heap structure to efficiently organize data, particularly useful for sorting and priority queue operations.
- Main: The entry point of the application, orchestrating interactions between components and initiating core functionalities.

## Installation

Clone the repository and compile the source files using a C++ compiler supporting C++11 or later. Ensure all dependencies are correctly installed.

## Usage

After compilation, run the executable to start the application. Use the provided interfaces to interact with the system, including adding, removing, or querying spatial data.

To ensure the project operates correctly, it requires the following input files:

- database.txt: Contains a comprehensive set of data entries that the system uses to populate its initial state or to perform bulk operations.
- connections.txt: This file presumably details the connections between different entities or locations, which could be used to establish the relationships within the system's network.
- intersections.txt: Contains information about various intersection points, which are crucial for mapping and routing functionalities.
- named-places.txt: Lists locations with specific identifiers or names, essential for the management of named places within the application.

These files are fundamental for initializing the system with necessary data, these files are specificalle parsed for within the project so if you'd like to use your own files to test you'd have to rewrite the parsing functions. 
