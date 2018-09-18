#include <iostream>
#include <memory>

using namespace std;

#define TR() do { cout << __PRETTY_FUNCTION__ << endl; } while (0)

class base_class {
public:
    base_class()  { TR(); }
    // Inheritance should always be for polymorphism.
    ~base_class() { TR(); }
};


class derived_class : public base_class {
public:
    derived_class()  { TR(); }
    ~derived_class() { TR(); }
};

class poly_base_class {
public:
    poly_base_class() { TR(); }
    virtual ~poly_base_class() { TR(); }
};

class poly_derived_class : public poly_base_class {
public:
    poly_derived_class() { TR(); }
    ~poly_derived_class() { TR(); }
};

int main(int argc, const char *argv[])
{
    derived_class a;
    std::unique_ptr<derived_class> pd1 { new derived_class{} };
    // dangerous, derived portion will not be destructed, because the destructor
    // is not virtual.
    std::unique_ptr<base_class> pd2 { new derived_class{} };
    std::unique_ptr<poly_base_class> pd3 { new poly_derived_class{} };

    //> output
    //> base_class::base_class()
    //> derived_class::derived_class()
    //> base_class::base_class()
    //> derived_class::derived_class()
    //> base_class::base_class()
    //> derived_class::derived_class()
    //> poly_base_class::poly_base_class()
    //> poly_derived_class::poly_derived_class()
    //> virtual poly_derived_class::~poly_derived_class()
    //> virtual poly_base_class::~poly_base_class()
    //> base_class::~base_class()
    //> derived_class::~derived_class()
    //> base_class::~base_class()
    //> derived_class::~derived_class()
    //> base_class::~base_class()

    return 0;
}
