#include "HashTable.h"
#include <iostream>

std::string abbreviations[] = {
    "AK", "AL", "AR", "AS", "AZ", "CA", "CO", "CT", "DC", "DE", "FL", "GA", "GU", "HA", "IA","ID", "IL", "IN", "KS", "KY",
    "LA", "MA", "MD", "ME", "MI", "MN", "MO", "MP", "MS", "MT", "NE", "NC", "ND", "NH", "NJ", "NM", "NV", "NY", "OH", "OK", "OR", "PA",
    "PR", "RI", "SC", "SD", "TN", "TT", "TX", "UT", "VA", "VI", "VT", "WA", "WI", "WV", "WY"
};

std::string statenames[] = {
    "Alaska", "Alabama", "Arkansas", "American Samoa", "Arizona", "California", "Colorado", "Connecticut", "Washington D. C.",
    "Delaware", "Florida", "Georgia", "Guam", "Hawaii", "Iowa", "Idaho", "Illinois", "Indiana", "Kansas", "Kentucky",
    "Louisiana", "Massachusetts", "Maryland", "Maine", "Michigan", "Minnesota", "Missouri", "North Marianas Islands", "Mississippi",
    "Montana", "Nebraska", "North Carolina", "North Dakota", "New Hampshire", "New Jersey", "New Mexico", "Nevada", "New York", "Ohio",
    "Oklahoma", "Oregon", "Pennsylvania", "Puerto Rico", "Rhode Island", "South Carolina", "South Dakota", "Tennessee", "Trust Territories",
    "Texas", "Utah", "Virginia", "U. S. Virgin Islands", "Vermont", "Washington", "Wisconsin", "West Virginia", "Wyoming"
};

HashTable::HashTable() {
    numentries = 0;
    tablesize = 0;
    table = nullptr;
}

HashTable::~HashTable() {
    for (int i = 0; i < tablesize; i++) {
        Pentry* p = table[i];
        while (p != nullptr) {
            Pentry* temp = p;
            p = p->next;
            delete temp->placeptr;
            delete temp;
        }
        table[i] = nullptr;
    }
    delete[] table;
}

unsigned int HashTable::hashval(std::string s) const {
    unsigned int hash = 0;
    for (char c : s) {
        hash = (hash * 31) + c;
    }
    return hash % tablesize;
}

void HashTable::resize() {
    if (tablesize == 0) {
        tablesize++;
        table = new Pentry*[tablesize];
        table[0] = nullptr;
        return;
    }
    tablesize = tablesize * 2;
    Pentry** newtable = new Pentry*[tablesize];
    for (int i = 0; i < tablesize; i++)
        newtable[i] = nullptr;
    for (int i = 0; i < numentries; i++) {
        Pentry* e = table[i];
        while (e != nullptr) {
            Pentry* enext = e->next;
            int newhv = hashval(e->placeptr->name);
            e->next = newtable[newhv];
            newtable[newhv] = e;
            e = enext;
        }
        table[i] = nullptr;
    }
    delete[] table;
    table = newtable;
}

void HashTable::insert(Pentry *e) {
    if (numentries == tablesize)
        resize();
    int hv = hashval(e->placeptr->name); // Ensure hash value is within bounds
    e->next = table[hv];
    table[hv] = e;
    numentries++;
}

bool HashTable::searchNames(std::string s) {
    bool found = false;
    Pentry* p = table[hashval(s)];
    while (p != nullptr) {
        if (p->placeptr->name == s)
            for (int i = 0; i < 57; i++)
                if (p->placeptr->state == abbreviations[i]) {
                    std::cout << p->placeptr->state << " " << statenames[i] << "\n";
                    found = true;
                }
        p = p->next;
    }
    return found;
}

// to return number of matching states for the navigate function
std::vector<NamedPlace*> HashTable::searchPossibilities(std::string s) const {
    std::vector<NamedPlace*> matching_states;
    Pentry* p = table[hashval(s)];
    while (p != nullptr) {
        if (p->placeptr->name == s) {
            matching_states.push_back(p->placeptr);
        }
        p = p->next;
    }

    return matching_states;
}

NamedPlace* HashTable::searchPlace(std::string n, std::string st) const {
    int hashValue = hashval(n);
    Pentry* p = table[hashValue];
    while (p != nullptr) {
        if (p->placeptr->name == n && p->placeptr->state == st) {
            std::cout << "Place found: " << std::endl;
            p->placeptr->printPlace(); // Output place details
            return p->placeptr;
        }
        p = p->next;
    }
    std::cout << "Place not found." << std::endl;
    return nullptr;
}

//to print the number of possibilities
int HashTable::countMatchingStates(std::string s) {
    int count = 0;
    Pentry* p = table[hashval(s)];
    while (p != nullptr) {
        if (p->placeptr->name == s) {
            count++;
        }
        p = p->next;
    }
    return count;
}

