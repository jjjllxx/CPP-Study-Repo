#include <iostream>

extern int globalVar;
extern void printMsg();

int main()
{
    std::cout << "globalVar: " << globalVar << std::endl;

    printMsg();
}