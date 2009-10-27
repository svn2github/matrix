#ifndef VECTOR_UTILITY_HPP
#define VECTOR_UTILITY_HPP


/*

vector_utility.hpp

Copyright (C) 2009, Ji Han

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/


namespace my {

template <typename Ts, const std::size_t N> class vector;
template <typename Ts, const std::size_t M, const size_t N> class matrix;


    // [rather than implementing matrix * vector]
    // convert a k-dimensional vector to a kx1 matrix (column vector)
    template <typename Ts, size_t M>
    matrix<Ts, M, 1>
    col_vector(const vector<Ts, M>& v)
    {
        return matrix<Ts, M, 1>( (const vector<Ts, M>(&)[1]) v );
    }


    // [rather than implementing vector * matrix]
    // convert a k-dimensional vector to a 1xk matrix (row vector)
    template <typename Ts, size_t N>
    matrix<Ts, 1, N>
    row_vector(const vector<Ts, N>& v)
    {
        return matrix<Ts, 1, N>( (const vector<Ts, N>(&)[1]) v, 1);
    }


    // [rather than implementing cross product]
    // v "cross" w is represented as cross(v) * col_vector(w)
    template <typename Ts>
    matrix<Ts, 3, 3>
    cross(const vector<Ts, 3>& v)
    {
        matrix<Ts, 3, 3> ret;

        /* ret(0,0) = 0; */ ret(0,1) = -v(2);   ret(0,2) = v(1);
        ret(1,0) = v(2);    /* ret(1,1) = 0; */ ret(1,2) = -v(0);
        ret(2,0) = -v(1);   ret(2,1) = v(0);    /* ret(2,2) = 0; */

        return ret;
    }


} //namespace

#endif // VECTOR_UTILITY_HPP
