#include <iostream>
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
    gMatrix.init(/* arguments to class Matrix*/);
    assert(gMatrix.exists());

    // Use the global variable of type Matrix
    gMatrix.get().transpose();

    // Lasst the global variable must be destroyed
    gMatrix.destroy();
    assert(!gMatrix.exists());

    std::cout << "Completed with no errors.\n";
    return 0;
}
