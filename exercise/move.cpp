#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

class A
{
public:
    A()
    {
        std::cout << "A construct..." << std::endl;
        ptr_ = new int(100);
    }

    A(const A& a)
    {
        std::cout << "A copy construct ..." << std::endl;
        ptr_ = new int();
        memcpy(ptr_, a.ptr_, sizeof(int));
    }

    A(A&& a)
    {
        std::cout << "A move construct ..." << std::endl;
        ptr_   = a.ptr_;
        a.ptr_ = nullptr;
    }

    ~A()
    {
        std::cout << "A deconstruct ..." << std::endl;
        if (ptr_)
        {
            delete ptr_;
        }
    }

    A& operator=(const A& a)
    {
        std::cout << " A operator= ...." << std::endl;
        return *this;
    }

    int* getVal()
    {
        return ptr_;
    }

private:
    int* ptr_;
};

int main(int argc, char* argv[])
{
    std::vector<A> vec;
    // vec.push_back(A());
    A* a = new A();
    vec.push_back(std::move(*a));
    std::cout << a->getVal() << std::endl;
    delete a;
}
