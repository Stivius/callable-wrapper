# Bind to function pointer

It's quite simple header-only wrapper around std::bind result object. The wrapper is generated that allows you to use it with C-style function pointer.

## Usage

Supposing you have C library with some some functions which should receive function pointer as one of their parameters.

```cpp
void c_lib_function(void (*funct_ptr)(int, int)); // function signature from C lib`
```

And you have your function from class Test which you want to pass to the lib function.

```cpp
void Example::mem_function(int a, int b); // your function from class Example
```

You can std::bind this function to make it independent from your class object and here comes the wrapper which allows to pass the bind result to C library function:

```cpp
#include "BindWrapper.hpp"

class Example
{
public:
    void mem_function(int a, int b) { }
};

int main()
{
    using namespace std::placeholders;
    
    Example obj;
    auto result = std::bind(&Example::mem_function, &obj, _1, _2);
    
    c_lib_function(get_wrapper<0, void, int, int>(result));
    
}

```

