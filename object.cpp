#include <iostream>
#include <string>

class car{
    public:
        int year;
        std::string Model;
        std::string Colour;
    void Paintcar(){
            std::cout << " What Colour do you want to paint your car:";
            std::string Newcolour = "";
            std::getline(std::cin,Newcolour);
            std::cin.ignore();
            if(Newcolour != "")
            Colour = Newcolour;
        }
        void maintain(){
            maintainance+=15;
            if(maintainance>100)
            maintainance = 100;
                std::cout << "your current maintainance is " << maintainance << "\n";
        }
    private:
        int maintainance = 12;

};

int main()
{
    car car1;
    car1.Model = "Clx-GenIII";
    car1.Colour = "Black";
    car1.year =  2023;

    car1.Paintcar();
    std::cout << car1.Colour << " Is the new colour \n";
    car1.maintain();
}