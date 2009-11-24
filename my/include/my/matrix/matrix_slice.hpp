#ifndef MATRIX_SLICE_HPP
#define MATRIX_SLICE_HPP


/*

matrix_slice.hpp

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

template <typename Ts, const std::size_t M, const std::size_t N, const std::size_t X, const std::size_t Y>
class matrix_slice
{
public:

    typedef Ts scalar_type;

    static const std::size_t size1 = M;
	static const std::size_t size2 = N;
    static const std::size_t sizer = X;
    static const std::size_t sizec = Y;

public:
    matrix_slice(matrix<Ts,M,N>&mat, const std::size_t (&row)[X], const std::size_t (&col)[Y]);
    ~matrix_slice();


    Ts& operator() (const std::size_t i, const std::size_t j); // index for mutator
    const Ts& operator() (const std::size_t i, const std::size_t j) const; // index for inspector

    matrix_slice& operator= (const matrix<Ts,X,Y> &rhs); // assignment: change matrix<Ts,M,N> mat *in place*
    template<typename U> matrix_slice& operator= (const matrix<U,X,Y>& rhs); // with coercion.

    matrix_slice& operator+= (const matrix<Ts,X,Y> &rhs);
    template<typename U> matrix_slice& operator+= (const matrix<U,X,Y>& rhs); // with coercion.

    matrix_slice& operator-= (const matrix<Ts,X,Y> &rhs);
    template<typename U> matrix_slice& operator-= (const matrix<U,X,Y>& rhs); // with coercion.

    matrix_slice& operator *= (const Ts &rhs);
    template<typename U> matrix_slice& operator*= (const U& rhs); // with coercion.

    const matrix<Ts, X, Y> operator+() const; // unary operator "+"
    const matrix<Ts, X, Y> operator-() const; // unary operator "-"


private:

    matrix<Ts,M,N>& mat_;
    size_t row_index_[M];
    size_t col_index_[N];

};


// constructor
template <typename Ts, const std::size_t M, const std::size_t N, const std::size_t X, const std::size_t Y>
matrix_slice<Ts,M,N,X,Y>:: matrix_slice (matrix<Ts,M,N>&mat, const std::size_t (&row)[X], const std::size_t (&col)[Y])
: mat_(mat)
{
#if defined(DEBUG)
    for (std::size_t i = 0; i < M; ++i) row_index_[i] = ((std::size_t)-1);
    for (std::size_t i = 0; i < N; ++i) col_index_[i] = ((std::size_t)-1);
#endif
    for (std::size_t i = 0; i < M && i < X; ++i) {
        row_index_[i] = row[i];
    }

    for (std::size_t j = 0; j < N && j < Y; ++j) {
        col_index_[j] = col[j];
    }
}



// destructor
template <typename Ts, const std::size_t M, const std::size_t N, const std::size_t X, const std::size_t Y>
matrix_slice<Ts,M,N,X,Y>::~matrix_slice() 
{
    // do nothing
}


// index for mutator
template <typename Ts, const std::size_t M, const std::size_t N, const std::size_t X, const std::size_t Y>
Ts& 
matrix_slice<Ts,M,N,X,Y>:: operator() (const std::size_t i, const std::size_t j) 
{
    return mat_(row_index_[i], col_index_[j]);
}


// index for inspector
template <typename Ts, const std::size_t M, const std::size_t N, const std::size_t X, const std::size_t Y>
const Ts& 
matrix_slice<Ts,M,N,X,Y>:: operator() (const std::size_t i, const std::size_t j) const 
{
    return mat_(row_index_[i], col_index_[j]);
}


template <typename Ts, const std::size_t M, const std::size_t N, const std::size_t X, const std::size_t Y>
matrix_slice<Ts,M,N,X,Y>&
matrix_slice<Ts,M,N,X,Y>:: operator= (const matrix<Ts, X, Y> &rhs)  // assignment operator
{
	for (std::size_t i = 0; i < X; ++i) {
		for (std::size_t j = 0; j < Y; ++j) {
			(*this)(i,j) = rhs(i, j); // data_[row_offset_[i] + col_offset_[j]] = rhs(i, j);
		}
	}

    return *this;
}


template <typename Ts, const std::size_t M, const std::size_t N, const std::size_t X, const std::size_t Y>
template<typename U> 
matrix_slice<Ts,M,N,X,Y>&
matrix_slice<Ts,M,N,X,Y>:: operator= (const matrix<U, X, Y> &rhs) // assignment, with coercion
{
	for (std::size_t i = 0; i < X; ++i) {
		for (std::size_t j = 0; j < Y; ++j) {
			(*this)(i,j) = static_cast<Ts>(rhs(i, j)); // data_[row_offset_[i] + col_offset_[j]] = static_cast<Ts>(rhs(i, j));
		}
	}

    return *this;
}



template <typename Ts, const std::size_t M, const std::size_t N, const std::size_t X, const std::size_t Y>
matrix_slice<Ts,M,N,X,Y>&
matrix_slice<Ts,M,N,X,Y>:: operator+= (const matrix<Ts, X, Y> &rhs)
{
	for (std::size_t i = 0; i < X; ++i) {
		for (std::size_t j = 0; j < Y; ++j) {
			(*this)(i,j) += rhs(i, j); // data_[row_offset_[i] + col_offset_[j]] += rhs(i, j);
		}
	}

    return *this;
}


template <typename Ts, const std::size_t M, const std::size_t N, const std::size_t X, const std::size_t Y>
template<typename U> 
matrix_slice<Ts,M,N,X,Y>&
matrix_slice<Ts,M,N,X,Y>:: operator+= (const matrix<U, X, Y> &rhs) // with coercion.
{
	for (std::size_t i = 0; i < X; ++i) {
		for (std::size_t j = 0; j < Y; ++j) {
			(*this)(i,j) += static_cast<Ts>(rhs(i, j)); // data_[row_offset_[i] + col_offset_[j]] += static_cast<Ts>(rhs(i, j));
		}
	}

    return *this;
}


template <typename Ts, const std::size_t M, const std::size_t N, const std::size_t X, const std::size_t Y>
matrix_slice<Ts,M,N,X,Y>&
matrix_slice<Ts,M,N,X,Y>:: operator-= (const matrix<Ts, X, Y> &rhs)
{
	for (std::size_t i = 0; i < X; ++i) {
		for (std::size_t j = 0; j < Y; ++j) {
			(*this)(i,j) -= rhs(i, j); // data_[row_offset_[i] + col_offset_[j]] -= rhs(i, j);
		}
	}

    return *this;
}


template <typename Ts, const std::size_t M, const std::size_t N, const std::size_t X, const std::size_t Y>
template<typename U> 
matrix_slice<Ts,M,N,X,Y>&
matrix_slice<Ts,M,N,X,Y>:: operator-= (const matrix<U, X, Y> &rhs) // with coercion.
{
	for (std::size_t i = 0; i < X; ++i) {
		for (std::size_t j = 0; j < Y; ++j) {
			(*this)(i,j) -= static_cast<Ts>(rhs(i, j)); // data_[row_offset_[i] + col_offset_[j]] -= static_cast<Ts>(rhs(i, j));
		}
	}

    return *this;
}


template <typename Ts, const std::size_t M, const std::size_t N, const std::size_t X, const std::size_t Y>
matrix_slice<Ts,M,N,X,Y>&
matrix_slice<Ts,M,N,X,Y>:: operator*= (const Ts &rhs)
{
	for (std::size_t i = 0; i < X; ++i) {
		for (std::size_t j = 0; j < Y; ++j) {
			(*this)(i,j) *= rhs; // data_[row_offset_[i] + col_offset_[j]] *= rhs;
		}
	}

    return *this;
}


template <typename Ts, const std::size_t M, const std::size_t N, const std::size_t X, const std::size_t Y>
template<typename U> 
matrix_slice<Ts,M,N,X,Y>&
matrix_slice<Ts,M,N,X,Y>:: operator*= (const U &rhs) // with coercion.
{
    (*this) *= static_cast<Ts>(rhs);
    return *this;
}


template <typename Ts, const std::size_t M, const std::size_t N, const std::size_t X, const std::size_t Y>
const matrix<Ts, X, Y>
matrix_slice<Ts,M,N,X,Y>:: operator+() const // unary "+"
{
    matrix<Ts, X, Y> ret;

    for (std::size_t i = 0; i < X; ++i) {
		for (std::size_t j = 0; j < Y; ++j) {
			ret(i,j) = (*this)(i,j);
		}
	}

    return ret;
}


template <typename Ts, const std::size_t M, const std::size_t N, const std::size_t X, const std::size_t Y>
const matrix<Ts, X, Y>
matrix_slice<Ts,M,N,X,Y>:: operator-() const // unary "-"
{
    matrix<Ts, X, Y> ret;

	for (std::size_t i = 0; i < X; ++i) {
		for (std::size_t j = 0; j < Y; ++j) {
			ret(i,j) = (*this)(i,j) * static_cast<Ts>(-1.0);
		}
	}

    return ret;
}



} // namespace my


#endif // MATRIX_SLICE_HPP
