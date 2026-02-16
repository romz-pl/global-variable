#include <iostream>
#include <cassert>
#include "global.h"

class Matrix
{
public:
    Matrix() {}
    Matrix transpose() const { return Matrix{}; }
};

global<Matrix> gMatrix;

void transpose(Matrix& m)
{
    m.transpose();
}

int main()
{
    // First, the global variable must be initialized
    assert(!gMatrix.exists());
    gMatrix.init(/* arguments to class Matrix*/);
    assert(gMatrix.exists());

    try {
        gMatrix.init();
    }
    catch(const std::runtime_error&)
    {
        std::cout << "Double init throws\n";
    }

    // Use the global variable of type Matrix
    gMatrix.with(transpose);

    // Lastly the global variable must be destroyed
    gMatrix.reset();
    assert(!gMatrix.exists());

    std::cout << "Completed with no errors.\n";
    return 0;
}
