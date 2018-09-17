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

class test_class2 {
public:
    test_class2()
    {
        cout << __PRETTY_FUNCTION__ << endl;
    }
    test_class2(const test_class2 &)
    {
        cout << __PRETTY_FUNCTION__ << endl;
    }
    ~test_class2()
    {
        cout << __PRETTY_FUNCTION__ << endl;
    }
    // https://en.cppreference.com/w/cpp/language/move_constructor
    // Why move constructor is not implicitly declared for this class?
    // If no user-defined constructors are provided for a classs type, and all of
    // the following is true:
    // - there are no user-declared copy constructors;
    // - there are no user-declared copy assignment operators;
    // - there are no user-declared move assignment operators;
    // - there are no user-declared destructors;
    // then the compiler will declare a move constructor as a non-implicit inline
    // public member of its class with the signator T::T(T &&).

    //// If there are user-declared copy constructor/assignment operator, it implies
    //// that the object cannot be constructed trivially, which in turn implying
    //// that the object cannot be moved trivially also. And thus the compiler
    //// should not generate implicitly declared move constructor, given that
    //// the object cannot be trivially constructed.
};

test_class test_func1()
{
    cout << __PRETTY_FUNCTION__ << endl;
    // https://en.cppreference.com/w/cpp/language/return
    // If ${expression} is prvalue, the result object is initialized directly by
    // that expression. This does not involve a copy or move constructor when the
    // types match. (since c++17)

    // https://en.cppreference.com/w/cpp/language/copy_elision
    // In the initialization of an object, when the source object is a nameless
    // temporary and is of hte same class type (ignoring cv-qualification) as the
    // target object. When the nameless temporary is the operand of a return
    // statement, this variant of copy elision is known as RVO, "return value
    // optimization". (since c++17)
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

test_class2 test_func3()
{
    cout << __PRETTY_FUNCTION__ << endl;
    return test_class2 {};
}

test_class2 test_func4()
{
    cout << __PRETTY_FUNCTION__ << endl;
    test_class2 obj;
    return obj;
}

int main(int argc, const char *argv[])
{
    test_class t1 = test_func1();  // move
    test_class t2 = test_func2();  // move
    test_class2 t3 = test_func3(); // copy
    test_class2 t4 = test_func4(); // copy

    //// Given the output below, there are two constructions happen
    //// 1. return statement -> temp variable.
    //// 2. temp variable -> named variable to be constructed.
#if 0
    // with copy elision.
    test_class test_func1()
    test_class::test_class()
    test_class test_func2()
    test_class::test_class()
    test_class2 test_func3()
    test_class2::test_class2()
    test_class2 test_func4()
    test_class2::test_class2()
    test_class2::~test_class2()
    test_class2::~test_class2()
    test_class::~test_class()
    test_class::~test_class()

    // without copy elision.
    test_class test_func1()
    test_class::test_class()
    test_class::test_class(test_class&&)
    test_class::~test_class()
    test_class::test_class(test_class&&)
    test_class::~test_class()
    test_class test_func2()
    test_class::test_class()
    test_class::test_class(test_class&&)
    test_class::~test_class()
    test_class::test_class(test_class&&)
    test_class::~test_class()
    test_class2 test_func3()
    test_class2::test_class2()
    test_class2::test_class2(const test_class2&)
    test_class2::~test_class2()
    test_class2::test_class2(const test_class2&)
    test_class2::~test_class2()
    test_class2 test_func4()
    test_class2::test_class2()
    test_class2::test_class2(const test_class2&)
    test_class2::~test_class2()
    test_class2::test_class2(const test_class2&)
    test_class2::~test_class2()
    test_class2::~test_class2()
    test_class2::~test_class2()
    test_class::~test_class()
    test_class::~test_class()
#endif
    return 0;
}

