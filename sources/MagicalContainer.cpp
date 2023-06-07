#include "MagicalContainer.hpp"
#include <algorithm> // for std::sort
#include <vector>

namespace ariel{


bool static isPrime(int number){
        if (number <= 1) {
        return false;
    }
    for (int i = 2; i * i <= number; ++i) {
        if (number % i == 0) {
            return false;  // Number is divisible, hence not prime
            }
        }
        return true;
}

bool comparePointers(const int* a, const int* b) {
    return (*a) < (*b);
}

void MagicalContainer::addElement(int element) {
    //check if the element alredy in the elmemts vector

    for(int run : elements){
        if(run == element){
            return;
        }
    }

    auto iter = std::lower_bound(elements.begin(), elements.end(), element);
    elements.insert(iter, element);

    prime_elements.clear();
    for(size_t i = 0; i < elements.size(); i++){
        if(isPrime(elements[i])){
            prime_elements.push_back(&elements[i]);
        }
    }


}

void MagicalContainer::removeElement(int element) {
    bool in_elemnts = false;
    for(int run : elements){
        if(run == element){
            in_elemnts = true;
        }
    }
    if(!in_elemnts){
        throw std::runtime_error("The Element not in the container!");
    }

    auto iter = std::lower_bound(elements.begin(), elements.end(), element);
    elements.erase(iter);

    prime_elements.clear();
    for(size_t i = 0; i < elements.size(); i++){
        if(isPrime(elements[i])){
            prime_elements.push_back(&elements[i]);
        }
    }

}

std::vector<int>& MagicalContainer::getElements(){
    return this->elements;
}

std::vector<int*>& MagicalContainer::getPrimeContainer(){
                return this->prime_elements;
            }

void MagicalContainer::setElements(std::vector<int>& elements){
    this->elements = elements;
} 

int MagicalContainer::size(){
    return elements.size();
}



}

