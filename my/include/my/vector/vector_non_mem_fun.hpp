#ifndef VECTOR_NON_MEM_FUN_HPP
#define VECTOR_NON_MEM_FUN_HPP


/*

vector_non_mem_fun.hpp

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


#include "my/promotion_traits.hpp"

namespace my {

template <typename Ts, const std::size_t N> class vector;

// vector + vector with type promotion, not a member function
template <typename T1, typename T2, const std::size_t N>
const typename my::vector<typename promotion_trait<T1,T2>::promoted_type, N> 
operator+ (const typename my::vector<T1, N> &op1, const typename my::vector<T2, N> &op2)
{
    typename my::vector<typename promotion_trait<T1,T2>::promoted_type, N> ret(op1);
    return (ret += op2);
}


// vector - vector with type promotion, not a member function
template <typename T1, typename T2, const std::size_t N>
const typename my::vector<typename promotion_trait<T1,T2>::promoted_type, N> 
operator- (const typename my::vector<T1, N> &op1, const typename my::vector<T2, N> &op2)
{
    typename my::vector<typename promotion_trait<T1,T2>::promoted_type, N> ret(op1);
    return (ret -= op2);
}


// scalar * vector, not a member function
template <typename T, const std::size_t N>
const typename my::vector<T, N> 
operator* (const T &op1, const typename my::vector<T, N> &op2) 
{
    typename my::vector<T, N> ret(op2);
    return (ret *= op1);
}


// scalar * vector with type promotion, not a member function
template <typename T1, typename T2, const std::size_t N>
const typename my::vector<typename promotion_trait<T1,T2>::promoted_type, N> 
operator* (const T1 &op1, const typename my::vector<T2, N> &op2) 
{
    typename my::vector<typename promotion_trait<T1,T2>::promoted_type, N> ret(op2);
    return (ret *= op1);
}


// vector * scalar, not a member function
template <typename T, const std::size_t N>
const typename my::vector<T, N> 
operator* (const typename my::vector<T, N> &op2, const T &op1) 
{
    typename my::vector<T, N> ret(op2);
    return (ret *= op1);
}


// vector * scalar with type promotion, not a member function
template <typename T1, typename T2, const std::size_t N>
const typename my::vector<typename promotion_trait<T1,T2>::promoted_type, N> 
operator* (const typename my::vector<T2, N> &op2, const T1 &op1) 
{ 
    typename my::vector<typename promotion_trait<T1,T2>::promoted_type, N> ret(op2);
    return (ret *= op1);
}


    // vector * vector (inner product), not a member function
    template <typename Ts, const std::size_t N>
    const Ts
    operator* (const typename my::vector<Ts, N> &op1, const typename my::vector<Ts, N> &op2)
    {
        Ts ret(0);
        for (size_t i = 0; i < N; ++i) {
            ret += (op1(i) * op2(i));
        }
        return ret;
    }


//////// //////// //////// //////// //////// //////// ////////
// vector * vector with type promotion, not a member function
//////// //////// //////// //////// //////// //////// ////////
template <typename T1, typename T2, const std::size_t N>
const typename my::promotion_trait<T1,T2>::promoted_type
operator* (const typename my::vector<T1, N> &op1, const typename my::vector<T2, N> &op2)
{
    typename my::promotion_trait<T1,T2>::promoted_type ret(0);
    for (size_t i = 0; i < N; ++i) {
        // static_cast<> is needed for template argument deduction
        ret += static_cast<typename my::promotion_trait<T1,T2>::promoted_type>(op1(i)) *
            static_cast<typename my::promotion_trait<T1,T2>::promoted_type>(op2(i));
    }

    return ret;
}


template <typename T, std::size_t N>
std::ostream& 
operator<<(ostream& os, const typename my::vector<T, N>& v)
{
    for(std::size_t i = 0; i < N; ++i) {
        os << v(i) << " ";
    }

    return os;
}


template <typename T, std::size_t N>
std::istream& 
operator>>(istream& is, typename my::vector<T, N>& v)
{
    for(std::size_t i = 0; i < N; ++i) {
        is >> v(i);
    }

    return is;
}


// helper function for matrix index slicing
template<typename Ts, std::size_t I, std::size_t F, std::ptrdiff_t H>
vector<Ts,(F-I)/H>
seq()
{
    vector<Ts,(F-I)/H> ret;
    for (std::size_t idx=0, val=I; idx < (F-I)/H; ++idx, val += H) ret(idx) = val;
    return ret;
}

#define my_range(from,to,step) my::seq<std::size_t, static_cast<std::size_t>(from), static_cast<std::size_t>(to), static_cast<std::size_t>(step)>()


} // namespace

#endif // VECTOR_NON_MEM_FUN_HPP
