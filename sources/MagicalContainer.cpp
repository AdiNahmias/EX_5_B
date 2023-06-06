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
    //check if the element alredy in the elments vector
    for(int run : elements){
        if(run == element){
            return;
        }
    }
    if(isPrime(element)){
        prime_elements.push_back(new int (element));
    }
    elements.push_back(element);
    
    std::sort(elements.begin(), elements.end());
    std::sort(prime_elements.begin(), prime_elements.end(), comparePointers);

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
    for (auto i = elements.begin(); i != elements.end(); ++i) {
        if (element == *i) {
            elements.erase(i);
            break;
        }
    }
    if(isPrime(element)){
        for (auto i = prime_elements.begin(); i != prime_elements.end(); ++i) {
            int *find_element = new int(element);
            if (find_element == *i) {
                prime_elements.erase(i);
                delete find_element;
                break;
            }
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

int MagicalContainer::size() const {
    return elements.size();
}



}

