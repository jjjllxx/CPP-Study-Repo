#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>
using namespace std;
int add(int x, int y)
{
    cout << "int add(int, int) = " << "(" << x << ", " << y << ")" << endl;
    return x + y;
}

int main()
{
    auto f = bind(add, 1, 2);
    cout << f() << endl;

    auto f1 = bind(add, 1, std::placeholders::_3);
    cout << f1(1 ,2, 3) << endl;
}