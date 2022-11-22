# Constructor Member Initialiser List
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

# Ternary Operator

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

# Create and Initialise Object
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

# new(keyword)
Free list: maintain the address with free bytes.
Must use delete after new.
``` cpp
Entity* e1 = new Entity;  // allocate memory & get a pointer & call the constructor
Entity* e2 = (Entity*)malloc(sizeof(Entity));  // only allocate memory and get a pointer to that address(not recommended)

delete[] b;  // for a pointer to an array, delete should be followed with []
delete e1;
delete e2;
```

# Implict Conversion and Explicit Keyword
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

# Operator and Operator Overloading
In operator overloading, it is allowed to define or change the behavior of operator in program.
Example of overloading +, * and <<;
``` cpp
struct Vector2
{
    float x, y;

    Vector2(const float x,
            const float y) :
            x(x),
            y(y)
    {
    }

    Vector2 operator+(const Vector2& other) const
    {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator*(const Vector2& other) const
    {
        return Vector2(x * other.x, y * other.y);
    }
};

int main() 
{
    Vector2 position(4.0f, 4.0f);
    Vector2 speed(0.5f, 1.5f);
    Vector2 powerup(1.1f, 1.1f);

    Vector2 result = position + speed * powerup;

    std::cout << result.x << ' ' << result.y <<std::endl;
}
```

# this(keyword)
*this* is a pointer pointing to the current instance.
``` cpp
class Entity
{
private:
    float x, y;
public:
    Entity(const float x,
           const float y)
    {
        this->x = x;
        this->y = y;
    }
};
```
