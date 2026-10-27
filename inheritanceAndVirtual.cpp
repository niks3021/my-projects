#include <iostream>
#include <vector>

class Base{
    public:
        virtual void show() {std::cout << "Base\n";} // testing with and without virtual
};

class derived : public Base{
     public:
        void show() {std::cout << "Derived\n";}
};

int main() {
    derived d1;
    Base *ptr = &d1;
    ptr->show();
    return 0;
}