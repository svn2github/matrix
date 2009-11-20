#ifndef MY_MATRIX_HPP
#define MY_MATRIX_HPP


/*

matrix.hpp

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


#include <cstdlib>
#include <cstring>
#include <cmath>
#include <complex>
#include <iostream>

#if !defined(NOTHROW)
#    include <exception>
#endif // !defined(NOTHROW)

#include "my/real_traits.hpp"
#include "my/promotion_traits.hpp"
#include "my/vector.hpp"
#include "my/matrix/matrix_base.hpp"
#include "my/matrix/matrix_impl.hpp"
#include "my/matrix/matrix_non_mem_fun.hpp"
#include "my/matrix/matrix_slice.hpp"
#include "my/matrix/matrix_slice_interop.hpp"

#endif // MY_MATRIX_HPP
