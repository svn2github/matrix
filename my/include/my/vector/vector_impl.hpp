#ifndef VECTOR_IMPL_HPP
#define VECTOR_IMPL_HPP


/*

vector_impl.hpp

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


template <typename Ts, const std::size_t N>
class vector
{

public:

    typedef Ts scalar_type;
    typedef const Ts(&ref_array_type)[N];

    static const std::size_t dim = N;

    vector();
    vector(const Ts(&a)[N]);
    template<typename U> vector(const U(&a)[N]);
    vector(const vector& rhs);
    template<typename U> vector(const vector<U, N>& rhs);
    ~vector();

    const Ts norm() const;

    Ts& operator() (const std::size_t index);
    const Ts& operator() (const std::size_t index) const;

    operator ref_array_type () const; // user-defined conversion

    vector& operator= (const vector &rhs);
    template<typename U> vector& operator= (const vector<U, N> &rhs);

    vector& operator+= (const vector &rhs);
    template<typename U> vector& operator+= (const vector<U, N> &rhs);

    vector& operator-= (const vector &rhs);
    template<typename U> vector& operator-= (const vector<U, N> &rhs);

    vector& operator *= (const Ts &rhs);
    template<typename U> vector& operator*= (const U &rhs);

    const vector& operator+() const; // unary operator "+" (do nothing)
    const vector operator-() const; // unary operator "-" (negation)

    const vector operator+ (const vector &other) const; // binary operator "+"
    const vector operator- (const vector &other) const; // binary operator "-"


private:

    Ts* data_;

};


template <typename Ts, const std::size_t N>
vector<Ts, N>::vector() 
{
    data_ = new Ts[N];
    memset(data_, 0, sizeof(Ts) * N);
}


template <typename Ts, const std::size_t N>
vector<Ts, N>::vector(const Ts(&a)[N]) 
{
    data_ = new Ts[N];
    memcpy(data_, a, sizeof(Ts) * N);
}


template <typename Ts, const std::size_t N>
template <typename U>
vector<Ts, N>::vector(const U(&a)[N]) 
{
    data_ = new Ts[N];
    for (size_t i = 0; i < N; ++i) {
        data_[i] = static_cast<Ts>(a[i]);
    }
}


template <typename Ts, const std::size_t N>
vector<Ts, N>::vector(const vector<Ts, N>& rhs) 
{
    data_ = new Ts[N];
    memcpy(data_, rhs.data_, sizeof(Ts) * N);
}


template <typename Ts, const std::size_t N>
template <typename U>
vector<Ts, N>::vector(const vector<U, N>& rhs) 
{ 
    data_ = new Ts[N];
    for (size_t i = 0; i < N; ++i) {
        data_[i] = static_cast<Ts>(rhs(i));
    }
}


template <typename Ts, const std::size_t N>
vector<Ts, N>::~vector() 
{
    delete [] data_;
}


template <typename Ts, const std::size_t N>
const Ts
vector<Ts, N>::norm() const 
{

    Ts ret(0);

    for (Ts* it = data_; it < data_ + N; ++it) {
        ret += (*it) * (*it);
    }

    return sqrt(ret);
}


template <typename Ts, const std::size_t N>
inline
Ts& 
vector<Ts, N>:: operator() (const std::size_t index) // index for mutator
{

#if !defined(NOTHROW)
    if (index >= N) { 
        throw std::exception("index out of bounds");
    }
#endif

    return data_[index];

}


template <typename Ts, const std::size_t N>
inline
const Ts& 
vector<Ts, N>:: operator() (const std::size_t index) const // index for inspector
{

#if !defined(NOTHROW)
    if (index >= N) { 
        throw std::exception("index out of bounds");
    }
#endif

    return data_[index];

}


// user-defined conversion (for matrix index slicing)
// since function cannot return array in C++,
// a vector<std::size_t,N> returned by seq gets converted to std::size_t(&)[N],
// and passed to matrix_slice constructor.
// when matrix_slice is constructed, data_ stays in scope.
template <typename Ts, const std::size_t N>
vector<Ts, N>:: operator typename vector<Ts, N>::ref_array_type () const
{
    return reinterpret_cast<const Ts(&)[N]>(*data_);
}


template <typename Ts, const std::size_t N>
inline
vector<Ts, N>& 
vector<Ts, N>:: operator= (const vector<Ts, N> &rhs) 
{

    if (this != &rhs) { // check for self-assignment
        memcpy( data_, rhs.data_, sizeof(Ts) * N );
    }

    return *this;
}


template <typename Ts, const std::size_t N>
template <typename U>
inline
vector<Ts, N>& 
vector<Ts, N>:: operator= (const vector<U, N> &rhs) 
{
    for (size_t i = 0; i < N; ++i) {
        data_[i] = static_cast<Ts>(rhs(i));
    }

    return *this;
}


template <typename Ts, const std::size_t N>
inline
vector<Ts, N>& 
vector<Ts, N>:: operator+= (const vector<Ts, N> &rhs) 
{
    Ts* const end = data_ + N;
    Ts* p = data_;
    const Ts* q = rhs.data_;
    while (p < end) { *p++ += *q++; }

    return *this;
}

template <typename Ts, const std::size_t N>
template <typename U>
inline
vector<Ts, N>& 
vector<Ts, N>:: operator+= (const vector<U, N> &rhs) 
{
/*
    // there's no partially specialized friend class

    Ts* const end = data_ + N;
    Ts* p = data_;
    const U* q = rhs.data_;
    while (p < end) { *p++ += static_cast<Ts>(*q++); }

    return *this;
*/

    for (size_t i = 0; i < N; ++i) {
        data_[i] += static_cast<Ts>(rhs(i));
    }

    return *this;
}

template <typename Ts, const std::size_t N>
inline
vector<Ts, N>& 
vector<Ts, N>:: operator-= (const vector<Ts, N> &rhs) 
{

    Ts* const end = data_ + N;
    Ts* p = data_;
    const Ts* q = rhs.data_;
    while (p < end) { *p++ -= *q++; }

    return *this;
}


template <typename Ts, const std::size_t N>
template <typename U>
inline
vector<Ts, N>& 
vector<Ts, N>:: operator-= (const vector<U, N> &rhs) 
{
    for (size_t i = 0; i < N; ++i) {
        data_[i] -= static_cast<Ts>(rhs(i));
    }

    return *this;
}


template <typename Ts, const std::size_t N>
inline
vector<Ts, N>& 
vector<Ts, N>:: operator*= (const Ts &rhs) 
{

    Ts* const end = data_ + N;
    Ts* p = data_;
    while (p < end) { *p++ *= rhs; }

    return *this;
}


template <typename Ts, const std::size_t N>
template <typename U>
inline
vector<Ts, N>& 
vector<Ts, N>:: operator*= (const U &rhs) 
{

    (*this) *= static_cast<Ts>(rhs);
/*
    for (size_t i = 0; i < N; ++i) {
        data_[i] *= static_cast<Ts>(rhs);
    }
*/
    return *this;
}


template <typename Ts, const std::size_t N>
inline
const vector<Ts, N>& 
vector<Ts, N>:: operator+() const  // unary "+"
{
    return (*this);
}


template <typename Ts, const std::size_t N>
inline
const vector<Ts, N> 
vector<Ts, N>:: operator-() const // unary "-"
{ 
    vector<Ts, N> ret(*this);
    // return (ret *= -1.0);
    return (ret *= static_cast<Ts>(-1.0));
}


// vector + vector
template <typename Ts, const std::size_t N>
inline
const vector<Ts, N> 
vector<Ts, N>:: operator+ (const vector<Ts, N> &other) const 
{
    vector<Ts, N> ret(*this);
    return (ret += other);
}




// vector - vector
template <typename Ts, const std::size_t N>
inline
const vector<Ts, N> 
vector<Ts, N>:: operator- (const vector<Ts, N> &other) const 
{
    vector<Ts, N> ret(*this);
    return (ret -= other);
}



} // namespace

#endif // VECTOR_IMPL_HPP
