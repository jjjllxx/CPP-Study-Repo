#include <iostream>

class Pt
{
public:
    double x;
    double y;

    Pt(const double x, const double y)
    {
        this->x = x;
        this->y = y;
    }

    Pt(const Pt& other)
    {
        this->x = other.x;
        this->y = other.y;
    }
};

int main()
{
    Pt pt(1, 2);
    Pt pt2 = pt;

    std::cout << &pt.x << ' ' << &pt.y << std::endl;
    std::cout << &pt2.x << ' ' << &pt2.y << std::endl;

    pt2.x += 2;
    pt.y++;
    std::cout << pt.x << ' ' << pt.y << std::endl;
    std::cout << pt2.x << ' ' << pt2.y << std::endl;
}