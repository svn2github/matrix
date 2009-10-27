#ifndef MY_PROMOTION_TRAITS_HPP
#define MY_PROMOTION_TRAITS_HPP


/*

promotion_traits.hpp

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


#include <complex>


namespace my {

using namespace std;

// define the promotion ladder
template <typename T, typename U> struct promotion_trait { };

// promotion within floatig point types: 
// {float, double, long double, 
// std::complex<float>, std::complex<double>, std::complex<long double>}
#include "promotion_traits/promotion_fp.hpp"

// promotion within integral types {short, int, long, long long}
#include "promotion_traits/promotion_i.hpp"

// #include "promotion_integral_2fp.hpp" such that
// promotion_trait<INT, FPT>::promoted_type is FPT, where FPT is one of 
// {float, double, long double, 
// std::complex<float>, std::complex<double>, std::complex<long double>}

#ifdef INT
#pragma push_macro("INT")
#define INT_MACRO_PUSH
#undef INT
#endif

#define INT short
#include "promotion_traits/promotion_i2fp.hpp"
#undef INT

#define INT int
#include "promotion_traits/promotion_i2fp.hpp"
#undef INT

#define INT long
#include "promotion_traits/promotion_i2fp.hpp"
#undef INT

#define INT long long
#include "promotion_traits/promotion_i2fp.hpp"
#undef INT

#ifdef INT_MACRO_PUSH
#pragma pop_macro("INT")
#undef INT_MACRO_PUSH
#endif

// end of promotion ladder

} // namespace

#endif // MY_PROMOTION_TRAITS_HPP

