#ifndef MATRIX_BASE_HPP
#define MATRIX_BASE_HPP

/*

matrix_base.hpp

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

    template <typename Ts, const std::size_t M, const size_t N> class matrix;

    // base class solely for inheritance
    template <typename Ts, const std::size_t M, const size_t N, bool isreal>
    class matrix_base
    { 
    protected:
        ~matrix_base() {} // dtor intended non-virtual.

        const matrix<Ts, N, M> H() const; // hermitian (conjugate transpose)
        const matrix<Ts, M, N> conj() const; // conjugate
        const Ts norm() const; // Frobenius norm
    };

    // specialization for real matrices
    template <typename Ts, const std::size_t M, const std::size_t N>
    class matrix_base<Ts, M, N, true>
    {
    public:
        const matrix<Ts, N, M> H() const; // hermitian (conjugate transpose)
        const matrix<Ts, M, N> conj() const; // conjugate
        const Ts norm() const; // Frobenius norm
    };


    // specialization for complex matrices
    template <typename Ts, const std::size_t M, const std::size_t N>
    class matrix_base<Ts, M, N, false>
    {
    public:
        const matrix<Ts, N, M> H() const; // hermitian (conjugate transpose)
        const matrix<Ts, M, N> conj() const; // conjugate
        const typename Ts::value_type norm() const; // Frobenius norm
    };

    //////// //////// //////// //////// 
    // hermitian (conjugate transpose)
    //////// //////// //////// //////// 

    //////// //////// //////// //////// 
    // specialization for complex types
    //////// //////// //////// //////// 
    template <typename Ts, const std::size_t M, const std::size_t N>
    const matrix<Ts, N, M>
    matrix_base<Ts, M, N, false>::H() const 
    {
        matrix<Ts, N, M> ret;
        for (std::size_t i = 0; i < M; ++i) {
            for (std::size_t j = 0; j < N; ++j) {
                ret(j,i) = std::conj((*static_cast<const matrix<Ts,M,N>*>(this))(i,j));
            }
        }
        return ret;
    }


    //////// //////// //////// //////// 
    // specialization for real types
    //////// //////// //////// //////// 
    template <typename Ts, const std::size_t M, const std::size_t N>
    const matrix<Ts, N, M>
    matrix_base<Ts, M, N, true>::H() const 
    {
        return static_cast<const matrix<Ts,M,N>*>(this)->T();
    }


    //////// ////////
    // conjugate
    //////// ////////

    //////// //////// //////// //////// 
    // specialization for complex types
    //////// //////// //////// //////// 
    template <typename Ts, const std::size_t M, const std::size_t N>
    const matrix<Ts, M, N>
    matrix_base<Ts, M, N, false>::conj() const 
    {
        matrix<Ts, M, N> ret;
        for (std::size_t i = 0; i < M; ++i) {
            for (std::size_t j = 0; j < N; ++j) {
                ret(i,j) = std::conj((*static_cast<const matrix<Ts,M,N>*>(this))(i,j));
            }
        }
        return ret;
    }

    //////// //////// //////// //////// 
    // specialization for real types
    //////// //////// //////// //////// 
    template <typename Ts, const std::size_t M, const std::size_t N>
    const matrix<Ts, M, N>
    matrix_base<Ts, M, N, true>::conj() const 
    {
        return *static_cast<const matrix<Ts,M,N>*>(this);
    }   

    //////// ////////
    // Frobenius norm
    //////// ////////

    //////// //////// //////// //////// 
    // specialization for complex types
    //////// //////// //////// //////// 
    template <typename Ts, const std::size_t M, const std::size_t N>
    const typename Ts::value_type
    matrix_base<Ts, M, N, false>::norm() const 
    {
        typename Ts::value_type ret(0);
        for (std::size_t i = 0; i < M; ++i) {
            for (std::size_t j = 0; j < N; ++j) {
                ret += (*static_cast<const matrix<Ts,M,N>*>(this))(i,j).real() *
                    (*static_cast<const matrix<Ts,M,N>*>(this))(i,j).real() +
                    (*static_cast<const matrix<Ts,M,N>*>(this))(i,j).imag() *
                    (*static_cast<const matrix<Ts,M,N>*>(this))(i,j).imag();
            }
        }
        return sqrt(ret);
    }

    //////// //////// //////// //////// 
    // specialization for real types
    //////// //////// //////// //////// 
    template <typename Ts, const std::size_t M, const std::size_t N>
    const Ts
    matrix_base<Ts, M, N, true>::norm() const 
    {
        Ts ret(0);
        for (std::size_t i = 0; i < M; ++i) {
            for (std::size_t j = 0; j < N; ++j) {
                ret += (*static_cast<const matrix<Ts,M,N>*>(this))(i,j) *
                    (*static_cast<const matrix<Ts,M,N>*>(this))(i,j);
            }
        }
        return sqrt(ret);
    }

} // namespace my

#endif // MATRIX_BASE_HPP
