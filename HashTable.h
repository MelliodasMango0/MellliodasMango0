#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "namedplace.h"
#include <vector>

struct Pentry {
    NamedPlace* placeptr;
    Pentry* next;

    Pentry(NamedPlace* p) : placeptr(p), next(nullptr) {}
};

class HashTable {
private:
    int tablesize;
    int numentries;
    Pentry **table;

    void resize();

public:
    HashTable();
    ~HashTable();

    unsigned int hashval(std::string s) const;

    void insert(Pentry *e);
    bool searchNames(std::string s);
    std::vector<NamedPlace*> searchPossibilities(std::string s) const;
    NamedPlace* searchPlace(std::string n, std::string st) const;
    int countMatchingStates(std::string s);
    
//    std::vector<Intersection*> dijkstra(const std::vector<Intersection>& intersect_vec,
//                                           const std::vector<Connection>& connection_vec,
//                                           int start, int end) const;
    };
    
    

#endif // HASHTABLE_H
