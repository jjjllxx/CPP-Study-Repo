#include <iostream>
#include <memory>

const func()
{
    return 1;
}

void func1()
{
}

int main()
{
    std::allocator<int> alloc;
    int* ptr = alloc.allocate(1);
    alloc.construct(ptr, 42);
    std::cout << "Value: " << *ptr << std::endl;

    alloc.destroy(ptr);
    alloc.deallocate(ptr, 1);
}