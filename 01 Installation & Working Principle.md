# Installation on Mac
Download Xcode -> create a new Xcode project -> name and save the project(choose C++ as language)
In main.cpp
``` cpp
#include <iostream>

int main() 
{
    std::cout << "Hello World!!" << std::endl;
    std::cin.get();
}
```
Product(on the top) -> build(to compile) -> run

# How C++ Works
#include <iostream>: statement after # means preprocess statement, happens before compilation.  
main() function: the entrance of application.  
Head files do not get complied, they get included in preprocess.   
Every .cpp file is compiled to an odject file individually.    
Linker make all the object files into one .exe file.   

Seperate code into different files. Use declaration to enable the compiler, otherwise compile failure.
Linker will find the correct function, otherwise linking error.
For each .cpp file, compiler will generate repective .obj file and the linker will take and stitch them into a .exe file.
``` cpp
#include <iostream>

void Log(const char* message)
{
    std::cout << message << std::endl;
}
```
``` cpp
#include <iostream>
void Log(const char* message);
// declaration or ignore the name of variable: void Log(const char*);

int main() {
    Log("Hello World!!");
    std::cin.get();
}
```

# How C++ Compiler Works
Stage of compilation
1. Preprocessing: include, define, if, ifdef, pragma.  
include: just copy the headfile and put into where the include statement is. 
Example: A head file named as EndBrace.h. It just includes a end brace.
``` cpp
}
```
``` cpp
int Multiply(int a, int b)
{
    int result = a * b;
    return result;
#include "EndBrace.h"
```

define: replace the former with latter
``` cpp
#define INTEGER int
INTEGER Multiply(int a, int b)
{
    INTEGER result = a * b;
    return result;
}
```
if/endif: if satisfy the condition, the code between if and endif will be included.
``` cpp
#if 1
int Multiply(int a, int b)
{
    int result = a * b;
    return result;
}
#endif
```
	
# How C++ linker Works
Linking: find every symbol and function, link them together.
