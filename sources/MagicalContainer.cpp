#include "MagicalContainer.hpp"
#include <algorithm> // for std::sort
#include <vector>

namespace ariel{

void MagicalContainer::addElement(int element) {
    elements.push_back(element);
}

void MagicalContainer::removeElement(int element) {
    for (auto i = elements.begin(); i != elements.end(); ++i) {
        if (element == *i) {
            elements.erase(i);
            break;
        }
    }
}

std::vector<int>& MagicalContainer::getElements(){
    return this->elements;
}

void MagicalContainer::setElements(std::vector<int>& elements){
    this->elements = elements;
} 

int MagicalContainer::size() const {
    return elements.size();
}



}

