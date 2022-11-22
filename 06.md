# Object Lifetime
Scope: function scope, if-statement scope, loop scope, empty scope(only curly brackets), class scope...
Variable allocated on the stack will be destroyed automatically at the end of scope.

``` cpp
class Entity
{
public:
    Entity() {}
    ~Entity() {}
};

class ScopePtr
{
private:
    Entity* entityPtr;
public:
    ScopePtr(Entity* entityPtr) :
        entityPtr(entityPtr) 
    {
    }

    ~ScopePtr()
    {
        delete entityPtr;
    }
};

int main() 
{
    {
        ScopePtr sPtr = new Entity();  // This will be destroyed after the scope because sPtr itself is allocated on stack.
        Entity* e = new Entity();  // This will not be destroyed because it is allocated on heap.
    }
}
```
Usage:
1. timer: to record time in a scope, do not need to stop the timer manually.
2. mutex locking

# Smart Pointer
smart pointer: 
1. a wrapper around a real raw pointer. 
2. to use smart pointer, include <memory> lib.

unique_ptr:
1. a scope pointer. If it is out of scope, it will be destroyed(call delete).
2. unique_ptr must be unique. it cannot be copied. If a unique pointer is copied, when one of them is dead, the memory they pointing to will be released, so the other one will point to memory has been freed.

``` cpp
class Entity
{
public:
    Entity()
    {
        std::cout << "Entity is created" << std::endl;
    }

    ~Entity()
    {
        std::cout << "Entity is destroyed" << std::endl;
    }
};

int main() 
{
    {
        std::unique_ptr<Entity> e1(new Entity());  // Two methods are the same.
        std::unique_ptr<Entity> e2 = std::make_unique<Entity>();  // This is recommended for exception safety. Support from C++14.
    }
}
```

shared_ptr:
1. principle: reference counting, tracking how many references to the pointer.
2. As soon as the count gets zero, it is deleted.
3. shared_ptr requires a memory, called control block, to store the reference count.
4. This is not recommended:
``` cpp
std::shared_ptr<Entity> e1(new Entity());  // Do not use this because it need two times of allocation, less efficient.
```
5. when a shared_ptr copied a shared_ptr, it will add reference count.
``` cpp
int main()
{
    {
        std::shared_ptr<Entity> e0;
        {
            std::shared_ptr<Entity> e1 = std::make_shared<Entity>();
            std::weak_ptr<Entity> e2 = e1;  // weak_ptr will not add reference count
            e0 = e1;
        }
        // shared_ptr will not be destroyed here because reference count is 1.
    }
    // It will be destroyed here.
}
```

weak_ptr: when copying a shared_ptr, it will not add reference count.
    
# Copy and Copy Constructor
Copy: copy data/memory.

The following program will crash.
Two String has the exact same char* pointer, pointing to the same memory address.
When the scope ends and the destructor is called, trying to free the same memory block twice.

``` cpp
class String
{
private:
    char* buffer;
    std::size_t size;
public:
    String(const char* string)
    {
        size = strlen(string);
        buffer = new char[size + 1]; // to copy the ultimation character
        memcpy(buffer, string, size + 1);
    }
    
    ~String()
    {
        delete [] buffer;
    }
    
    char& operator[](const std::size_t idx)
    {
        return buffer[idx];
    }
    
    // set function as friend function, then it can call private member/method
    friend std::ostream& operator<<(std::ostream& stream, const String& string);
};

std::ostream& operator<<(std::ostream& stream, const String& string)
{
    stream << string.buffer;
    return stream;
}

int main()
{
    String string("abcabc");
    String second = string;  // shallow copy
    
    second[2] = 'e'; // will change both string and second
    
    std::cout << string << std::endl;
    std::cout << second << std::endl; 
}
```

copy constructor: will be called when copying(for same type)
``` cpp
class String
{
private:
    char* buffer;
    std::size_t size;
public:
    String(const char* string)
    {
        size = strlen(string);
        buffer = new char[size + 1]; // to copy the ultimation character
        memcpy(buffer, string, size + 1);
    }
    
    String(const String& other) :
        size(other.size)
    {
        buffer = new char[size + 1];
        memcpy(buffer, other.buffer, size + 1);
    }
    
    ~String()
    {
        delete [] buffer;
    }
    // set function as friend function, then it can call private member/method
    char& operator[](const std::size_t idx)
    {
        return buffer[idx];
    }
    
    friend std::ostream& operator<<(std::ostream& stream, const String& string);
};



std::ostream& operator<<(std::ostream& stream, const String& string)
{
    stream << string.buffer;
    return stream;
}

int main()
{
    String string("abcabc");
    String second = string;  // deep copy
    
    second[2] = 'e'; // will only change second
    
    std::cout << string << std::endl;
    std::cout << second << std::endl;
}
// will not crash
```
Always pass parameter by const reference
    
# Array Operator
``` cpp
class Entity
{
private:
    int x;
public:
    void print()
    {
        std::cout << "Hello!" <<std::endl;
    }
};

class ScopePtr
{
private:
    Entity* obj;
public:
    ScopePtr(Entity*  entity) :
        obj(entity)
    {
    }
    
    ~ScopePtr()
    {
        delete obj;
    }
    
    // overload -> operator
    Entity* operator->()
    {
        return obj;
    }
};

int main()
{
    ScopePtr entity = new Entity;
    
    entity->print();
}
```

calculate offset in the memory

``` cpp
struct Vector3
{
    float x, y, z;
};

int main()
{
    int offsetX = (int)&((Vector3*)nullptr)->x; // get 0;
    int offsetY = (int)&((Vector3*)nullptr)->y; // get 4;
    int offsetZ = (int)&((Vector3*)nullptr)->z; // get 8;
}
```

# Dynamic arrays
standard template library(STL): containers
``` cpp
#include <iostream>
#include <vector>  // need include vector lib

struct Vertex
{
    float x, y, z;
};

std::ostream& operator<<(std::ostream& stream, const Vertex& vertex)
{
    stream << vertex.x << ", " << vertex.y << ", " << vertex.z;
    return stream;
}

int main()
{
    std::vector<Vertex> vertices;
    vertices.push_back({1, 2, 3});
    vertices.push_back({4, 5, 6});
    
    vertices.size();  // get the number of elements
    
    for (Vertex& v : vertices)
    {
        std::cout << v << std::endl;
    }
    
    vertices.erase(vertices.begin() + 1); // remove the second element
    vertices.clear(); // remove all the elements in vector
}
```
Remember always pass by reference when passing into a function.

# Use Vector in an optimal way

``` cpp
struct Vertex
{
    float x, y, z;
    
    Vertex(const float x, const float y, const float z) :
        x(x),
        y(y),
        z(z)
    {
    }
    
    Vertex(const Vertex& vertex) :
        x(vertex.x),
        y(vertex.y),
        z(vertex.z)
    {
        std::cout << "Copied!" << std::endl;
    }
};

int main()
{
    std::vector<Vertex> vertices;
    vertices.reserve(3);
    
    vertices.emplace_back(1, 2, 3);
    vertices.emplace_back(4, 5, 6);
    vertices.emplace_back(7, 8, 9);
    
//    vertices.push_back(Vertex(1, 2, 3));
//    vertices.push_back(Vertex(4, 5, 6));
//    vertices.push_back(Vertex(7, 8, 9));
}
```
copy times: 
||without reverse| with reverse|
|----|----|----|
|push_back| 6 | 3|
|emplace_back| 3|0|

# Use External Libraries (Static Link)
32 bit binary file or 64 bit binary file: not related with the computer system, but the file you are going to make (must match).      
static linking: library will be put in .exe files， happen when compiling.   
dynamic linking: link at runtime, still some linkage can be loaded on the fly(loadLibrary function).    
	
To include file,   
<> : for external lib   
"" : check relative path first, use it for files in project   
	
# Dynamic Linkage

# Create and Use Libraries
1. Create two projects under one solution(.sln).
2. One is set as application, another is set as static library.
