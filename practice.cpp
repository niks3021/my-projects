#include <iostream>

class Technician;

class Consutant{
    private:
        int empID;
        std::string name;
        int projects; 
        double PayPerProject;
        double income()
        {
            return projects * PayPerProject;
        }
    public:
        Consutant(int EID, std::string N, int P, double PPP)
            : empID(EID), name(N), projects(P), PayPerProject(PPP) {}
        friend void compareIncome(Consutant &C, Technician &T);
};

class Technician{
    private:
        int empID;
        std::string name;
        int hours;
        double PayPerHour;
        double income()
        {
            return hours * PayPerHour;
        }
    public:
        Technician(int EID, std::string N, int H, double PPH)
            : empID(EID), name(N), hours(H), PayPerHour(PPH) {}
        friend void compareIncome(Consutant &C, Technician &T);
};

void compareIncome(Consutant &C, Technician &T)
{
    double consultantIncome = C.income();
    double technicianIncome = T.income();
    std::cout << "Consultant income: " << consultantIncome << '\n';
    std::cout << "Technician income: " << technicianIncome << '\n';
    if(consultantIncome == technicianIncome) 
    {
        std::cout << "Both earn same\n";
    }
    else if (consultantIncome >technicianIncome)
    {
        std::cout << C.name << " earns more\n";
    }
    else
    {
        std::cout << T.name << " earns more\n";
    }
}

int main()
{
    Consutant C(301,"Neha",12,2500);
    Technician T(401,"Rohit",180,150);
    compareIncome(C,T);
    return 0;
}