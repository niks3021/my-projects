#include <iostream>

class Entity{
    private:
        int HP;
        int Defense;

};
class Boss : Entity{
    public:
    virtual int makemove();
};
class Dragon :Boss{
    public:
    int makemove() override{}
};