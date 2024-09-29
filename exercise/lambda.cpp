#include <iostream>
using namespace std;

int main()
{
    int   year  = 19900212;
    int   shoes = 42;
    std::string name  = "zhangxiang";
    auto  show  = [&, shoes]() mutable
    {
        shoes++;
        year++;
        cout << year << ' ' << shoes << ' ' << name << endl;
    };
    show();
    show();
    show();

    cout << year << ' ' << shoes << ' ' << name << endl;
}

