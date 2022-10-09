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

