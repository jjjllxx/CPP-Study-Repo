# Tracking Memory Allocation
A little tool to track memory
``` cpp
#include <iostream>

struct AllocationMetrics
{
    int32_t totalAllocated = 0;
    int32_t totalFreed = 0;
    
    int32_t getCurrentUsage()
    {
        return this->totalAllocated - this->totalFreed;
    }
};

static AllocationMetrics memoryTracker;

void* operator new(std::size_t size)
{
    memoryTracker.totalAllocated += size;
    return malloc(size);
}

void operator delete(void* memory, std::size_t size)
{
    memoryTracker.totalFreed += size;
    free(memory);
}

void printMemoryUsage()
{
    std::cout << "Memory used: " << memoryTracker.getCurrentUsage() << "byts\n";
}
```

# Lvalues and Rvalues
Rvalue cannot be assigned with value. Lvalue has location in memory.
The following example is feasible because it returns a reference of lvalue.
``` cpp
int& getValue()
{
    static int value = 10;
    return value;
}

int main()
{
    int i = getValue();
    getValue() = 5;
}
```

A  rvalue is not allowed to be assigned to a lvalue reference. In another word, can only have lvalue reference of a lvalue.
``` cpp
void setValue(int& i)
{
}

int main()
{
    int i = 10;
    setValue(i);
    setValue(10); // This is not allowed
}
```

A special rule: rvalue can be assigned to const lvalue reference.
``` cpp
const int& i = 10;
```

Use lvalue reference to check one value is lvalue or rvalue.
``` cpp
void printName(std::string& name)
{
    
}

int main()
{
    std::string firstName = "aasdas";
    std::string lastName = "ajhfalfkldfjds";
    std::string fullName = firstName + lastName;
    
    printName(fullName);
    printName(firstName + lastName);  // This is not allowed, because it is a rvalue.
    // Solution: add const to name in printName()
}
```

&&: rvalue reference, only receive temporary object.
``` cpp
void printName(std::string&& name)
{
    
}

int main()
{
    std::string firstName = "aasdas";
    std::string lastName = "ajhfalfkldfjds";
    std::string fullName = firstName + lastName;
  
    printName(fullName); // This is not allowed, because it is a lvalue.
    printName(firstName + lastName);
}
```

The following code can be used to check whether it is 
``` cpp
void printName(const std::string& name)
{
    std::cout << "[lvalue]" << std::endl;
}

void printName(std::string&& name)
{
    std::cout << "[rvalue]" << std::endl;
}

int main()
{
    std::string firstName = "aasdas";
    std::string lastName = "ajhfalfkldfjds";
    std::string fullName = firstName + lastName;
    
    printName(fullName); // This is not allowed, because it is a lvalue.
    printName(firstName + lastName);
}
```

## Continous Integration
Use Jenkins

## Static Analysis

## Argument Evaluation Order
Try the following code in debug/realse mode, in version before C++ 17(excluded) and after C++ 17(included). The result of clang/gcc may also be different.  The correct answer of following code should be undefined.
``` cpp
void printSum(int a, int b)
{
    std::cout << a << '+' << b << '=' << (a + b) << std::endl;
}

int main()
{
    int value = 0;
    printSum(value++, value++);
    
    int value0 = 0;
    printSum(++value0, ++value);
}
```
C++ 17: The postfix-expression is sequenced before each expression in the expression-list and any default argument.   
Compile and run different version of C++: wandbox.org

# Move Semantics
C++11 introduces rvalue reference which is necessary for move semantics.

``` cpp
class String
{
public:
    String() = default;
    String(const char* string)
    {
        printf("Create!\n");
        this->size = std::strlen(string);
        this->data = new char[this->size];
        std::memcpy(this->data, string, this->size);
    }
    
    String(const String& other)
    {
        printf("Copied!\n");
        this->size = other.size;
        this->data = new char[this->size];
        std::memcpy(this->data, other.data, this->size);
    }
    
    // Move constructor
    String(String&& other) noexcept
    {
        printf("Moved!\n");
        this->size = other.size;
        this->data = other.data;
        
        other.size = 0;
        other.data = nullptr;
    }
    
    ~String()
    {
        printf("Destroyed!\n");
        delete this->data;
    }
    
    void print()
    {
        for (size_t i = 0; i < this->size; ++i)
        {
            printf("%c", this->data[i]);
        }
        
        printf("\n");
    }
private:
    char* data;
    std::size_t size;
};

class Entity
{
public:
    Entity(const String& name):
        name(name)
    {
    }
    // A constructor to receive tempory data.
    Entity(String&& string):
    name((String&&)name)  // tranfer to the reference of right value explicitly
    // name(std::move(name))
    {
        
    }
    void printName()
    {
        this->name.print();
    }
private:
    String name;
};

int main()
{
    Entity entity = Entity(String("asaafa"));
    entity.printName();
}
```

## Move Assignment Operator
Use the class in last section
``` cpp
String str = "Hello!";
String dest = std::move(str);
```

Assignment Operator
``` cpp
String& operator=(String&& other) noexcept
{
    if(this != &other)
    {
        printf("Assigned!\n");
        delete[] this->data;

        this->size = other.size;
        this->data = other.data;

        other.size = 0;
        other.data = nullptr;
    }

    return *this;
}

int main()
{
    String apple = "apple!";
    String dest;
    apple.print();
    dest.print();
    
    dest = std::move(apple);
    
    apple.print();
    dest.print();
}
```
