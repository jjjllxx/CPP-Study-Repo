#include <iostream>

int main()
{
    int x = 6;
    const int &y = x;
    std::cout << x << " " << y << std::endl;
    std::cout << &x << " " << &y << std::endl;
    x++;
    std::cout << x << " " << y << std::endl;

    const int& z = x * 6;
    std::cout << x << " " << z << std::endl;
    std::cout << &x << " " << &z << std::endl;
    x++;
    std::cout << x << " " << z << std::endl;

    int&& z2 = 6;
    std::cout << z2 << std::endl;

    const int & z3 = x;
    std::cout << z3 << std::endl;
}