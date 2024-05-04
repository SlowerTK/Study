//вариант 2
#include <iostream>
#include <math.h>

class Formula
{
public:
    Formula() {
        N = 0;
        D = 0;
        PI = acos(-1);
        if (N || D)
            throw "Ошибка конструктора";
    };
    void Print(double x) {
        NumeratorWithoutTan(x);
        Numerator();
        Denominator(x);
        std::cout << N / D << std::endl;
    }
private:
    void NumeratorWithoutTan(double x) {
        N = PI / 180 * x;

    }
    void Numerator() {
        double y = cos(N), eps = 1e-10;
        if (abs(y-0)<eps) throw "Тангенс не существует";
        N = sin(N) / y;
    }
    void Denominator(double x) {
        D = 4 - (x * x);
        if (!D)
            throw "При х -> +/-2, Y = +INF";
    }
    double N;
    double D;
    double PI;
};

int main()
{
    setlocale(LC_ALL, "");
    double x = 0;
    std::cout << "Введите x: ";
    std::cin >> x;
    try {
        Formula t {};
        t.Print(x);
    }
    catch (const char* error) {
        std::cout << error << std::endl;
    }
}