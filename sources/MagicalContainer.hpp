#ifndef MAGICALCONTAINER_HPP
#define MAGICALCONTAINER_HPP

#include <vector>
#include <algorithm> // for std::sort
#include <cstddef>
#include <stdexcept>


namespace ariel{

class MagicalContainer {

    private:
        std::vector<int> elements;
        std::vector<int*> prime_elements;

    public:
        MagicalContainer() = default; // Default constructor
        MagicalContainer(const MagicalContainer& other) = default; // Copy constructor
        std::vector<int*>& getPrimeContainer();
        std::vector<int>& getElements();
        void setElements(std::vector<int>& elements);
        void addElement(int element);
        void removeElement(int element);
        int size();

        bool operator==(const MagicalContainer& other) const {
            return elements == other.elements && prime_elements == other.prime_elements;
        }
        ~MagicalContainer() {}

        //----------------------------------------------------
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

    class Iterator {
        private:
            MagicalContainer& container;
            int index;
            bool start_index;
            
        public:
            Iterator(MagicalContainer& container) : container(container), index(0), start_index(true){}
            Iterator(const Iterator& other) : container(other.container), index(other.index) , start_index(other.start_index) {}
            virtual ~Iterator() = default;
            virtual Iterator& begin() = 0;
            virtual Iterator& end() = 0;
            virtual int& operator*() = 0;
            virtual Iterator& operator++() = 0;

            int getIndex() const{
                return index;
            }

            void setIndex(int other){
                index = other;
            }

            MagicalContainer& getContainerIterator() const{
                return container;
            }

            bool get_move_start() const{
                return start_index;
            }

            void set_move_start(bool other){
                start_index = other;
            }

            bool operator==(const Iterator& other) const{
                if(typeid(*this) != typeid(other)){
                    throw std::runtime_error("there is diffrent iterators");
                }
                return (this->container == other.container) && (this->index == other.index) && (this->start_index == other.start_index);
            }

            bool operator!=(const Iterator& other) const {
                return !(*this == other);
            }

            bool operator>(const Iterator& other) const{
                return index > other.index;
            }

            bool operator<(const Iterator& other) const{
                return !(*this == other) && !(*this > other);
            }

            //----------------------------------------------------
            // Copy assignment operator
            Iterator& operator=(const Iterator& other) {
                if(container.getElements() != other.container.getElements()){
                    throw std::runtime_error("not the same containar");
                }

                if (this != &other) {
                    container = other.container;
                    index = other.index;
                    start_index = other.start_index;
                }
                return *this;
            }
            // Move constructor
            Iterator(Iterator&& other) noexcept : container(other.container), index(other.index) , start_index(other.start_index) {}

            // Move assignment operator
            Iterator& operator=(Iterator&& other) noexcept {
                if (this != &other) {
                container = std::move(other.container);
                index = other.index;
                start_index = other.start_index;
                }
                return *this;
            }
    };



    class AscendingIterator : public Iterator {
 
        public:

            AscendingIterator(MagicalContainer& container): Iterator(container){}

            int& operator*() override {
                return this->getContainerIterator().getElements()[static_cast<std::vector<int>::size_type>(this->getIndex())];
            }

            AscendingIterator& operator++() override{
                if(this->getIndex() == this->getContainerIterator().getElements().size()){
                    throw std::runtime_error("Iterator at the end index");
                }
                this->setIndex(this->getIndex() + 1);
                return *this;
            }
            
            AscendingIterator& begin() override{
                    this->setIndex(0);
                    return *this;
            }
            AscendingIterator& end() override {
                this->setIndex(static_cast<int>(this->getContainerIterator().getElements().size()));
                return *this;
            }


       
    };

    class SideCrossIterator: public Iterator {
        
    public:

        SideCrossIterator(MagicalContainer& container):Iterator(container){}
        
        int& operator*() override {
            if (this->get_move_start()) {
                return this->getContainerIterator().getElements()[static_cast<std::vector<int>::size_type>(this->getIndex())];
            }
            return this->getContainerIterator().getElements()[this->getContainerIterator().getElements().size() - static_cast<std::vector<int>::size_type>(this->getIndex())];
        }

        SideCrossIterator& operator++() override {
        auto containerSize = static_cast<int>(this->getContainerIterator().getElements().size());
        if (this->getIndex() == containerSize) {
            throw std::runtime_error("Iterator at the end index");
        }

        if (this->get_move_start()) { // Iterator on the left side
            set_move_start(false); // Iterator goes to the right side
            if (this->getIndex() == containerSize / 2) { // If the index is at the end
                this->setIndex(containerSize);
            } else {
                this->setIndex(this->getIndex() + 1);
            }
        } else {
            this->set_move_start(true); // Iterator goes to the left side
        }

        return *this;
    }


         SideCrossIterator& begin() override{
            this->setIndex(0);
            this->set_move_start(true);
            return *this;

        }

        SideCrossIterator& end() override{
            this->setIndex(static_cast<int>(this->getContainerIterator().getElements().size()));
            this->set_move_start(false);
            return *this;
        }

    };

    class PrimeIterator: public Iterator{

        public:

            PrimeIterator(MagicalContainer& container):Iterator(container){}

            int& operator*() override {
            return *(this->getContainerIterator().getPrimeContainer()[static_cast<std::vector<int>::size_type>(this->getIndex())]);
            }

            PrimeIterator& operator++() override{
                if (this->getIndex() == this->getContainerIterator().getPrimeContainer().size()) {
                throw std::runtime_error("Iterator at the end index");
            }
                this->setIndex(this->getIndex() + 1);
                return *this;
            }

            PrimeIterator& begin() override{
                        this->setIndex(0);
                        return *this;
                    }

            // Return an iterator that point to the end of the container (one past the last element)
            PrimeIterator& end() override{
                this->setIndex(static_cast<int>(this->getContainerIterator().getPrimeContainer().size()));
                return *this;
            }

        };
    };

}



#endif
