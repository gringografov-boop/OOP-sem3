#include "matrix.h"
#include <gtest/gtest.h>
#include <sstream>
#include <stdexcept>
#include <utility>

TEST(MatrixTest, Empty) {
    const Matrix a;
    EXPECT_EQ(a.rows(), 0U);
    EXPECT_EQ(a.cols(), 0U);
}

TEST(MatrixTest, CreateAndAccess) {
    Matrix a(2, 3, 5.0);
    EXPECT_EQ(a.rows(), 2U);
    EXPECT_EQ(a.cols(), 3U);
    EXPECT_DOUBLE_EQ(a.get(1, 2), 5.0);
    a.set(1, 2, 7.0);
    EXPECT_DOUBLE_EQ(a.get(1, 2), 7.0);
}

TEST(MatrixTest, CopyConstructor) {
    Matrix a(2, 2, 3.0);
    Matrix b(a);
    b.set(0, 0, 9.0);
    EXPECT_DOUBLE_EQ(a.get(0, 0), 3.0);
    EXPECT_DOUBLE_EQ(b.get(0, 0), 9.0);
}

TEST(MatrixTest, MoveConstructor) {
    Matrix a(2, 2, 4.0);
    Matrix b(std::move(a));
    EXPECT_DOUBLE_EQ(b.get(1, 1), 4.0);
    EXPECT_EQ(a.rows(), 0U);
    EXPECT_EQ(a.cols(), 0U);
}

TEST(MatrixTest, CopyAssignment) {
    Matrix a(2, 3, 6.0), b(1, 1, 0.0);
    b = a;
    ASSERT_EQ(b.rows(), 2U);
    ASSERT_EQ(b.cols(), 3U);
    b.set(1, 2, 8.0);
    EXPECT_DOUBLE_EQ(a.get(1, 2), 6.0);
    EXPECT_DOUBLE_EQ(b.get(1, 2), 8.0);
}

TEST(MatrixTest, MoveAssignment) {
    Matrix a(2, 2, 8.0), b(1, 1, 0.0);
    b = std::move(a);
    EXPECT_DOUBLE_EQ(b.get(1, 1), 8.0);
    EXPECT_EQ(a.rows(), 0U);
    EXPECT_EQ(a.cols(), 0U);
}

TEST(MatrixTest, SelfAssignment) {
    Matrix a(2, 2, 7.0);
    const Matrix& same = a;
    a = same;
    EXPECT_EQ(a.rows(), 2U);
    EXPECT_EQ(a.cols(), 2U);
    EXPECT_DOUBLE_EQ(a.get(1, 1), 7.0);
}

TEST(MatrixTest, Addition) {
    Matrix a(2, 2, 1.0), b(2, 2, 2.0);
    a.add(b);
    EXPECT_DOUBLE_EQ(a.get(0, 0), 3.0);
    EXPECT_DOUBLE_EQ(a.get(1, 1), 3.0);
    EXPECT_THROW(a.add(Matrix(1, 1)), std::invalid_argument);
}

TEST(MatrixTest, Multiplication) {
    Matrix a(2, 3, 2.0), b(3, 2, 3.0);
    a.mul(b);
    ASSERT_EQ(a.rows(), 2U);
    ASSERT_EQ(a.cols(), 2U);
    EXPECT_DOUBLE_EQ(a.get(0, 0), 18.0);
    EXPECT_DOUBLE_EQ(a.get(1, 1), 18.0);
    EXPECT_THROW(a.mul(Matrix(3, 1)), std::invalid_argument);
}

TEST(MatrixTest, Print) {
    const Matrix a(1, 2, 5.0);
    std::ostringstream out;
    a.print(out);
    EXPECT_EQ(out.view(), "5 5\n");
}

TEST(MatrixTest, Submatrix) {
    Matrix a(3, 3);
    for (std::size_t r = 0; r < 3; ++r)
        for (std::size_t c = 0; c < 3; ++c)
            a.set(r, c, static_cast<double>(r * 3 + c + 1));
    Matrix b = a.submatrix(1, 1);
    ASSERT_EQ(b.rows(), 2U);
    ASSERT_EQ(b.cols(), 2U);
    EXPECT_DOUBLE_EQ(b.get(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(b.get(0, 1), 3.0);
    EXPECT_DOUBLE_EQ(b.get(1, 0), 7.0);
    EXPECT_DOUBLE_EQ(b.get(1, 1), 9.0);
    b.set(0, 0, 99.0);
    EXPECT_DOUBLE_EQ(a.get(0, 0), 1.0);
}

TEST(MatrixTest, SubmatrixBoundary) {
    const Matrix a(1, 1, 42.0);
    const Matrix b = a.submatrix(0, 0);
    EXPECT_EQ(b.rows(), 0U);
    EXPECT_EQ(b.cols(), 0U);
    EXPECT_THROW((void)a.submatrix(1, 0), std::out_of_range);
    EXPECT_THROW((void)a.submatrix(0, 1), std::out_of_range);
    EXPECT_THROW((void)b.submatrix(0, 0), std::out_of_range);
}