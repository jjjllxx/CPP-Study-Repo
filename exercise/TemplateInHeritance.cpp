#include <iostream>
#include <vector>

template<typename T>
struct ManyValues : std::vector<T>
{
    int  val;
    void add(const T& value)
    {
        ManyValues::push_back(value);
    }
};

int main()
{
    std::cout << "Hello World!" << std::endl;

    ManyValues<int> mv;
    mv.val = 5;
    mv.push_back(1);
    mv.push_back(2);
    mv.add(3);
    std::cout << mv[0] << mv[1] << mv[2] << mv.val << std::endl;

    return 0;
}