# Variable
``` cpp
#include <iostream>

int main() {
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

# if statement
Conditions or branches will affect performance. Using mathmatical calculation instead of comparison.   
The following code will print hello!. 
``` cpp
#include <iostream>

int main() {
    const char* ptr = "hello!";
    // const char* ptr = nullptr;
    if (ptr)
        std::cout << ptr << std::endl;
    else
        std::cout << "ptr is null!" <<std::endl;
}
```

# loops
for loops and while loops
``` cpp
#include <iostream>

int main() {
    for (int i = 0; i < 5; i++){
        std::cout << "Hello world!" << std::endl;
    }
    int i = 0;
    std::cout << "======================" << std::endl;
    while (i < 5) {
        std::cout << "Hello world!" << std::endl;
        i++;
    }
    std::cin.get();
}
```
do while: code in loop will be run at least once.

# control statement
Used with loops
1. continue: go to the next iteration of the loop. 
2. break: end the loop. Also used in switch.  
3. return: exit the function.

