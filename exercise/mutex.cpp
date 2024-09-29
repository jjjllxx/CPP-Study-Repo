#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;

void func1(int& a)
{
    mtx.lock();
    std::cout << "func1 is changing a." << std::endl;
    std::cout << "original a: " << a << std::endl;
    a += 2;
    std::cout << "new a: " << a<< std::endl;
    mtx.unlock();
}

void func2(int& a)
{
    mtx.lock();
    std::cout << "func2 is changing a." << std::endl;
    std::cout << "original a: " << a << std::endl;
    a += 1;
    std::cout << "new a: " << a << std::endl;
    mtx.unlock();
}

int main()
{
    int a = 0;
    std::thread t1(func1, std::ref(a));
    std::cout << "current a: " << a << std::endl;
    std::thread t2(func2, std::ref(a));
    std::cout << "current a: " << a << std::endl;
    t1.join();
    std::cout << "current a: " << a << std::endl;
    t2.join();
    std::cout << "current a: " << a << std::endl;
    return 0;
}