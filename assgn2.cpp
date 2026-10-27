#include <iostream>

class rectangle {
public:
    // constructor
    rectangle(double l, double w) : length(l), width(w)
    {}

    // methods
    double area() const { return length * width;}

    double perimeter() const { return 2 * (length + width);}

    // getters
    double GetLength() const{ return length; }

    double GetWidth() const{ return width; }

    // setters
    void SetLength(double newlength) {   length = newlength; }

    void SetWidth(double newwidth){   width = newwidth;   }

private:
    double length;
    double width;
};

int main()
{
    double L = 0, W = 0;
    do {
        std::cout << "Enter length: ";
        std::cin >> L;
        std::cout << "Enter Width: ";
        std::cin >> W;
        if (L <= 0 || W <= 0)
        {   std::cout << "invalid length or width\n";   }
    } while (L <= 0 || W <= 0);

    rectangle rect1(L, W);
    std::cout << "Area Is : " << rect1.area() << " Perimeter is: " << rect1.perimeter();
    return 0;
}