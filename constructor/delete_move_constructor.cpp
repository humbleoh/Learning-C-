#include <iostream>

using namespace std;

// To disable copy elision,
// g++ -fno-elide-constructors -O0 -std=c++14

class test_class2 {
public:
    test_class2()
    {
    }

    test_class2(const test_class2 &)
    {
        cout << __FUNCTION__ << endl;
    }

    // The intent on = delete is to provide a declaration that will
    // cause an error if it is selected as the best overload.
    test_class2(test_class2 &&) = delete;
    
    ~test_class2()
    {
        cout << __FUNCTION__ << endl;
    }

    test_class2 &operator=(const test_class2 &) = default;
    test_class2 &operator=(test_class2 &&) = delete;
};

test_class2 test_func3()
{
    cout << __FUNCTION__ << endl;
    return test_class2 {}; // prvalue, so move constructor is selected.
                           // since move constructor is declared but deleted,
                           // compilation error is given.
}

test_class2 test_func4()
{
    cout << __FUNCTION__ << endl;
    test_class2 obj;
    // If ${expression} is an lvalue expression that is (possibly parenthesized)
    // name of an automatic storage duration object declared in the body or as a
    // parameter of the innermost enclosing function or lambda expression, then
    // overload resolution to select the constructor to  use for initialization
    // of the returned value is perform twice:
    // 1. as if ${expression} were an rvalue expression (thus it may select the
    //    move constructor)
    // 2. or if no suitable conversion is available, or if the type of the first
    //    parameter of the selected constructor is not an rvalue reference to the
    //    object's type (possibly cv-qualified), overload resolution is performed
    //    a second time, with ${expression} considered as an lvalue (so it may
    //    select the copy constructor taking a reference to non-const).
    return obj;
}

int main(int argc, const char *argv[])
{
    test_func3();
    test_func4();
    return 0;
}
