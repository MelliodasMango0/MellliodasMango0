#include "Minheap.h"

Minheap::Minheap(){}

bool Minheap::empty() const{
    return heap.empty();
}

void Minheap::push(float prio, Intersection* data){
    heap.push_back(node(prio,data));       //add the new value to the end of the vector
    heapifyUp(heap.size() - 1); //cal heapify up to maintain min heap
}


int Minheap::pop(node &result){
    if (heap.empty()){
        return -1;
    }
        result = heap[0]; // Store the top element in 'result'
       heap[0] = heap.back(); // Move the last element to the top
       heap.pop_back(); // Remove the last element
       heapifyDown(0); // Maintain the min-heap property

       return 0; // Return success
    }


bool Minheap::top(node& result) const {
    if (!empty()) {
        result = heap[0]; // Get the top element without removing it
        return true;
    }
    return false;   // If the heap is empty, return false
}

void Minheap::heapifyUp(int index) {
    while (index > 0) { // If index is 0, then we wouldn't need to move the element up because it's already the smallest
        int parent_index = (index - 1) / 2; // Calculate the parent index
        if (heap[index].prio < heap[parent_index].prio) { // If the current element has a smaller priority than its parent
            std::swap(heap[index], heap[parent_index]); // Swap them
            index = parent_index;   // Move up the tree
        } else {
            break;  // If the current element is in the correct position, then break
        }
    }
}

void Minheap::heapifyDown(int index) {

    int left_child = 2 * index + 1; // Get left child index
    int right_child = 2 * index + 2; // Get right child index
    int smallest = index;           // Assume current element is the smallest

    if (left_child < heap.size() && heap[left_child].prio < heap[smallest].prio) { // If left child exists and has a smaller priority
        smallest = left_child; // Update the smallest index
    }

    if (right_child < heap.size() && heap[right_child].prio < heap[smallest].prio) { // If right child exists and has a smaller priority
        smallest = right_child; // Update the smallest index
    }

    if (smallest != index) { // Check to see if the smallest is still equal to the index; if not, then
        std::swap(heap[index], heap[smallest]); // Swap them
        heapifyDown(smallest); // Move down the tree
    }
}

void Minheap::decreasePriority(Intersection* data, float new_prio) {
    // Find the node containing the specific Intersection
    for (size_t i = 0; i < heap.size(); i++) {
        if (heap[i].data == data) {
            // Update the priority of the node
            heap[i].prio = new_prio;
            // Maintain the min-heap property by performing heapifyUp
            heapifyUp(i);
            break; // Once updated, break out of the loop
        }
    }
}
