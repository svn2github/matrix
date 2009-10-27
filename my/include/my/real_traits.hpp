#ifndef MY_REAL_TRAITS_HPP
#define MY_REAL_TRAITS_HPP


/*

real_traits.hpp 

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

// real_trait<Type>::is_real != false 
// if Type is one of the following types:
// (including most common integral and floating point types)
// 
// char, signed char, unsigned char, wchar_t
// bool, short, unsigned short, 
// int, unsigned int, long, unsigned long, long long, unsigned long long
// float, double, long double

// Note: 
// for the sake of simplicity and minimum dependency, 
// enum types are *not* included.
// (not really needed for me as I never make vectors/matrices out of enums.
// if you really miss this feature, pull boost/type_traits/is_enum in.)


namespace my {


template <typename T> 
struct real_trait 
{ 
    enum {is_real = false};
};

template<> struct real_trait<bool> 
{ 
    enum {is_real = true};
};

template<> struct real_trait<char> 
{ 
    enum {is_real = true};
};

template<> struct real_trait<signed char> 
{ 
    enum {is_real = true};
};

template<> struct real_trait<unsigned char> 
{ 
    enum {is_real = true};
};

template<> struct real_trait<wchar_t> 
{ 
    enum {is_real = true};
};

template<> struct real_trait<short> 
{ 
    enum {is_real = true};
};

template<> struct real_trait<unsigned short> 
{ 
    enum {is_real = true};
};

template<> struct real_trait<int> 
{ 
    enum {is_real = true};
};

template<> struct real_trait<unsigned int> 
{ 
    enum {is_real = true};
};

template<> struct real_trait<long> 
{ 
    enum {is_real = true};
};

template<> struct real_trait<unsigned long> 
{ 
    enum {is_real = true};
};

template<> struct real_trait<long long> 
{ 
    enum {is_real = true};
};

template<> struct real_trait<unsigned long long> 
{ 
    enum {is_real = true};
};

template<> struct real_trait<float> 
{ 
    enum {is_real = true};
};

template<> struct real_trait<double> 
{ 
    enum {is_real = true};
};

template<> struct real_trait<long double> 
{ 
    enum {is_real = true};
};

} // namespace


#endif // MY_REAL_TRAITS_HPP

