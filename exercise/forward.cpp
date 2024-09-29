#include <iostream>

void anotherFunction(int& value)
{
    std::cout << "Lvalue reference: " << value << std::endl;
}

void anotherFunction(int&& value)
{
    std::cout << "Rvalue reference: " << value << std::endl;
}

template<typename T>
void forwardFunction(T&& arg)
{
    anotherFunction(std::forward<T>(arg));
}

int main()
{
    int x = 42;
    forwardFunction(x);   // Calls lvalue reference overload
    forwardFunction(123); // Calls rvalue reference overload
    anotherFunction(x); 
    anotherFunction(123);
    return 0;
}
