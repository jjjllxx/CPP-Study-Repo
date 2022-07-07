# Class
A combination of data and functions.
Visibility: private(by default), protected, public
``` cpp
class Player {
public:
    int x, y;
    int speed;
    void Move(int xa, int ya){
        x += xa * speed;
        y += ya * speed;
    }
};
int main() {
    Player player;
    player.x = 5;
    player.Move(1, -1);
}
```

# Comparison of class and struct
Struct in C++: maintain the compatibility with C. 
An example of struct in Plain Old Data(POD)
``` cpp
struct Vec2 {
    float x, y;
    void Add(const Vec2& other){
        x += other.x;
        y += other.y;
    }
};
```
Use class in inheritance.

# How to write a C++ class
