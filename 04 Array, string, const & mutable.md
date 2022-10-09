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
```
