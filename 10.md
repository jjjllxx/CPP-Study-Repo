# Improve C++ Performance
Multi-threading: std::async in the <future> head file.
	
# How to Make String Faster
Try the following code to see how many allocations, and think do we really need so many strings. Try to avoid copy of string.
(1 allocation in total).
``` cpp
#include <iostream>
#include <string>

static u_int32_t allocCnt = 0;

void* operator new(std::size_t size)
{
    allocCnt++;
    std::cout << "Allocationg: " << size << "Bytes" <<std::endl;
    return malloc(size);
}

void printName(const std::string& str)
{
    std::cout << str << std::endl;
}

int main()
{
    std::string name = "abc akfhakfa";
    
    std::string firstName = name.substr(0, 3);
    std::string lastName = name.substr(4, 12);
    
    std::cout << "Allocation times: " << allocCnt << std::endl;
}
```

use std::string_view (C++ 17). Only pass in a pointer(const char*) and a size. (1 allocation in total).
``` cpp
std::string_view firstName(name.c_str(), 3);
std::string_view lastName(name.c_str() + 4, 8);
```

printName() also change to(no need to pass by reference):
``` cpp
void printName(const std::string_view str)
{
    std::cout << str << std::endl;
}
```

Since name is a static string, it can be const char*. (0 allocation in total).
``` cpp
const char* name = "abc akfhakfa";
std::string_view firstName(name, 3);
std::string_view lastName(name + 4, 8);
```
	
# Visualisation of Bench Marking
Use Chrome Function: chrome://tracing/
	
# Singleton
The [singleton pattern](https://en.wikipedia.org/wiki/Singleton_pattern) is a software design pattern that restricts the instantiation of a class to a singular instance.  
Example: Random number generator, renderer..  
Singleton Class Template:
``` cpp
class Singleton
{
public:
    Singleton(const Singleton&) = delete; // delete as copy constructor
    static Singleton& get()
    {
        return instance;
    }
    void func() {};

private:
    Singleton() {}
    static Singleton instance;
};

Singleton Singleton::instance;

int main()
{
    Singleton::get().func(); // To call function of Singleton
}
```

An example of Singleton: Random number generator:
``` cpp
class Random
{
public:
    Random(const Random&) = delete; // delete as copy constructor
    static Random& get()
    {
        return instance;
    }
    float generateRandom() {return randomNum;};

private:
    Random() {}
    static Random instance;
     
    float randomNum = 0.5f;
};

Random Random::instance;

int main()
{
    Random::get().generateRandom(); // To call function of Singleton
}
```
	
# Small String Optimization(SSO)
Small string(less than a certain length(e.g 15 characters)) may be allocated on stack buffer instead of stack buffer.
``` cpp
#include <iostream>
#include <string>

void* operator new(std::size_t size)
{
    std::cout << "Allocating" << size << "bytes" << std::endl;
    return malloc(size);
}

int main()
{
    std::string name = "aaahfkaf"; // will not print
    std::string str = "aafajkfhahfalsfhal";  // will print allocating size in console
}
```
