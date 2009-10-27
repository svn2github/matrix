#ifndef PROMOTION_FP_HPP
#define PROMOTION_FP_HPP


/*

promotion_fp.hpp

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


template<> struct promotion_trait<float, double> 
{ 
    typedef double promoted_type;
};

template<> struct promotion_trait<double, float> 
{ 
    typedef double promoted_type;
};

template<> struct promotion_trait<float, long double> 
{ 
    typedef long double promoted_type;
};

template<> struct promotion_trait<long double, float> 
{ 
    typedef long double promoted_type;
};

template<> struct promotion_trait<double, long double> 
{ 
    typedef long double promoted_type;
};

template<> struct promotion_trait<long double, double> 
{ 
    typedef long double promoted_type;
};

//////// //////// //////// ////////

template<> struct promotion_trait<float, std::complex<float> > 
{ 
    typedef std::complex<float> promoted_type;
};

template<> struct promotion_trait<std::complex<float>, float> 
{ 
    typedef std::complex<float> promoted_type;
};

template<> struct promotion_trait<float, std::complex<double> > 
{ 
    typedef std::complex<double> promoted_type;
};

template<> struct promotion_trait<std::complex<double>, float> 
{ 
    typedef std::complex<double> promoted_type;
};

template<> struct promotion_trait<float, std::complex<long double> > 
{ 
    typedef std::complex<long double> promoted_type;
};

template<> struct promotion_trait<std::complex<long double>, float> 
{ 
    typedef std::complex<long double> promoted_type;
};


//////// //////// //////// ////////

template<> struct promotion_trait<double, std::complex<float> > 
{ 
    typedef std::complex<double> promoted_type;
};

template<> struct promotion_trait<std::complex<float>, double> 
{ 
    typedef std::complex<double> promoted_type;
};

template<> struct promotion_trait<double, std::complex<double> > 
{ 
    typedef std::complex<double> promoted_type;
};

template<> struct promotion_trait<std::complex<double>, double> 
{ 
    typedef std::complex<double> promoted_type;
};

template<> struct promotion_trait<double, std::complex<long double> > 
{ 
    typedef std::complex<long double> promoted_type;
};

template<> struct promotion_trait<std::complex<long double>, double> 
{ 
    typedef std::complex<long double> promoted_type;
};

//////// //////// //////// ////////

template<> struct promotion_trait<long double, std::complex<float> > 
{ 
    typedef std::complex<long double> promoted_type;
};

template<> struct promotion_trait<std::complex<float>, long double> 
{ 
    typedef std::complex<long double> promoted_type;
};

template<> struct promotion_trait<long double, std::complex<double> > 
{ 
    typedef std::complex<long double> promoted_type;
};

template<> struct promotion_trait<std::complex<double>, long double> 
{ 
    typedef std::complex<long double> promoted_type;
};

template<> struct promotion_trait<long double, std::complex<long double> > 
{ 
    typedef std::complex<long double> promoted_type;
};

template<> struct promotion_trait<std::complex<long double>, long double> 
{ 
    typedef std::complex<long double> promoted_type;
};

//////// //////// //////// ////////

template<> struct promotion_trait<std::complex<float>, std::complex<double> > 
{ 
    typedef std::complex<double> promoted_type;
};

template<> struct promotion_trait<std::complex<double>, std::complex<float> > 
{ 
    typedef std::complex<double> promoted_type;
};

template<> struct promotion_trait<std::complex<float>, std::complex<long double> > 
{ 
    typedef std::complex<long double> promoted_type;
};

template<> struct promotion_trait<std::complex<long double>, std::complex<float> > 
{ 
    typedef std::complex<long double> promoted_type;
};

template<> struct promotion_trait<std::complex<double>, std::complex<long double> > 
{ 
    typedef std::complex<long double> promoted_type;
};

template<> struct promotion_trait<std::complex<long double>, std::complex<double> > 
{ 
    typedef std::complex<long double> promoted_type;
};

#endif
