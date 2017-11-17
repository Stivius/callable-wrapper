#include <iostream>
#include <functional>

#include "BindWrapper.hpp"

class Example
{
public:
    void mem_function(int a, int b) { std::cout << a << " " << b << std::endl; }
};

void global_function(void (*function_pointer)(int, int))
{
	function_pointer(1, 2);
}

int main()
{
    using namespace std::placeholders;
    
    Example obj;
    auto result = std::bind(&Example::mem_function, &obj, _1, _2);
    
    global_function(get_wrapper<0, void, int, int>(result));
    
}
