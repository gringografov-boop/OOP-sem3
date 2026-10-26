#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>
#include <iosfwd>

class Matrix {
public:
    Matrix() noexcept;
    Matrix(std::size_t rows, std::size_t cols, double value = 0.0);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
    ~Matrix();

    Matrix& operator=(Matrix other);

    void swap(Matrix& other) noexcept;

    [[nodiscard]] std::size_t rows() const noexcept;
    [[nodiscard]] std::size_t cols() const noexcept;

    [[nodiscard]] double get(std::size_t row, std::size_t col) const;
    void set(std::size_t row, std::size_t col, double value);

    void add(const Matrix& other);
    void mul(const Matrix& other);

    [[nodiscard]] Matrix submatrix(std::size_t row, std::size_t col) const;

    void print(std::ostream& out) const;

private:
    std::size_t rows_;
    std::size_t cols_;
    double* data_;

    [[nodiscard]] static std::size_t checked_size(std::size_t rows,
                                                   std::size_t cols);
    [[nodiscard]] std::size_t index(std::size_t row,
                                    std::size_t col) const;
};

#endif
