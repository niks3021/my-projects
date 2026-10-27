#include <iostream>

class DynamicVector {
private:
    int *data;
    int size;

public:
    DynamicVector() : data(nullptr), size(0) {}

    DynamicVector(int n) {
        if (n <= 0) {
            size = 0;
            data = nullptr;
        } else {
            size = n;
            data = new int[size](); // Initializes elements to 0
        }
    }

    DynamicVector(const DynamicVector &other) {
        size = other.size;
        if (size > 0) {
            data = new int[size];
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        } else {
            data = nullptr;
        }
    }

    ~DynamicVector() {
        std::cout << "[Destructor executed for DynamicVector at address: " << this << "]\n";
        delete[] data;
    }

    void set(int index, int value) {
        if (index >= 0 && index < size) {
            data[index] = value;
        } else {
            std::cout << "Error: Index out of bounds!\n";
        }
    }

    void set(int value) {
        for (int i = 0; i < size; i++) {
            data[i] = value;
        }
    }

    DynamicVector operator+(const DynamicVector &rhs) const {
        if (size != rhs.size) {
            std::cout << "Error: Cannot add vectors of incompatible sizes (" 
                      << size << " != " << rhs.size << ")!\n";
            return DynamicVector();
        }
        DynamicVector result(size);
        for (int i = 0; i < size; i++) {
            result.data[i] = data[i] + rhs.data[i];
        }
        return result;
    }

    bool operator==(const DynamicVector &rhs) const {
        if (size != rhs.size) return false;
        for (int i = 0; i < size; i++) {
            if (data[i] != rhs.data[i]) return false;
        }
        return true;
    }

    int& operator[](int index) {
        static int dummy = 0;
        if (index >= 0 && index < size) {
            return data[index];
        }
        std::cout << "Error: Index out of bounds! Returning reference to dummy.\n";
        return dummy;
    }

    void display() const {
        std::cout << "[ ";
        for (int i = 0; i < size; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << "]\n";
    }
};

int main() {
    std::cout << "1. Creating vector v1 (size 3) and initializing to 10:\n";
    DynamicVector v1(3);
    v1.set(10);
    std::cout << "v1: "; v1.display();

    std::cout << "\n2. Copying v1 to v2 and modifying v2 using operator[]:\n";
    DynamicVector v2 = v1; // Copy Constructor invoked
    v2[1] = 99;            // Subscript operator used
    std::cout << "v1 (Original): "; v1.display();
    std::cout << "v2 (Modified): "; v2.display();

    std::cout << "\n3. Equality check before and after modification:\n";
    DynamicVector v3(3);
    v3.set(10);
    std::cout << "v1 == v3 (Same elements): " << (v1 == v3 ? "True" : "False") << "\n";
    std::cout << "v1 == v2 (Modified copy): " << (v1 == v2 ? "True" : "False") << "\n";

    std::cout << "\n4. Valid Vector Addition (v1 + v3):\n";
    DynamicVector vAdd = v1 + v3;
    std::cout << "v1 + v3 = "; vAdd.display();

    std::cout << "\n5. Incompatible Size Addition Case:\n";
    DynamicVector vIncompatible(5);
    DynamicVector vFail = v1 + vIncompatible;

    std::cout << "\n6. Program termination (Destructors execute next):\n";
    return 0;
}