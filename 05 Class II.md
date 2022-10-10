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
