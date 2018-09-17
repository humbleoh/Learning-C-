#include <iostream>

using namespace std;

// To disable copy elision,
// g++ -fno-elide-constructors -O0 -std=c++14

class test_class {
public:
    test_class()
    {
        cout << __PRETTY_FUNCTION__ << endl;
    }

    test_class(const test_class &)
    {
        cout << __PRETTY_FUNCTION__ << endl;
    }
    
    test_class(test_class &&)
    {
        cout << __PRETTY_FUNCTION__ << endl;
    }

    ~test_class()
    {
        cout << __PRETTY_FUNCTION__ << endl;
    }
};

test_class test_func1()
{
    cout << __PRETTY_FUNCTION__ << endl;
    return test_class{}; // prvalue, so move constructor is selected.
}

test_class test_func2()
{
    cout << __PRETTY_FUNCTION__ << endl;
    test_class obj;  
    // https://en.cppreference.com/w/cpp/language/return
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
    test_func1();
    test_func2();
    return 0;
}

