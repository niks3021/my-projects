#include <iostream>
#include <string>

class Items
{
public:
    Items() : ItemName(""), Price(0.0), Quantity(0) {}
    Items(std::string ItemName, double Price, int Quantity)
        : ItemName(ItemName), Price(Price), Quantity(Quantity)
    {
    }
    //getters
    std::string GetName() const { return ItemName; }
    double GetPrice() const { return Price; }
    int GetQuantity() const { return Quantity; }
    //setters
    void SetName(const std::string& name) { ItemName = name; }
    void SetPrice(double price)           { if (price >= 0.0) Price = price; }
    void SetQuantity(int qty)             { if (qty >= 0) Quantity = qty; }


private:
    std::string ItemName;
    double Price = 0.00;
    int Quantity = 0;
};
void PrintReceipt(const Items* cart, int count) {
    double grandTotal = 0.0;
    std::cout << "\n===============================\n";
    std::cout << "        STORE RECEIPT          \n";
    std::cout << "===============================\n";

    for (int i = 0; i < count; i++) {
        double itemTotal = cart[i].GetPrice() * cart[i].GetQuantity();
        grandTotal += itemTotal;
        std::cout << cart[i].GetName() << " x" << cart[i].GetQuantity() 
                  << " @ $" << cart[i].GetPrice() << " = $" << itemTotal << "\n";
    }

    std::cout << "-------------------------------\n";
    std::cout << "GRAND TOTAL: $" << grandTotal << "\n";
    std::cout << "===============================\n";
}
int main()
{
    int NumberOfItems = 0;
    do
    {
        std::cout << " Enter the number of items ";

        std::cin >> NumberOfItems;
    } while (NumberOfItems <= 0);
    Items *cart = new Items[NumberOfItems];
    for (int i = 0; i < NumberOfItems; i++)
    {
        std::cin.ignore(1000,'\n');
        std::string name;
        int qty,price;
        std::cout << " Enter Item Name: ";
        std::getline(std::cin,name);
        std::cout << " Enter Price: ";
        std::cin>> price;
        std::cout << " Enter Quantity: ";
        std::cin >> qty;
        cart[i].SetName(name);
        cart[i].SetPrice(price);
        cart[i].SetQuantity(qty);
        std::cout << "_____________________________\n";
    }
    PrintReceipt(cart,NumberOfItems);
    delete[] cart;
    
}
