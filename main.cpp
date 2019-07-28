#include <iostream>
#include <functional>

#include "CallableWrapper.hpp"

class Example
{
public:
    void mem_function(int a, int b) { std::cout << a << " " << b << std::endl; }
    void mem_function2(int a, int b) { std::cout << a + 1 << " " << b + 1 << std::endl; }
};

class FunctionObject
{
public:
    ~FunctionObject()
    {
        std::cout << "destroy" << std::endl;
    }

    void operator()()
    {
        std::cout << "called" << std::endl;
    }

};

int main()
{
    using namespace std::placeholders;
    
    Example obj;
    void (*wrapped)(int, int);
    void (*wrapped2)(int, int);
    void (*wrapped3)(int);
    void (*wrapped4)();
    void (*wrapped5)();

    {
        auto result = std::bind(&Example::mem_function, &obj, _1, _2);
        wrapped = Wrapper<0, void(int, int)>::wrap(result);

        auto result2 = std::bind(&Example::mem_function2, &obj, _1, _2);
        wrapped2 = Wrapper<1, void(int, int)>::wrap(result2);

        auto result3 = std::bind(&Example::mem_function, &obj, 5, _1);
        wrapped3 = Wrapper<2, void(int)>::wrap(result3);

        FunctionObject object;
        wrapped4 = Wrapper<3, void()>::wrap(object);

        int a = 5;
        wrapped5 = Wrapper<4, void()>::wrap([a]() mutable {
            std::cout << ++a << std::endl;
        });

    }

    wrapped(1, 2);
    wrapped2(1, 2);
    wrapped3(1);
    wrapped4();
    wrapped5();
}
