#include "matrix.h"

#include <algorithm>
#include <limits>
#include <ostream>
#include <stdexcept>
#include <utility>

Matrix::Matrix() noexcept : rows_(0), cols_(0), data_(nullptr) {}

Matrix::Matrix(std::size_t rows, std::size_t cols, double value)
    : rows_(rows), cols_(cols), data_(nullptr) {
    const std::size_t count = checked_size(rows_, cols_);
    if (count != 0) {
        data_ = new double[count];
        std::fill(data_, data_ + count, value);
    }
}

Matrix::Matrix(const Matrix& other)
    : rows_(other.rows_), cols_(other.cols_), data_(nullptr) {
    const std::size_t count = checked_size(rows_, cols_);
    if (count != 0) {
        data_ = new double[count];
        std::copy(other.data_, other.data_ + count, data_);
    }
}

Matrix::Matrix(Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {
    other.rows_ = 0;
    other.cols_ = 0;
    other.data_ = nullptr;
}

Matrix::~Matrix() {
    delete[] data_;
}

Matrix& Matrix::operator=(Matrix other) {
    swap(other);
    return *this;
}

void Matrix::swap(Matrix& other) noexcept {
    using std::swap;
    swap(rows_, other.rows_);
    swap(cols_, other.cols_);
    swap(data_, other.data_);
}

std::size_t Matrix::rows() const noexcept {
    return rows_;
}

std::size_t Matrix::cols() const noexcept {
    return cols_;
}

double Matrix::get(std::size_t row, std::size_t col) const {
    return data_[index(row, col)];
}

void Matrix::set(std::size_t row, std::size_t col, double value) {
    data_[index(row, col)] = value;
}

void Matrix::add(const Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("matrix sizes must match for addition");
    }

    const std::size_t count = checked_size(rows_, cols_);
    for (std::size_t i = 0; i < count; ++i) {
        data_[i] += other.data_[i];
    }
}

void Matrix::mul(const Matrix& other) {
    if (cols_ != other.rows_) {
        throw std::invalid_argument(
            "left column count must equal right row count");
    }

    Matrix result(rows_, other.cols_, 0.0);
    for (std::size_t i = 0; i < rows_; ++i) {
        for (std::size_t k = 0; k < cols_; ++k) {
            const double left = data_[i * cols_ + k];
            for (std::size_t j = 0; j < other.cols_; ++j) {
                result.data_[i * other.cols_ + j] +=
                    left * other.data_[k * other.cols_ + j];
            }
        }
    }
    swap(result);
}

Matrix Matrix::submatrix(std::size_t row, std::size_t col) const {
    if (row >= rows_ || col >= cols_) {
        throw std::out_of_range("submatrix row or column is out of range");
    }

    Matrix result(rows_ - 1, cols_ - 1, 0.0);
    std::size_t target_row = 0;

    for (std::size_t source_row = 0; source_row < rows_; ++source_row) {
        if (source_row == row) {
            continue;
        }

        std::size_t target_col = 0;
        for (std::size_t source_col = 0; source_col < cols_; ++source_col) {
            if (source_col == col) {
                continue;
            }
            result.data_[target_row * result.cols_ + target_col] =
                data_[source_row * cols_ + source_col];
            ++target_col;
        }
        ++target_row;
    }

    return result;
}

void Matrix::print(std::ostream& out) const {
    for (std::size_t row = 0; row < rows_; ++row) {
        for (std::size_t col = 0; col < cols_; ++col) {
            if (col != 0) {
                out << ' ';
            }
            out << data_[row * cols_ + col];
        }
        out << '\n';
    }
}

std::size_t Matrix::checked_size(std::size_t rows, std::size_t cols) {
    if (rows != 0 && cols > std::numeric_limits<std::size_t>::max() / rows) {
        throw std::length_error("matrix size is too large");
    }
    return rows * cols;
}

std::size_t Matrix::index(std::size_t row, std::size_t col) const {
    if (row >= rows_ || col >= cols_) {
        throw std::out_of_range("matrix index is out of range");
    }
    return row * cols_ + col;
}
