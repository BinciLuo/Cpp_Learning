#include <iostream>
#include <string>
using namespace std;
#include "../head/swap.h"
// 基类
class Animal {
public:
    string name;
    Animal(const std::string &name) : name(name) {}

    void eat() {
        std::cout << "Animal is eating." << std::endl;
    }
};

// 中间类1，虚继承 Animal
class Mammal : virtual public Animal {
public:
    Mammal(const std::string &name) : Animal(name) {}
    void breathe() {
        std::cout << "Mammal is breathing." << std::endl;
    }
};

// 中间类2，虚继承 Animal
class Bird : virtual public Animal {
public:
    Bird(const std::string &name) : Animal(name) {}
    void fly() {
        std::cout << "Bird is flying." << std::endl;
    }
};

// 最终派生类，继承 Mammal 和 Bird
class Bat : public Mammal, public Bird {
public:
    Bat(const std::string& name) : Animal(name), Mammal(name), Bird(name) {}

    void sleep() {
        std::cout << "Bat is sleeping." << std::endl;
    }
};

int main() {
    Bat bat("123");
    bat.eat();      // 调用虚继承的基类函数
    bat.breathe();  // 调用虚继承的中间类函数
    bat.fly();      // 调用虚继承的中间类函数
    bat.sleep();    // 调用最终派生类函数

    int a = 1, b = 0;
    swap(a,b);
    cout<<a<<" "<<b<<endl;
    return 0;
}
