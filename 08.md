# Static Array
static array: array do not grow.

``` cpp
#include <array>

int main()
{
    std::array<int, 5> data;
    data.size();
}
```

# Function Pointer
A pointer pointing to a function address. Simple example:
``` cpp
#include <iostream>

void printHello()
{
    std::cout << "Hello!" << std::endl;
}

void printValue(int a)
{
    std::cout << "value: " << a << std::endl;
}

int main()
{
    auto func = printHello; // get function pointer
    void (*func1)() = printHello; // same
    void (*func2)(int) = printValue; // with input parameter
    
    func();
    func1();
    func2(8);
    func2(10);
}
```

pass a function pointer to another function
``` cpp
#include <iostream>
#include <vector>

void printValue(const int value)
{
    std::cout << "value: " << value << std::endl;
}

void forEach(const std::vector<int>& values, void(*func)(int))
{
    for (const int value: values)
    {
        func(value);
    }
}

int main()
{
    std::vector<int> values = {1, 5, 3, 2, 4};
    forEach(values, printValue);  // use function pointer
    forEach(values, [](const int value){std::cout << "value: " << value << std::endl;});
    // use lambda function
    // []: capture method: how to pass parameter in
    // (): put paramter(s)
}
```

# Lambda
lambda: a way to define anonymous function, whenever there is a function pointer, can use lambda.
``` cpp
#include <iostream>
#include <vector>
#include <functional>

void forEach(const std::vector<int>& values, std::function<void(int)> func)
{
    // use lib <functional>
    for (const int value: values)
    {
        func(value);
    }
}

int main()
{
    std::vector<int> values = {1, 5, 3, 2, 4};
    
    auto lambda = [](const int value){std::cout << "value: " << value << std::endl;};
    forEach(values, lambda);
    
    // lambda can also pass value
    int a = 5;
    int b = 8;
    auto lambda1 = [&a, b](){std::cout<<"a: "<< a << "b: " << b<< std::endl;};
}
```
Refer to cppreference.com for detailed capture method, parameters..  
An application of lambda.
``` cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> values = {1, 5, 3, 2, 4};
    // std::find_if is in lib <algorithm>
    auto it = std::find_if(values.begin(), values.end(), [](const int value){return value > 3;});
    std::cout << *it << std::endl;
}
```

# Namespace std
To avoid namespace conflict, do not use "using namespace std".

# Namespace
To avoid naming conflicts.
No namespace in C language.

# Thread
An example:
``` cpp
#include <iostream>
#include <thread>

static bool isFinished = false;

void doWork()
{
    using namespace std::literals::chrono_literals;
    
    while (isFinished == false)
    {
        std::cout << "This thread id = " << std::this_thread::get_id() << std::endl;
        std::cout << "working...\n";
        std::this_thread::sleep_for(1s);
        // sleep for 1s before get back to while-loop
    }
    
}

int main()
{
    std::thread worker(doWork);
    std::cin.get();  // working... will show until enter
    isFinished = true;
    
    worker.join();
    std::cout << "finished" << std::endl;
    std::cout << "This thread id = " << std::this_thread::get_id() << std::endl;
    // thread id is different from that in doWork function, they are working on different thread
    std::cin.get();  // program will end until another enter
}
```

# Timing
Calculate how long it takes to complete an operation or execute a certain code.
``` cpp
#include <iostream>
#include <thread>
#include <chrono>

int main()
{
    using namespace std::literals::chrono_literals;
    
    auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(1s);
    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<float> duration = end - start;
    std::cout << duration.count() << "s" << std::endl;
}
```

An example of timer:
``` cpp
struct Timer
{
    std::chrono::time_point<std::chrono::steady_clock> start, end;
    std::chrono::duration<float> duration;
    
    Timer()
    {
        start = std::chrono::high_resolution_clock::now();
    }
    
    ~Timer()
    {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        
        std::cout << "Timer took "<< duration.count() * 1000.0f << "ms" << std::endl;
    }
};

void printHello()
{
    Timer timer;
    // Since timer will be destructed at the end of function, it records the time automatically.
    for (std::size_t i = 0; i < 100; ++i)
    {
        std::cout << "Hello!\n"; // use "\n" to replace std::endl to speed up
    }
}

int main()
{
    printHello();
}
```

# Multi-dimensional array
An array of arrays.  A block of memory contains consecutive pointers, pointing to an array in memory.
A buffer of pointer.

``` cpp
// 1d array
int*  array = new int[50];

// 2d array 50 * 20
int** a2d = new int*[50];
for (std::size_t i = 0; i < 50; ++i)
{
    a2d[i] = new int[20];
}


// delete 2d array
for (std::size_t i = 0; i < 50; ++i)
{
    delete[] a2d[i];
}

delete[] a2d;

// 3d array 50 * 20 * 10
int*** a3d = new int**[50];

for (std::size_t i = 0; i < 50; ++i)
{
    a3d[i] = new int*[20];
    for (std::size_t j = 0; j < 20; ++j)
    {
        a3d[i][j] = new int[10];
    }
}

// assign value to 3d array
a3d[0][0][0] = 0;
```

# Sorting
``` cpp
std::vector<int> values = {3, 5, 1, 4, 2};

std::sort(values.begin(), values.end(), std::greater<int>());
// can use an insert function or lambda function to decide how to sort.
for (const int value : values)
{
    std::cout << value << ' ';
}
std::cout << std::endl;

std::sort(values.begin(), values.end(), [](const int a, const int b) {return a < b;});
// If the lambda return true, a will be placed in front of b.
for (const int value : values)
{
    std::cout << value << ' ';
}

std::cout << std::endl;
```

# Type Punning

``` cpp
int a = 50;
double b = *(double*)&a;
// value will get a random value because int(4 bytes) transfer to double(8 bytes).

std::cout << b << std::endl;
```

Convert struct to array
``` cpp
struct Entity
{
    int x;
    int y;
};

int main()
{
    Entity e = {5, 8};
    int* pos = (int*)&e;
    
    std::cout << pos[0] << ", " << pos[1] << std::endl;
    
    int y = *(int*)((char*)&e + 4);
    
    std::cout << y << std::endl; // get 8
}
```

# Union
Multiple ways to access the same data. Union can be more readable compared with type punning.
``` cpp
struct Vector2
{
    int x;
    int y;
};

struct Vector4
{
    union
    {
        // Because of union, two struct share the same memory
        struct
        {
            int a, b, c, d;
        };
        
        struct
        {
            Vector2 v1, v2;
        };
    };
};

int main()
{
    Vector4 vec = {1, 2, 3, 4};
    
    // can access and revise in any method in the union
    std::cout << vec.a << vec.b << vec.c << vec.d << std::endl;
    
    vec.a = 8;
    
    std::cout << vec.v1.x << vec.v1.y << vec.v2.x << vec.v2.y << std::endl;
}
```
