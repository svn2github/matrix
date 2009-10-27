#ifndef PROMOTION_I_HPP
#define PROMOTION_I_HPP


/*

promotion_i.hpp

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


template<> struct promotion_trait<short, int> 
{ 
    typedef int promoted_type;
};

template<> struct promotion_trait<int, short> 
{ 
    typedef int promoted_type;
};

template<> struct promotion_trait<short, long> 
{ 
    typedef long promoted_type;
};

template<> struct promotion_trait<long, short> 
{ 
    typedef long promoted_type;
};

template<> struct promotion_trait<short, long long> 
{ 
    typedef long long promoted_type;
};

template<> struct promotion_trait<long long, short> 
{ 
    typedef long long promoted_type;
};

template<> struct promotion_trait<int, long> 
{ 
    typedef long promoted_type;
};

template<> struct promotion_trait<long, int> 
{ 
    typedef long promoted_type;
};

template<> struct promotion_trait<int, long long> 
{ 
    typedef long long promoted_type;
};

template<> struct promotion_trait<long long, int> 
{ 
    typedef long long promoted_type;
};

template<> struct promotion_trait<long, long long> 
{ 
    typedef long long promoted_type;
};

template<> struct promotion_trait<long long, long> 
{ 
    typedef long long promoted_type;
};

#endif
