#include <iostream>
#include <exception>

using namespace std;

void throw_nothing()
{
    // If no exception is presently being handled, executing a throw expression
    // with no operand calls std::terminate(.)
    throw;
}

int main(int argc, const char *argv[])
{
    std::set_terminate([](){ cout << "Hello, Terminate" << endl; });
    throw_nothing();
    return 0;
}
