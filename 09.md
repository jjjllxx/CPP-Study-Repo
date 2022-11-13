# Virtual Destructor
Useful when dealing with polymorphism. Prevent memory leakage.  
Try the following code with or without virtual for the Base destructor.
``` cpp
class Base
{
public:
    Base() {std::cout << "Base Constructor\n";}
    virtual ~Base() {std::cout << "Base Destructor\n";}
};

class Derived : public Base
{
public:
    Derived() {std::cout << "Derived Constructor\n";}
    ~Derived() {std::cout << "Derived Destructor\n";}
};

int main()
{
    Base* base = new Base();
    delete base;
    
    std::cout << "----------------------\n";
    
    Derived* derived = new Derived();
    delete derived;
    
    std::cout << "----------------------\n";
    // If the destructor of Base is not set as virtual,
    // poly will not call the destructor of Derived when deleted.
    Base* poly = new Derived();
    delete poly;
}
```

# Casting
1. static_cast: perform "natural" and low-risk conversions, such as conversions between integers and float types, and between character types. It cannot be used for casts of pointer types.
2. reinterpret_cast: mandatory cast between various types of pointers reinterpret. memory to something else. 
3. const_cast: add or remove const.  
4. dynamic_cast: does not check cast safety, only checks at runtime, returns null if no cast is possible.

``` cpp
double value = 5.25;
int a = (int)value + 5.3; // C style casting
int s = static_cast<int>(value) + 5.3; // Cpp style casting
```

``` cpp
class Base
{
public:
    Base() {}
    virtual ~Base() {}
};

class Derived : public Base
{
public:
    Derived() {}
    ~Derived() {}
};

class AnotherClass : public Base
{
public:
    AnotherClass() {}
    ~AnotherClass() {}
};

int main()
{   
    Derived* derived = new Derived();
    Base* base = derived;
    
    AnotherClass* ac = dynamic_cast<AnotherClass*>(base);  // return nullptr
    Derived* der = dynamic_cast<Derived*>(base);  // successful conversion
}
```
RTTI: Runtime Type Information

# Break Points

# Precompiled Header
Precompiled header: get a bunch of head files and convert them into compile format. Compiler can use them instead of reading those head files again and again.  
Do not put frequentlt changing head files into precompiled header.

# dynamic_cast
dynamic_cast: cast derived type to base type or base type to derived type.
``` cpp
class Entity
{
private:
    virtual void printName() {};  // To make class Entity polymorphic
};

class Player : public Entity
{
};

class Enemy : public Entity
{
};

int main()
{
    Player* player = new Player();
    Entity* actualEnemy = new Enemy();
    Entity* actualPlayer = player;
    
    Player* p0 = dynamic_cast<Player*>(actualPlayer);
    Player* p1 = dynamic_cast<Player*>(actualEnemy);  // return nullptr
}
```
C++ stores runtime type information(RTTI), including runtime information about types. Create extra cost.
RTTI can be enabled or disabled in visualstudio.

# Bench Marking
RAII: Resource Acquisition is Initialization. 
``` cpp
#include <iostream>
#include <array>
#include <chrono>

class Timer
{
public:
    Timer()
    {
        this->start = std::chrono::high_resolution_clock::now();
    }
    ~Timer()
    {
        Timer::stop();
    }
    
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    
    void stop()
    {
        auto end = std::chrono::high_resolution_clock::now();
        auto startTime = std::chrono::time_point_cast<std::chrono::microseconds>(this->start).time_since_epoch().count();
    
        auto endTime = std::chrono::time_point_cast<std::chrono::microseconds>(end).time_since_epoch().count();
        
        auto duriation = endTime - startTime;
        
        std::cout << duriation << "us" << std::endl;
    }

};

int main()
{
    int value = 0;
    {
        Timer timer;
        
        for (int i = 0; i < 10000000; ++i)
        {
            value += 2;
        }
    }
    
    struct Vec2
    {
        float x, y;
    };
    
    std::cout << "Make shared: ";
    {
        std::array<std::shared_ptr<Vec2>, 1000> sharedPtrs;
        Timer timer;
        for (int i = 0; i < sharedPtrs.size(); ++i)
            sharedPtrs[i] = std::make_shared<Vec2>();
    }
    
    std::cout << "New shared: ";
    {
        std::array<std::shared_ptr<Vec2>, 1000> sharedPtrs;
        Timer timer;
        for (int i = 0; i < sharedPtrs.size(); ++i)
            sharedPtrs[i] = std::shared_ptr<Vec2>(new Vec2());
    }
    
    std::cout << "Make unique: ";
    {
        std::array<std::unique_ptr<Vec2>, 1000> sharedPtrs;
        Timer timer;
        for (int i = 0; i < sharedPtrs.size(); ++i)
            sharedPtrs[i] = std::make_unique<Vec2>();
    }
}
```
Test the performance in release mode to avoid extra safety measure.

# Structured Bindings(C++ 17)
Structured Bindings helps to deal with multiple return values.
``` cpp
#include <string>
#include <tuple>

std::tuple<std::string, int> createPerson()
{
    return {"abc", 24};
}

int main()
{
    {// tuple
        auto person = createPerson();
        std::string& name =  std::get<0>(person);
        int age = std::get<1>(person);
    }
    
    {// tie
        std::string name;
        int age;
        std::tie(name, age) = createPerson();
    }
    
    {// structured binding
        auto [name, age] = createPerson();
    }
}
```

# optional(C++ 17)
``` cpp
#include <iostream>
#include <fstream>
#include <string>
#include <optional>

std::optional<std::string> readFile(const std::string& fileName)
{
    std::ifstream stream(fileName);
    
    if (stream)
    {
        std::string result;
        stream.close();
        return result;
    }
    
    return {};
}

int main()
{
    std::optional<std::string> data = readFile("data.txt");
    
    //If data exists, get data, otherwise get the input string or a value.
    std::string value = data.value_or("Not present");
    
    if (data.has_value() == true)
    {
        std::string str = *data;
        data.value(); // get content
        std::cout << "Successful" << std::endl;
    }
    else
    {
        std::cout << "Failed" << std::endl;
    }
}
```

# Store Multiple Data in A Single Variable(C++ 17)
Use std::variant to hold different data type. The size of variant type data is the sizeof all the data types it includes.
``` cpp
#include <iostream>
#include <variant>
#include <string>

int main()
{
    std::variant<std::string, int> data;
    data = "abc";
    std::cout << std::get<std::string>(data) << std::endl;
    data = 2;
    std::cout << std::get<int>(data) << std::endl;
    
    // if data is not string,return nullptr
    auto value = std::get_if<std::string>(&data);
    
    // wrong data type, will get an exception: bad_variant_access
    std::cout << std::get<std::string>(data) << std::endl;
}
```

# How to Store Any Type of data
Although std::any is convienent without listing all the possible data types, may cause type unsafety compared with std::variant.  
1. For small types, std::any store them as a union.
2. For large types, use void*, dynamic allocate memory, which is not good for performance.
So, std::variant will be faster if dealing with large data.

``` cpp
#include <iostream>
#include <any>
#include <string>

int main()
{
    std::any data;
    data = 2;
    data = "abc";  // const char
    data = std::string("abc");
    
    std::string str = std::any_cast<std::string>(data);
    std::string& str0 = std::any_cast<std::string&>(data); // pass by reference
}
```
