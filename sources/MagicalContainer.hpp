#ifndef MAGICALCONTAINER_HPP
#define MAGICALCONTAINER_HPP

#include <vector>
#include <algorithm> // for std::sort
#include <cstddef>

namespace ariel{

class MagicalContainer {

    private:
    std::vector<int> elements;

    public:
    MagicalContainer() = default; // Default constructor
    MagicalContainer(const MagicalContainer& other) = default; // Copy constructor
    ~MagicalContainer() = default; // Destructor

    std::vector<int>& getElements();
    void setElements(std::vector<int>& elements);
    void addElement(int element);
    void removeElement(int element);
    int size() const;

    //for tidy
    
    // Copy assignment operator
    MagicalContainer& operator=(const MagicalContainer& other) {
        if (this != &other) {
            // Perform deep copy of the container
            elements = other.elements;
        }
        return *this;
    }

    // Move constructor
    MagicalContainer(MagicalContainer&& other) noexcept = default;

    // Move assignment operator
    MagicalContainer& operator=(MagicalContainer&& other) noexcept {
        if (this != &other) {
            // Move the container from the other object
            elements = std::move(other.elements);
        }
        return *this;
    }


    class AscendingIterator {
        
        private:

            MagicalContainer& container;
            int index = 0;

        public:

            AscendingIterator(const AscendingIterator& copy_container):container(copy_container.container){}//Copy constructor
            ~AscendingIterator() = default; // Destructor

            AscendingIterator(MagicalContainer& container): container(container){
            std::vector<int> sortedElements = container.getElements();
            std::sort(sortedElements.begin(), sortedElements.end());
            this->container.setElements(sortedElements);
            }

            
            int& operator*() const {
                return container.getElements()[static_cast<std::vector<int>::size_type>(index)];
            }

            AscendingIterator& operator++(){
                this->index = this->index + 1;
                return *this;
            }

            bool operator==(const AscendingIterator& other_iterator) const {
                        return index == other_iterator.index;
            }
            bool operator!=(const AscendingIterator& other_iterator) const {
                        return index != other_iterator.index;
            }
            
            AscendingIterator begin() const{
                    AscendingIterator begin_iterator(container);
                    return begin_iterator;
            }

            
            AscendingIterator end() const{
                AscendingIterator iterator_end(container);
                iterator_end.index = container.size();
                return iterator_end;
            }

            // Copy assignment operator
            AscendingIterator& operator=(const AscendingIterator& other) {
                if (this != &other) {
                    container = other.container;
                    index = other.index;
                }
                return *this;
            }
           

            // Move constructor
            AscendingIterator(AscendingIterator&& other) noexcept : container(other.container), index(other.index) {}

            // Move assignment operator
            AscendingIterator& operator=(AscendingIterator&& other) noexcept {
                if (this != &other) {
                    container = std::move(other.container);
                    index = other.index;
                }
                return *this;
            }

            

            


        };



    class SideCrossIterator {

    private:
        MagicalContainer& container;
        int index = 0;

    public:

        SideCrossIterator(MagicalContainer& container):container(container){
            std::vector<int>& sortedElements = container.getElements();
            std::sort(sortedElements.begin(), sortedElements.end());
            size_t start = 0;
            size_t end = sortedElements.size() -1;
            std::vector<int> crossElements(static_cast<size_t>(sortedElements.size()), 0);
            //size_t ind = 0;
            for (size_t i = 0; i < container.size() ; i+=2){
                if(start == end){
                    crossElements[i] = sortedElements[start]; 
                    break;  
                }
                crossElements[i] = sortedElements[start];
                crossElements[i+1] = sortedElements[end];
                start++;
                end--; 
            }

            this->container.setElements(crossElements);

        }

        //copy constructor
        SideCrossIterator(const SideCrossIterator& other_container) : container(other_container.container){} //Copy constructor
        ~SideCrossIterator() = default; //Destructor

        int& operator*() const {
            return container.getElements()[static_cast<std::vector<int>::size_type>(index)];
        }
        SideCrossIterator& operator++(){
            // Increment the index
            index++;
            return *this;
        }
       
        bool operator==(const SideCrossIterator& other) const{
            return index == other.index;
        }

        bool operator!=(const SideCrossIterator& other) const{
            return index != other.index;
        }

        bool operator>(const SideCrossIterator& other) const{
            return index > other.index;
        }

        bool operator<(const SideCrossIterator& other) const{
            return index < other.index;
        }

        SideCrossIterator begin() const{
            return SideCrossIterator(container);
        }

        // Return an iterator that point to the end of the container (one past the last element)
        SideCrossIterator end() const{
            SideCrossIterator iterator_end(container);
            iterator_end.index = container.size();
            return iterator_end;
        }

        // Copy assignment operator
        SideCrossIterator& operator=(const SideCrossIterator& other) {
            if (this != &other) {
                container = other.container;
                index = other.index;
            }
            return *this;
        }

        SideCrossIterator(SideCrossIterator&& other) noexcept
            : container(other.container), index(other.index) {
            // Move constructor implementation
        }

        SideCrossIterator& operator=(SideCrossIterator&& other) noexcept {
            if (this != &other) {
                container = std::move(other.container);
                index = other.index;
            }
            return *this;
        }


    };

    class PrimeIterator  {

        private:
        
            MagicalContainer& container;
            int index = 0;

            //help function
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

        public:
            
            PrimeIterator(const PrimeIterator& other_container) : container(other_container.container){} //Copy constructor
            ~PrimeIterator() = default; //Destructor

            PrimeIterator(MagicalContainer& container):container(container){
                std::vector<int> primeElements;
                for (size_t i = 0; i < container.getElements().size(); i++)
                {
                    if (isPrime(container.getElements()[i])) {
                        primeElements.push_back(container.getElements()[i]);
                    }
                }
                container.setElements(primeElements);
            }

            int& operator*() const {
                return container.getElements()[static_cast<std::vector<int>::size_type>(index)];
            }
             PrimeIterator& operator++(){
                // Increment the index
                index++;
                return *this;
            }
            
            bool operator==(const PrimeIterator& other) const{
                return index == other.index;
            }

            bool operator!=(const PrimeIterator& other) const{
                return index != other.index;
            }

            bool operator>(const PrimeIterator& other) const{
                return index > other.index;
            }

            bool operator<(const PrimeIterator& other) const{
                return index < other.index;
            }

            PrimeIterator begin() const{
                return PrimeIterator(container);
            }

            // Return an iterator that point to the end of the container (one past the last element)
            PrimeIterator end() const{
                PrimeIterator iterator_end(container);
                iterator_end.index = container.size();
                return iterator_end;
            }


            PrimeIterator& operator=(const PrimeIterator& other) {
                if (this != &other) {
                    container = other.container;
                    index = other.index;
                }
                return *this;
            }

            PrimeIterator(PrimeIterator&& other) noexcept
                : container(other.container), index(other.index) {
                // Move constructor implementation
            }

            PrimeIterator& operator=(PrimeIterator&& other) noexcept {
                if (this != &other) {
                    container = std::move(other.container);
                    index = other.index;
                }
                return *this;
            }
            



        };
    };

}



#endif
