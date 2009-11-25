#ifndef MATRIX_NON_MEM_FUN_HPP
#define MATRIX_NON_MEM_FUN_HPP


/*

matrix_non_mem_fun.hpp

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


    // addition with type promotion, not a member function
    template <typename T1, typename T2, const std::size_t M, const std::size_t N>
    const matrix<typename promotion_trait<T1,T2>::promoted_type, M, N> 
    operator+ (const matrix<T1, M, N> &A, const matrix<T2, M, N> &B) 
    {
        matrix<typename promotion_trait<T1,T2>::promoted_type, M, N> ret(A);
        ret += B;
        return ret;
    }


    // subtraction with type promotion, not a member function
    template <typename T1, typename T2, const std::size_t M, const std::size_t N>
    const matrix<typename promotion_trait<T1,T2>::promoted_type, M, N> 
    operator- (const matrix<T1, M, N> &A, const matrix<T2, M, N> &B) 
    {
        matrix<typename promotion_trait<T1,T2>::promoted_type, M, N> ret(A);
        ret -= B;
        return ret;
    }


    // matrix * matrix, not a member function
    template <typename Ts, const std::size_t M, const std::size_t N, const std::size_t P>
    const matrix<Ts, M, P> 
    operator* (const matrix<Ts, M, N> &A, const matrix<Ts, N, P> &B) 
    {
        matrix<Ts, M, P> ret;

        for (std::size_t i = 0; i < M; ++i) {
            for (std::size_t j = 0; j < P; ++j) {
                ret(i, j) = 0;
                for (std::size_t k = 0; k < N; ++k) {
                    ret(i, j) += A(i, k) * B(k, j);
                }
            }
        }

        return ret;
    }


    // matrix * matrix with type promotion, not a member function
    template <typename T1, typename T2, const std::size_t M, const std::size_t N, const std::size_t P>
    const matrix<typename promotion_trait<T1,T2>::promoted_type, M, P> 
    operator* (const matrix<T1, M, N> &A, const matrix<T2, N, P> &B) 
    {
        matrix<typename promotion_trait<T1,T2>::promoted_type, M, P> ret;
    
        for (std::size_t i = 0; i < M; ++i) {
            for (std::size_t j = 0; j < P; ++j) {
                ret(i, j) = 0;
                for (std::size_t k = 0; k < N; ++k) {
                    ret(i, j) += static_cast<typename promotion_trait<T1,T2>::promoted_type>(A(i, k))
                        * static_cast<typename promotion_trait<T1,T2>::promoted_type>(B(k, j));
                }
            }
        }

        return ret;
    }


    // scalar * matrix, not a member function
    template <typename Ts, const std::size_t M, const std::size_t N>
    const matrix<Ts, M, N> 
    operator* (const Ts &op1, const matrix<Ts, M, N> &op2) 
    {
        matrix<Ts, M, N> ret(op2);
        return (ret *= op1);
    }


    // matrix * scalar, not a member function
    template <typename Ts, const std::size_t M, const std::size_t N>
    const matrix<Ts, M, N> 
    operator* (const matrix<Ts, M, N> &op2, const Ts &op1) 
    {
        matrix<Ts, M, N> ret(op2);
        return (ret *= op1);
    }


    // scalar * matrix with type promotion, not a member function
    template <typename T1, typename T2, const std::size_t M, const std::size_t N>
    const matrix<typename promotion_trait<T1,T2>::promoted_type, M, N> 
    operator* (const T1 &op1, const matrix<T2, M, N> &op2) 
    {
        matrix<typename promotion_trait<T1,T2>::promoted_type, M, N> ret(op2);
        return (ret *= static_cast<typename promotion_trait<T1,T2>::promoted_type>(op1));
    }


    // matrix * scalar with type promotion, not a member function
    template <typename T1, typename T2, const std::size_t M, const std::size_t N>
    const matrix<typename promotion_trait<T1,T2>::promoted_type, M, N> 
    operator* (const matrix<T2, M, N> &op2, const T1 &op1) 
    {
        matrix<typename promotion_trait<T1,T2>::promoted_type, M, N> ret(op2);
        return (ret *= static_cast<typename promotion_trait<T1,T2>::promoted_type>(op1));
    }


    // construct a diagonal matrix from a vector
    template <typename Ts, size_t M>
    matrix<Ts, M, M>
    diag(const vector<Ts, M>& v)
    {
        matrix<Ts, M, M> ret;

        for (size_t i = 0; i < M; ++i) {
            ret(i,i) = v(i);
        }

        return ret;
    }


    /*
    // return an MxN zero matrix
    template <typename Ts, size_t M, size_t N>
    matrix<Ts, M, N>
    zeros()
    {
        matrix<Ts, M, N> ret;
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j <N; ++j) {
                ret(i,j) = 0;
            }
        }
        return ret;
    }
    */


    // reset a matrix to the zero matrix
    template <typename Ts, size_t M, size_t N>
    const matrix<Ts, M, N>&
    zeros(matrix<Ts, M, N>& m)
    {
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j <N; ++j) {
                m(i,j) = 0;
            }
        }

        return m;
    }


    // return an MxN identity matrix
    template <typename Ts, size_t M, size_t N>
    matrix<Ts, M, N>
    eye() {
        matrix<Ts, M, N> ret;
        Ts t = M < N ? M : N;
        for (size_t i = 0; i < t; ++i) {
            ret(i,i) = 1;
        }

        return ret;
    }


    // return an MxM identity matrix
    template <typename Ts, size_t M>
    matrix<Ts, M, M>
    eye() {
        matrix<Ts, M, M> ret;
        for (size_t i = 0; i < M; ++i) {
            ret(i,i) = 1;
        }

        return ret;
    }


    // reset a matrix to the identity matrix
    template <typename Ts, size_t M, size_t N>
    const matrix<Ts, M, N>&
    eye(matrix<Ts, M, N>& m)
    {
        for (size_t i = 0; i < M; ++i) {
            for (size_t j = 0; j <N; ++j) {
                (i==j) ? (m(i,j)=1) : (m(i,j)=0);
            }
        }
        return m;
    }


    // output (e.g. std::cout << matrix)
    template <typename Ts, std::size_t M, std::size_t N>
    std::ostream& 
    operator<<(std::ostream& os, const matrix<Ts, M, N>& m)
    {
        for(std::size_t i = 0; i < M; ++i) {
            for(std::size_t j = 0; j < N; ++j) {
            os << m(i,j) << " ";
            }
            os << "\n";
        }

        return os;
    }


    // input (e.g. std::cin >> matrix)
    template <typename Ts, std::size_t M, std::size_t N>
    std::istream&
    operator>>(std::istream& is, matrix<Ts, M, N>& m)
    {
        for(std::size_t i = 0; i < M; ++i) {
            for(std::size_t j = 0; j < N; ++j) {
                is >> m(i,j);
            }
        }

        return is;
    }


} // namespace

#endif // MATRIX_NON_MEM_FUN_HPP
