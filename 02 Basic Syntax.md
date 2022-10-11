# Variable
``` cpp
#include <iostream>

int main() 
{
    int variable = 8;
    std::cout << variable << std::endl;
    variable = 20;
    std::cout << variable << std::endl;
    std::cin.get();
}
```
data type: char(1), short(2), int(4), long(4), long long(8). They can also be combined with unsigned.   
char will treat number as a character.   
for decimal value: float(4), (long) double(8).   
``` cpp
float var1 = 5.5f;
double var2 = 5.2;
```
bool: boolean can be true(1) or false(0).   
sizeof(): to show how big a data type is.  
``` cpp
sizeof(bool);
```

# Function
Functions: prevent code duplication.

# Head file
Head files: store function definition and declaration.  
#pragma once: make sure the content is only copied once, prevent redefinition(duplicate error).   
#include: <> for compiler to search the file, "" for files in current folder.
C standard library: usually has .h suffix. C++ does not.

# Debugging
set break points

# If Statement
Conditions or branches will affect performance. Using mathmatical calculation instead of comparison.   
The following code will print hello!. 
``` cpp
#include <iostream>

int main() 
{
    const char* ptr = "hello!";
    // const char* ptr = nullptr;
    if (ptr)
    {
        std::cout << ptr << std::endl;
    }   
    else
    {
        std::cout << "ptr is null!" <<std::endl;
    }  
}
```

# Loops
for loops and while loops
``` cpp
#include <iostream>

int main() 
{
    for (int i = 0; i < 5; i++)
    {
        std::cout << "Hello world!" << std::endl;
    }
    int i = 0;
    std::cout << "======================" << std::endl;
    while (i < 5)
    {
        std::cout << "Hello world!" << std::endl;
        i++;
    }
    std::cin.get();
}
```
do while: code in loop will be run at least once.

# Control Statement
Used with loops
1. continue: go to the next iteration of the loop. 
2. break: end the loop. Also used in switch.  
3. return: exit the function.

# Pointer
example
``` cpp
#include <iostream>

#define LOG(x) std::cout << x << std::endl

int main() 
{
    char* buffer = new char[8];
    // allocate an 8-byte memory, buffer is a pointer that points to the beginning of the memory
    memset(buffer, 0, 8); // 3 parameter: a pointer, a value, a size.
    char** ptr = &buffer; // pointer to pointer
    delete[] buffer; //
    std::cin.get();
}
```

# Reference
The result of the following example is 2.
``` cpp
#include <iostream>

#define LOG(x) std::cout << x << std::endl

int main() 
{
    int a = 5;
    int& ref = a;
    ref = 2;
    LOG(ref);
}
```
Pass the reference of variables that will influence the variable.
1. use pointer: result 6
``` cpp
#include <iostream>
#define LOG(x) std::cout << x << std::endl
void Increment(int* value) 
{
    (*value)++;
}
int main() 
{
    int a = 5;
    Increment(&a);
    LOG(a);
}
```
2. use reference(syntax sugar): result 6
``` cpp
#include <iostream>
#define LOG(x) std::cout << x << std::endl
void Increment(int& value)
{
    value++;
}
int main() 
{
    int a = 5;
    Increment(a);
    LOG(a);
}
```
