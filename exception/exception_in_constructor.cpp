#include <iostream>

using namespace std;

#define TR() do { cout << __PRETTY_FUNCTION__ << endl; } while (0);

// build with g++ -fno-elide-constructors -O0 -std=c++14, because this example
// relies on side effect inside the constructor, where copy elision will bypass it.

class test_class {
public:
    test_class()
    {
        TR()
    }
    test_class(const test_class &)
    {
        TR()
        throw nullptr;
    }
    ~test_class()
    {
        TR();
    }
};

test_class test_func(int *output)
{
    *output = 10;
    return test_class {};    
}

int main(int argc, const char *argv[])
{
    int i = 1;
    cout << i << endl;
    try {
        test_class t1 = test_func(&i);
        // Why return by value is still considered as bad practice?
        // Return by value may invoke constructor, and a constructor may throw
        // exception. If a return-by-value function has side effect, and exception
        // happen during 1. returning from the function or 2. construction of the
        // lvalue, then strong exception safety has been violated.
    }
    catch (...) {
        cout << "CATCH" << endl;
    }
    cout << i << endl;

    //> output:
    //> 1
    //> test_class::test_class()
    //> test_class::test_class(const test_class&)
    //> test_class::~test_class()
    //> CATCH
    //> 10

    return 0;
}

