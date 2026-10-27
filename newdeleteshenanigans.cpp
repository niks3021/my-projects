#include <iostream>
#include <cstdlib>

class Table {
public:
    int* box;
    int size;

    Table(int s) : size(s) {
        std::cout << "Constructor called: Allocating box array of size " << size << "\n";
        box = new int[size]; 
    }

    void* operator new(size_t bytes) {
        std::cout << "Custom operator new: Allocating " << bytes << " bytes for Table object\n";
        void* p = std::malloc(bytes);
        if (!p) throw std::bad_alloc();
        return p;
    }

    void operator delete(void* p) noexcept {
        std::cout << "Custom operator delete: Freeing Table object memory\n";
        std::free(p);
    }

    ~Table() {
        std::cout << "Destructor called: Cleaning up box array\n";
        delete[] box;
    }
};

int main() {

    Table* t = new Table(5);

    delete t;

    return 0;
}