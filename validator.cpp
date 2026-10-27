#include <iostream>

int GetDigits(const int Number);
int OddDigits(const std::string &CardNumber);
int EvenDigits(const std::string &CardNumber);

int main()
{
    int result = 0;
    std::string CardNumber;
    std::cout << "enter your card number # ";
    std::cin >> CardNumber;
    result = EvenDigits(CardNumber) + OddDigits(CardNumber);

    if(result%10 == 0)
    {
        std::cout << " Card Number is Valid";
    }
    else{
        std::cout << " Card Number is invalid";
    }

}
int GetDigits(const int Number)
{
    return Number % 10 + Number/10 %10;
}
int OddDigits(const std::string &CardNumber)
{
    int sum = 0;
    for (int i = CardNumber.size() - 1; i >=0; i-=2)
    {
        sum += (CardNumber[i]-'0');
    }
    return sum;
    
}
int EvenDigits(const std::string &CardNumber)
{
    int sum = 0;
    for (int i = CardNumber.size() - 2; i >=0; i-=2)
    {
        sum += GetDigits((CardNumber[i]-'0')*2);
    }
    return sum;
}