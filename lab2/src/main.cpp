#include "matrix.h"

#include <iostream>
#include <utility>

int main() {
    Matrix a(2, 2, 1.0);
    Matrix b(2, 2, 2.0);

    Matrix sum(a);
    sum.add(b);
    std::cout << "A + B:\n";
    sum.print(std::cout);

    Matrix product(a);
    product.mul(b);
    std::cout << "A * B:\n";
    product.print(std::cout);

    Matrix source(3, 3, 0.0);
    double value = 1.0;
    for (std::size_t row = 0; row < source.rows(); ++row) {
        for (std::size_t col = 0; col < source.cols(); ++col) {
            source.set(row, col, value++);
        }
    }

    Matrix result = source.submatrix(1, 1);
    std::cout << "Submatrix without row 1 and column 1:\n";
    result.print(std::cout);

    Matrix moved(std::move(result));
    std::cout << "Moved result is " << moved.rows() << 'x' << moved.cols()
              << ", source is " << result.rows() << 'x' << result.cols()
              << '\n';

    return 0;
}
