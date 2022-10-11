# Constructor member initialiser list
Initialise all the variables in the order that they are declared.

``` cpp
class Entity
{
private:
    int score;
    std::string name;
public:
    Entity() :
        score(0),
        name("unknown")
    {
    }

    Entity(const int          score,
           const std::string& name ) :
        score(score),
        name(name) 
    {
    }
};
```
Initialiser list prevents to create member twice(one by default, one in traditional constructor), which causes waste of performance.

# Ternary operator

Ternary operator: a syntax sugar of if-else clause.
``` cpp
static int level = 2;
static int speed = 10;

int main() 
{
    if (level > 5)
    {
        speed = 10;
    }
    else 
    {
        speed = 5;
    }

    // This if-else and ternary operator code are the same.
    speed = level > 5 ? 10 : 5;
}
```

Ternary operator in ternary operator(not recommended):
``` cpp
speed = level > 5 ? level > 10 ? 15 : 10 : 5; 
```

# Create and initialise object
1. stack object: has an automatic lifespan which is decided by the scope where it is declared. As soon as the variable get out of scope, the memory is free. Because when scope end, the stack pops and everything in that scope gets free.
3. heap object: once created will stay until delete it manually.

Creat and initialise object on stack
``` cpp
class Entity
{
private:
    int score;
    std::string name;
public:
    Entity() :
        score(0),
        name("unknown")
    {
    }

    Entity(const int          score,
           const std::string& name ) :
        score(score),
        name(name) 
    {
    }
};

int main() 
{
    Entity e; // always try to create object like this. fast and manageable.
    Entity e2(5, "abc");
}
```
 Two situations of not creating objects on stack
 1. want an object still alive after its scope (explictly control the lifetime of object)
 2. this object is too large in memory(Because stack is usually very small).

``` cpp
Entity* entity = new Entity();
Entity* entity2 = new Entity(5, "abc");
```

1. allocating on the heap takes longer time.
2. have to manually free that memory.

# new keyword
Free list: maintain the address with free bytes.
Must use delete after new.
``` cpp
Entity* e1 = new Entity;  // allocate memory & get a pointer & call the constructor
Entity* e2 = (Entity*)malloc(sizeof(Entity));  // only allocate memory and get a pointer to that address(not recommended)

delete[] b;  // for a pointer to an array, delete should be followed with []
delete e1;
delete e2;
```

# Implict conversion and explicit keyword
Example of implicit conversion/construction
``` cpp
class Entity
{
private:
    std::string name;
    int age;
public:
    Entity(const std::string& name) :
        name(name),
        age(-1)
    {
    }
    
    Entity(const int age) :
        name("unknown"),
        age(age)
    {
    }

    int getAge() const
    {
        return age;
    }
};

void printEntity(const Entity& e)
{
    std::cout << e.getAge() << std::endl;
}

int main() 
{
    Entity a = std::string("abc");  // Entity a("abc");
    Entity b = 24;  // Entity b(24);

    printEntity(22);  // output 22
    printEntity(std::string("aaa"));  // output -1
}
```

explicit keyword: disable implicit conversion.

``` cpp
explicit Entity(const std::string& name) :
        name(name),
        age(-1)
    {
    }

explicit Entity(const int age) :
    name("unknown"),
    age(age)
{
}
```

For low level wrapper, explicit can prevent accidental casting.

# Operator and Operator overloading
