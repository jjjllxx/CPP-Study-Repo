# How to Deal with Multiple Return Types
1. Pass by reference, then the variable can be changed inside the function.
2. Pass a pointer. Compared with reference, pointer can be nullptr and do some check.
3. Return an array(created on stack). 
4. Return a vector(created on heap, technically slower than array)

Special methods:
1. tuple: can contain any number of variables, regardless of type. Also have std::make_tuple.

``` cpp
const std::tuple<std::string, std::string, int> a = {"abc", "def", 3};
std::cout << std::get<1>(a) << std::endl;  // get "def"
```
2. pair: like tuple, but only has two elements

``` cpp
const std::pair<int, std::string> a = {3, "abc"};
const auto b = std::make_pair(2, "def");
std::cout << a.first << std::endl;  // get 3
std::cout << b.second << std::endl;  // get "abc"
```

To avoid confusion, better return a struct contain all the return values.

# Templates
An example of using templates:
``` cpp
#include <iostream>
#include <string>

template<typename T>  //  can also be written as template<class T>
void print(T t)
{
    std::cout << t << std::endl;
}

int main()
{
    print(5);
    print(5.5f);
    print<std::string>("abc");  // the correct type can also be added for readability
}
```

Another example of a class: 
1. size of array must be known when compiling, and template is evaluate at compiling, so it works(for N in the example). 
2. template can be 2 or more(for T and N).
``` cpp
template<typename T, int N>
class Array
{
private:
    T array[N];
public:
    int getSize() const
    {
        return N;
    }
};

int main()
{
    Array<int, 5> arr;
    std::cout << arr.getSize() << std::endl;
}
```

Do not overuse templates.

# Stack VS Heap
Stack and heap are two areas in the RAM
1. Stack is typically a predefined memory with size of around 2MB.
2. Heap can grow and change as programme goes on.

Allocation
1. Stack allocation: Continuous memory address and fast, just move of pointer according to bytes, memmory released at the end of scope. It is like one CPU instruction.
2. Heap allocation: Memory is not continuous, memory has to be released manually(new - delete). It is a series of things.

Working Principle of new keyword
1. Call the function malloc(memory allocate) to call the underline operating system or platform specific function. 
2. When start the appication, then get a certain amount of RAM, programme will maintain free list, which keeps tracking which block of memory is free. 
3. When asked for dynamic memory, it will go through the free list and find a block of memory at least as large as asked. Then return a pointer to that memory and record size of allocation...
4. If asking for memory exceed free list of the initial allocation. The potential cost is huge. 

Cache misses problem

# Macros
preprocessor will go through all the code start with # (preproccesor directive), then pass to the compiler.
macros: basically replace some texts in code(search and replace).

An example(but not recommend to overuse macros)]
``` cpp
#include <iostream>
#include <string>

#define WAIT std::cin.get()
#define LOG(x) std::cout << x << std::endl  //function-like

int main()
{
    LOG("Hello");
    WAIT;
}
```

Preprocessor definitions: 
``` cpp
#ifdef PROJ_DEBUG
#define LOG(x) std::cout << x << std::endl
#else
#define LOG(x)
#endif
```

Another manner: value of PROJ_DEBUG can be changed to enable or disable macros inside PROJ_DEBUG
``` cpp
#define PROJ_DEBUG 1

#if PROJ_DEBUG == 1
#define LOG(x) std::cout << x << std::endl
#else
#define LOG(x)
#endif
```

Even can define a function with several lines. \(back slash) indicates enter.
``` cpp
#define WAIT int main()\
{\
    std::cin.get();\
}

WAIT
```

# Auto(keyword)
auto can be used when declaring or copying variables. 
example(actually auto should not be used to replace type of short name.
``` cpp
int main()
{
    auto a = 5;
    auto b = 5L;
    auto c = 5.5f;
    auto d = "Hello";
    auto e = a;
}

use auto to replace very long type name to add readability:
``` cpp
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> fruits;
    fruits.push_back("apple");
    fruits.push_back("orange");
    
//    for (std::vector<std::string>::iterator it = fruits.begin(); it != fruits.end(); ++it)
//    {
//        std::cout << *it << std::endl;
//    }
    
    for (auto it = fruits.begin(); it != fruits.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
}
```
