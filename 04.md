# Array
Array: a collection of elements.
Index: the variable in an array that refers to.
Memeory access violation: access memory does not belong to the array(access illegal index).

Array usually combines with for loop.
``` cpp
int main() 
{
    int example[5];
    int* ptr = example;

    for (int i = 0; i < 5; ++i)
    {
        example[i] = 2;
    }

    example[2] = 5; // two way to access elements in an array and change value
    *(ptr + 2) = 8;
}
```

``` cpp
int example[5]; // created on stack, will be destroyed at the end of main function.
int* another = new int[5]; // created on heap, will be alive until destroy it manually.

delete [] another;
```

memory indirection: pointer points to another block of memory which holds actual array. May cause memory fragmentation and cache miss.   
create array on stack to prevent pointer jumping around memory.   
In C++ 11, there is std::array.

size -> byte   
count -> number

# String
``` cpp
#include <string>

int main() 
{
    // C version
    const char* name = "abc";  
    const char name2[4] = {'a', 'b', 'c', 0};

    // C++ version, need include <string> lib
    std::string name3 = "abc";  
    name3.size();
    name3 += "hello!";
    bool isContains = name3.find("he") !=  std::string::npos;
}
```

# String Literal
``` cpp
// p is a pointer, pointing to const area. 
// Revising p[0] is revising const content, which is not allowed.
char *p = "hello"; 

// Compiler creates a string p on stack, conpy "hello" from const area to p.
// Revising p[0] is revising an element of array , which is allowed.
char p[] = "hello";  
```

Different type of char(error may happen for different compiler):
``` cpp
const char* name = u8"abc";  // 1 Byte ->8 bits, utf8
const wchar_t* name2 = L"abc";
const char16_t* name3 = u"abc";  // 2 Bytes ->16 bits, utf16
const char32_t* name4 = U"abc";  // 4 Bytes ->32 bits, utf32 
```

# Const

const and pointer:
``` cpp
const int* a = new int;  // The content a pointing to cannot be modified.
int const* b = new int;  // Same with a;
int* const c = new int;  // The content of b can be changed, but b cannot be resigned and point to something else.
const int* const d = new int;  // Both cannot be changed.

// The following code causes error.
(*a) = 2;  // Dereference and change the value.
(*b) = 2;
c++; // Change the address of c
```

const after a method(only in class): this method will not modify any of actual class(class member).

``` cpp
class Entity
{
private:
    int mX, mY;
public:
    int getX() const
    {
        return mX;
    }

    void setX(int x)
    {
        mX = x;
    }
}

void printEntity(const Entity& e)
{
    // If getX() is not declared with const, it cannot be called here;
    // Because we pass a const reference of Entity. It must be confirmed that getX() will not change Entity e.
    std::cout << e.getX() << std::endl; 
}
```

# Mutable
Variable marked as mutable can be modified in const method.

``` cpp
class Entity
{
private:
    int mX, mY;
    mutable int debugCount = 0;
public:
    int getX() const
    {
        debugCount++;
        return mX;
    }
};
```

For a lambda expression with mutable, it can operate directly on input parameter when capture by value.
This is not capture by reference, it is still a capture by value and does not modify original value. 
``` cpp
int x = 8; 
auto f = [=]() mutable
{
    x++;
    std::cout << x << std::endl;
};

f();
```

In this example, x will still be 8 after calling the lambda expression. 
