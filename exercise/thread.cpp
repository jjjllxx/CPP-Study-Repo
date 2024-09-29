#include <iostream>
#include <thread>

void func1(int& a)
{
    std::cout << "parameter: "<< a << std::endl;
    std::cout << "sub thread id in sub: " << std::this_thread::get_id() << std::endl;
}

void func2()
{
    std::cout << "Hello from thread2!" << std::endl;
}

int main()
{
    int a  = 9;
    std::thread t1(func1, std::ref(a));
    std::cout << "sub thread id in main: " << t1.get_id() << std::endl;
    t1.join();
    return 0;
}