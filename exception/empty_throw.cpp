#include <iostream>
#include <exception>

using namespace std;

void throw_nothing()
{
    throw;
}

int main(int argc, const char *argv[])
{
    std::set_terminate([](){ cout << "Hello, Terminate" << endl; });
    throw_nothing();
    return 0;
}
