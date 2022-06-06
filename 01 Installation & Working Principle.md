# Installation

## Mac
Download Xcode -> create a new Xcode project -> name and save the project(choose C++ as language)
In main.cpp
``` cpp
#include <iostream>

int main() {
    std::cout << "Hello World!!" << std::endl;
    std::cin.get();
}
```
Product(on the top) -> build(to compile) -> run
# Working Principle

## How C++ Works
Head files do not get complied, they get included in preprocess.   
Every .cpp file is compiled to an odject file individually.    
Linker make all the object files into one .exe file.   
## How C++ Compiler Works

## How C++ linker Works
