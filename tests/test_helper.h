// @author G. Hemingway, copyright 2025 - All rights reserved
#ifndef TESTHELPER_H
#define TESTHELPER_H

#include "vector.h"
#include <fstream>
#include <gtest/gtest.h>

/**
 *  Given a test vector and a correct vector, this function will check if the
 *  two vectors are the same, up to some tolerance level. If the test fails,
 *  abort() is called.
 *  @param test - lhs
 *  @param correct - rhs
 *  @param tol - allowed distance
 */
inline void assertVector(const Vector2& test, const Vector2& correct, const double tol = 0.00001)
{
    EXPECT_NEAR((correct - test).norm(), 0.0, tol);
}

/**
 *  A helper method for creating 2-dimensional vectors.
 *  @param x - x value
 *  @param y - y value
 *  @return created vector
 */
inline Vector2 makeVector2(const double x = 0, const double y = 0)
{
    Vector2 v;
    v[0] = x;
    v[1] = y;
    return v;
}

/**
 *  A RAII struct that will close an ifstream.
 */
struct FileCloser {
    explicit FileCloser(std::ifstream& f)
        : file_(f)
    {
    }

    ~FileCloser()
    {
        file_.close();
    }

private:
    std::ifstream& file_;
};

/**
 *  Returns the next vector in the file.
 *  @param file - ifstream to read values from
 *  @return vector of read values
 */
inline Vector2 getNextVector(std::ifstream& file)
{
    Vector2 v;
    file >> v[0] >> v[1];
    return v;
}

#endif // TESTHELPER_H
