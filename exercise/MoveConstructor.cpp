#include <iostream>

class MyResource
{
public:
    MyResource()
    {
        data = new int[1000];
        std::cout << "Resource allocated." << std::endl;
    }

    ~MyResource()
    {
        delete[] data;
        std::cout << "Resource deallocated." << std::endl;
    }

    // Move Constructor
    MyResource(MyResource&& other) :
        data(other.data)
    {
        other.data = nullptr; // Set the resource pointer of the other object to nullptr to prevent duplicate deallocation
        std::cout << "Resource moved." << std::endl;
    }

private:
    int* data;
};

int main()
{
    MyResource resource1;
    MyResource resource2 = std::move(resource1); // Call the Move Constructor using std::move()

    return 0;
}
