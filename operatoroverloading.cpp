#include <iostream>

class Complex
{
private:
    double Real;
    double Imaginary;

public:
    Complex(double R = 0, double I = 0) : Real(R), Imaginary(I) {}

    friend Complex operator+(const Complex &Z1, const Complex &Z2);
    friend Complex operator-(const Complex &Z1, const Complex &Z2);
    friend Complex operator*(const Complex &Z1, const Complex &Z2);
    friend Complex operator/(const Complex &Z1, const Complex &Z2);

    Complex Conjugate() const { return Complex(Real, -Imaginary); }
    double NormSquared() const { return (Real * Real) + (Imaginary * Imaginary); } 
    Complex Inverse() const
    {
        double den = NormSquared();
        return Complex(Real / den, -Imaginary / den);
    }
    void Display() const { std::cout << Real << " + " << Imaginary << "i\n"; }
};

Complex operator*(const Complex &Z1, const Complex &Z2)
{
    return Complex((Z1.Real * Z2.Real) - (Z1.Imaginary * Z2.Imaginary),
                   (Z1.Imaginary * Z2.Real) + (Z2.Imaginary * Z1.Real));
}

Complex operator+(const Complex &Z1, const Complex &Z2)
{
    return Complex(Z1.Real + Z2.Real, Z1.Imaginary + Z2.Imaginary);
}

Complex operator-(const Complex &Z1, const Complex &Z2)
{
    return Complex(Z1.Real - Z2.Real, Z1.Imaginary - Z2.Imaginary);
}

Complex operator/(const Complex &Z1, const Complex &Z2)
{
    return Z1*Z2.Inverse();
}

int main()
{

    return 0;
}