#ifndef MATRIX_IMPL_HPP
#define MATRIX_IMPL_HPP


/*

matrix_impl.hpp

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


template <typename Ts, const std::size_t M, const std::size_t N, const std::size_t X, const std::size_t Y> class matrix_slice;


template <typename Ts, const std::size_t M, const std::size_t N>
class matrix : public matrix_base<Ts, M, N, real_trait<Ts>::is_real>
{

public:

    typedef Ts scalar_type;

    static const std::size_t size1 = M;
	static const std::size_t size2 = N;

    matrix();

    // construct from a 2-D array of scalars
    matrix(const Ts(&a)[M][N]); 
    template<typename U> matrix(const U(&a)[M][N]);

    // construct from an array of column vectors
    matrix(const vector<Ts, M>(&a)[N]); 
    template<typename U> matrix(const vector<U, M>(&a)[N]);

    // construct from an array of row vectors
	matrix(const vector<Ts, N>(&a)[M], bool dummy); 
    template<typename U> matrix(const vector<U, N>(&a)[M], bool dummy);

    // construct from another matrix
    matrix(const matrix& copy); 
    template<typename U> matrix(const matrix<U, M, N>& copy); 

    // construct from matrix_slice
    template<std::size_t K, std::size_t L> matrix(const matrix_slice<Ts,K,L,M,N>& s);
    template<typename U, std::size_t K, std::size_t L> matrix(const matrix_slice<U,K,L,M,N>& s);

    ~matrix();

    // index for mutator
    Ts& operator() (const std::size_t i, const std::size_t j); 

    // index for inspector
    const Ts& operator() (const std::size_t i, const std::size_t j) const; 

    // index slicing
    template <std::size_t X, std::size_t Y> matrix_slice<Ts, M, N, X, Y> operator() (const std::size_t (&row)[X], const std::size_t (&col)[Y]);
    template <std::size_t X, std::size_t Y> const matrix_slice<Ts, M, N, X, Y> operator() (const std::size_t (&row)[X], const std::size_t (&col)[Y]) const;

    matrix& operator= (const matrix &rhs);
    template<typename U> matrix& operator= (const matrix<U, M, N>& rhs);

    // matrix = matrix_slice is not provided
    // but works by way of implicit conversion of rhs to tmp matrix and assignment of lhs from tmp matrix
    // this is inexpensive as matrix data are reference counted

	// matrix& operator= (const Ts(&a)[M][N]);
    // template<typename U> matrix& operator= (const U(&a)[M][N]);

	// matrix& operator= (const vector<Ts, M>(&a)[N]);
    // template<typename U> matrix& operator= (const vector<U, M>(&a)[N]);

    matrix& operator+= (const matrix &rhs);
    template<typename U> matrix& operator+= (const matrix<U, M, N>& rhs);

    matrix& operator-= (const matrix &rhs);
    template<typename U> matrix& operator-= (const matrix<U, M, N>& rhs);

    matrix& operator *= (const Ts &rhs);
    template<typename U> matrix& operator*= (const U& rhs);

    const matrix& operator+() const; // unary operator "+" (do nothing)
    const matrix operator-() const; // unary operator "-" (negation)

    const matrix operator+ (const matrix &other) const; // binary operator "+"
    const matrix operator- (const matrix &other) const; // binary operator "-"

    // addition with type promotion is factored out
    // subtraction with type promotion is factored out
    // matrix multiplication is not a member function

    const Ts norm() const; // Frobenius norm (for computational simplicity)
	const matrix<Ts, N, M> T() const; // transpose

    // hermitian and conjugacy are derived from matrix_base<Ts, M, N, real_trait<Ts>::is_real>
    // no virtual function table is needed.

    template <typename U, const std::size_t P, const std::size_t Q, const std::size_t X, const std::size_t Y> friend class matrix_slice;

private:

    Ts* data_; // pointer to POD
    int* count_; // reference counting

};


// constructors
// Ts is shallow-copyable (e.g. primitive data type, or class without resource management)

template <typename Ts, const std::size_t M, const std::size_t N>
matrix<Ts, M, N>::matrix()
{
    count_ = new int(1);
    data_ = new Ts[M*N];
    memset(data_, 0, sizeof(Ts) * M * N);
}


template <typename Ts, const std::size_t M, const std::size_t N>
matrix<Ts, M, N>::matrix(const Ts(&a)[M][N]) 
{
    count_ = new int(1);
    data_ = new Ts[M*N];
    memcpy(data_, a, sizeof(Ts) * M * N);
}


template <typename Ts, const std::size_t M, const std::size_t N>
template<typename U> 
matrix<Ts, M, N>::matrix(const U(&a)[M][N])
{
    count_ = new int(1);
    data_ = new Ts[M*N];
	for (std::size_t i = 0; i < M; ++i) {
		for (std::size_t j = 0; j < N; ++j) {
			data_[i * N + j] = static_cast<Ts>(a[i][j]);
		}
	}
}


template <typename Ts, const std::size_t M, const std::size_t N>
matrix<Ts, M, N>::matrix(const vector<Ts, M>(&a)[N]) // array of column vectors
{
    count_ = new int(1);
	data_ = new Ts[M*N];
	for (std::size_t i = 0; i < N; ++i) { // column
		for (std::size_t j = 0; j < M; ++j) { // row
			data_[j * N + i] = a[i](j);
		}
	}
}


template <typename Ts, const std::size_t M, const std::size_t N>
template<typename U> 
matrix<Ts, M, N>::matrix(const vector<U, M>(&a)[N]) // array of column vectors
{
    count_ = new int(1);
	data_ = new Ts[M*N];
	for (std::size_t i = 0; i < N; ++i) { // column
		for (std::size_t j = 0; j < M; ++j) { // row
			data_[j * N + i] = static_cast<Ts>(a[i](j));
		}
	}
}



template <typename Ts, const std::size_t M, const std::size_t N>
matrix<Ts, M, N>::matrix(const vector<Ts, N>(&a)[M], bool dummy) // array of row vectors
{
    count_ = new int(1);
	data_ = new Ts[M*N];
	for (std::size_t i = 0; i < M; ++i) { // row
		for (std::size_t j = 0; j < N; ++j) { // column
			data_[i * N + j] = a[i](j);
		}
	}

}


template <typename Ts, const std::size_t M, const std::size_t N>
template<typename U> 
matrix<Ts, M, N>::matrix(const vector<U, N>(&a)[M], bool dummy) // array of row vectors
{
    count_ = new int(1);
	data_ = new Ts[M*N];
	for (std::size_t i = 0; i < M; ++i) { // row
		for (std::size_t j = 0; j < N; ++j) { // column
			data_[i * N + j] = static_cast<Ts>(a[i](j));
		}
	}

}


template <typename Ts, const std::size_t M, const std::size_t N>
matrix<Ts, M, N>::matrix(const matrix<Ts, M, N>& copy) // copy constructor
: count_(copy.count_), data_(copy.data_)
{
    ++*count_;
}


template <typename Ts, const std::size_t M, const std::size_t N>
template<typename U> 
matrix<Ts, M, N>::matrix(const matrix<U, M, N>& copy) // copy constructor
{
    count_ = new int(1);
    data_ = new Ts[M*N];
	for (std::size_t i = 0; i < M; ++i) {
		for (std::size_t j = 0; j < N; ++j) {
			data_[i * N + j] = static_cast<Ts>(copy(i, j));
		}
	}    
}


template <typename Ts, const std::size_t M, const std::size_t N>
template<std::size_t K, std::size_t L>
matrix<Ts, M, N>:: matrix(const matrix_slice<Ts,K,L,M,N>& s) // construct from matrix_slice
{
    count_ = new int(1);
    data_ = new Ts[M*N];
	for (std::size_t i = 0; i < M; ++i) {
		for (std::size_t j = 0; j < N; ++j) {
			data_[i * N + j] = s(i, j);
		}
	}
}


template <typename Ts, const std::size_t M, const std::size_t N>
template<typename U, std::size_t K, std::size_t L>
matrix<Ts, M, N>:: matrix(const matrix_slice<U,K,L,M,N>& s) // construct from matrix_slice
{
    count_ = new int(1);
    data_ = new Ts[M*N];
	for (std::size_t i = 0; i < M; ++i) {
		for (std::size_t j = 0; j < N; ++j) {
			data_[i * N + j] = static_cast<Ts>(s(i, j));
		}
	}
}


// destructor
template <typename Ts, const std::size_t M, const std::size_t N>
matrix<Ts, M, N>::~matrix() 
{
    if (--*count_ == 0) {
        delete count_;
        delete[] data_;
#ifdef COUTDELETE
        std::cout << "delete[] data_" << std::endl;
#endif
    }
}


// index for mutator
template <typename Ts, const std::size_t M, const std::size_t N>
Ts& 
matrix<Ts, M, N>:: operator() (const std::size_t i, const std::size_t j) 
{

#if !defined(NOTHROW)
    if (i >= M || j >= N) { 
        throw std::exception("index out of bounds");
    }
#endif

    if (*count_ > 1) { // copy on write
        Ts* cow_data_ = new Ts[M*N];
        memcpy(cow_data_, data_, sizeof(Ts) * M * N);
        data_ = cow_data_;
        --*count_;
        count_ = new int(1);
    }
    return data_[i * N + j];
}


// index for inspector
template <typename Ts, const std::size_t M, const std::size_t N>
const Ts& 
matrix<Ts, M, N>:: operator() (const std::size_t i, const std::size_t j) const 
{

#if !defined(NOTHROW)
    if (i >= M || j >= N) { 
        throw std::exception("index out of bounds");
    }
#endif

    return data_[i * N + j];

}


template <typename Ts, const std::size_t M, const std::size_t N>
template <std::size_t X, std::size_t Y> 
matrix_slice<Ts, M, N, X, Y> 
matrix<Ts, M, N>:: operator() (const std::size_t (&row)[X], const std::size_t (&col)[Y])
{
    matrix_slice<Ts, M, N, X, Y> ret(*this, row, col);
    return ret;
}


template <typename Ts, const std::size_t M, const std::size_t N>
template <std::size_t X, std::size_t Y> 
const matrix_slice<Ts, M, N, X, Y> 
matrix<Ts, M, N>:: operator() (const std::size_t (&row)[X], const std::size_t (&col)[Y]) const
{
    matrix_slice<Ts, M, N, X, Y> ret(*this, row, col);
    return ret;
}


template <typename Ts, const std::size_t M, const std::size_t N>
matrix<Ts, M, N>& 
matrix<Ts, M, N>:: operator= (const matrix<Ts, M, N> &rhs)  // assignment operator
{
    Ts* old_ = data_; // save ptr to old data
    data_ = rhs.data_; // point to new data
    ++*rhs.count_; // update ref count for new data *before* dec ref count for old data
    if (--*count_ == 0) { // if ref count for old data drops to zero, destroys old data
        delete count_;
        delete[] old_;
    }
    count_ = rhs.count_; // point to the corresponding ref count

    return *this;
}


template <typename Ts, const std::size_t M, const std::size_t N>
template<typename U> 
matrix<Ts, M, N>& 
matrix<Ts, M, N>:: operator= (const matrix<U, M, N> &rhs) // assignment
{
	for (std::size_t i = 0; i < M; ++i) {
		for (std::size_t j = 0; j < N; ++j) {
			(*this)(i,j) = static_cast<Ts>(rhs(i, j));
		}
	}

    return *this;
}


template <typename Ts, const std::size_t M, const std::size_t N>
matrix<Ts, M, N>& 
matrix<Ts, M, N>:: operator+= (const matrix<Ts, M, N> &rhs) 
{
   	for (std::size_t i = 0; i < M; ++i) {
		for (std::size_t j = 0; j < N; ++j) {
			(*this)(i,j) += rhs(i, j);
		}
	}

    return *this;
}


template <typename Ts, const std::size_t M, const std::size_t N>
template<typename U> 
matrix<Ts, M, N>& 
matrix<Ts, M, N>:: operator+= (const matrix<U, M, N>& rhs)
{
	for (std::size_t i = 0; i < M; ++i) {
		for (std::size_t j = 0; j < N; ++j) {
			(*this)(i,j) += static_cast<Ts>(rhs(i, j));
		}
	}

    return *this;
}


template <typename Ts, const std::size_t M, const std::size_t N>
matrix<Ts, M, N>& 
matrix<Ts, M, N>:: operator-= (const matrix<Ts, M, N> &rhs)
{
   	for (std::size_t i = 0; i < M; ++i) {
		for (std::size_t j = 0; j < N; ++j) {
			(*this)(i,j) -= rhs(i, j);
		}
	}

    return *this;
}


template <typename Ts, const std::size_t M, const std::size_t N>
template<typename U> 
matrix<Ts, M, N>& 
matrix<Ts, M, N>:: operator-= (const matrix<U, M, N>& rhs)
{
	for (std::size_t i = 0; i < M; ++i) {
		for (std::size_t j = 0; j < N; ++j) {
			(*this)(i,j) -= static_cast<Ts>(rhs(i, j));
		}
	}

    return *this;
}


template <typename Ts, const std::size_t M, const std::size_t N>
matrix<Ts, M, N>& 
matrix<Ts, M, N>:: operator*= (const Ts &rhs) 
{
   	for (std::size_t i = 0; i < M; ++i) {
		for (std::size_t j = 0; j < N; ++j) {
			(*this)(i,j) *= rhs;
		}
	}

    return *this;
}


template <typename Ts, const std::size_t M, const std::size_t N>
template<typename U> 
matrix<Ts, M, N>& 
matrix<Ts, M, N>:: operator*= (const U &rhs) // with coercion
{
    (*this) *= static_cast<Ts>(rhs);
    return *this;
}


template <typename Ts, const std::size_t M, const std::size_t N>
const matrix<Ts, M, N>& 
matrix<Ts, M, N>:: operator+() const // unary "+"
{
    return (*this);
}


template <typename Ts, const std::size_t M, const std::size_t N>
const matrix<Ts, M, N> 
matrix<Ts, M, N>:: operator-() const // unary "-"
{
    matrix<Ts, M, N> ret(*this);
    return (ret *= static_cast<Ts>(-1.0));
}


template <typename Ts, const std::size_t M, const std::size_t N>
const matrix<Ts, M, N> 
matrix<Ts, M, N>:: operator+ (const matrix<Ts, M, N> &other) const 
{
    matrix<Ts, M, N> ret(*this);
    return (ret += other);
}


template <typename Ts, const std::size_t M, const std::size_t N>
const matrix<Ts, M, N> 
matrix<Ts, M, N>:: operator- (const matrix<Ts, M, N> &other) const 
{
    matrix<Ts, M, N> ret(*this);
    return (ret -= other);
}


// Frobenius norm
template <typename Ts, const std::size_t M, const std::size_t N>
const Ts
matrix<Ts, M, N>::norm() const 
{
    Ts ret(0);

    for (Ts* it = data_; it < data_ + M * N; ++it) {
        ret += (*it) * (*it);
    }

    return sqrt(ret);
}


// transpose
template <typename Ts, const std::size_t M, const std::size_t N>
const matrix<Ts, N, M>
matrix<Ts, M, N>::T() const 
{
	matrix<Ts, N, M> ret;
	for (std::size_t i = 0; i < M; ++i) {
		for (std::size_t j = 0; j < N; ++j) {
			ret(j,i) = (*this)(i,j);
		}
	}
	return ret;
}


} // namespace my


#endif // MATRIX_IMPL_HPP
