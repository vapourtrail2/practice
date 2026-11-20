#include <iostream>
using namespace std;

//使用重载
class Vector2D {
public:
    Vector2D(int x, int y) : x(x), y(y){};

    Vector2D operator+(Vector2D& point) const{
        return Vector2D(x + point.x, y + point.y);
    }
    
    void print() {
        cout << x << "," << y << endl;
    }
private:
    int x;
    int y;
};


int main()
{
    Vector2D p1(1, 2);
    Vector2D p2(2, 5);
    
    Vector2D p3 = p1 + p2;   

    p3.print();
    
    return 0;
}

