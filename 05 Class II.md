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
