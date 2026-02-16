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

int main()
{
    // First, the global variable must be initialized
    assert(!gMatrix.exists());
    assert(!gMatrix);
    gMatrix.init(/* arguments to class Matrix*/);
    assert(gMatrix.exists());
    assert(gMatrix);

    // Use the global variable of type Matrix
    gMatrix.get().transpose();

    // Lastly the global variable must be destroyed
    gMatrix.reset();
    assert(!gMatrix.exists());
    assert(!gMatrix);

    std::cout << "Completed with no errors.\n";
    return 0;
}
