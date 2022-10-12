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
