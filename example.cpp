#include "BindWrapper.hpp"

class Example
{
public:
    void mem_function(int a, int b) { }
};

void global_function(void (*function_pointer)(int, int))
{
	function_pointer(1, 2);
}

int main()
{
    using namespace std::placeholder;
    
    Example obj;
    auto result = std::bind(&Example::mem_function, &obj, _1, _2);
    
    global_function(get_wrapper<0, void, int, int>(result));
    
}
