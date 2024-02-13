#ifndef Minheap_h
#define Minheap_h

#include <vector>
#include <iostream>

#include "Intersections.h"

struct node{
    Intersection *data;
    float prio;
    
    node(float p, Intersection* d) : prio(p), data(d) {}
};

class Minheap {
public:
    

    Minheap();
    
    bool empty() const; //checks if heap is empty
    void push(int value, float prio); //insert
    void push(float prio, Intersection *data); //  push function to be able to add tentative distance
    int pop(node &result); // attempts to remove element from the heap and store it in value
    bool top(node& result) const; //attempts to get the top element of the heap without removing it and store it in value
    void decreasePriority(Intersection* data, float new_prio); //node containing the specified Intersection* in the heap and updates its priority with the new priority value
    
private:
    
    std::vector<node> heap; //the vector fr the heap
    
    void heapifyUp(int index); //maintains min-heap when pushing
    void heapifyDown(int index); //maintains min-heap when popping
};

#endif /* Minheap_hpp */
