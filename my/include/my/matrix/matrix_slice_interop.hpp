#ifndef MATRIX_SLICE_INTEROP_HPP
#define MATRIX_SLICE_INTEROP_HPP


/*

matrix_slice_interop.hpp

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

template <typename Ts, const std::size_t M, const std::size_t N, const std::size_t X, const std::size_t Y> class matrix_slice;


//////// //////// ////////
// non-member functions
//////// //////// ////////


//////// ////////
// addition
//////// ////////

// matrix slice + matrix slice
template <typename T, const std::size_t M, const std::size_t N, const std::size_t P, const std::size_t Q, const std::size_t X, const std::size_t Y>
const matrix<T, X, Y> 
operator+ (const matrix_slice<T,M,N,X,Y> &A, const matrix_slice<T,P,Q,X,Y> &B)
{
    matrix<T, X, Y> ret;

    for (std::size_t i = 0; i < X; ++i) {
		for (std::size_t j = 0; j < Y; ++j) {
			ret(i,j) = A(i,j) + B(i,j);
		}
	}

    return ret;
}


// matrix + matrix slice
template <typename T, const std::size_t P, const std::size_t Q, const std::size_t X, const std::size_t Y>
const matrix<T, X, Y> 
operator+ (const matrix<T,X,Y> &A, const matrix_slice<T,P,Q,X,Y> &B)
{
    matrix<T, X, Y> ret;

    for (std::size_t i = 0; i < X; ++i) {
		for (std::size_t j = 0; j < Y; ++j) {
			ret(i,j) = A(i,j) + B(i,j);
		}
	}

    return ret;
}


// matrix slice + matrix
template <typename T, const std::size_t M, const std::size_t N, const std::size_t X, const std::size_t Y>
const matrix<T, X, Y> 
operator+ (const matrix_slice<T,M,N,X,Y> &A, const matrix<T,X,Y> &B)
{
    matrix<T, X, Y> ret;

    for (std::size_t i = 0; i < X; ++i) {
		for (std::size_t j = 0; j < Y; ++j) {
			ret(i,j) = A(i,j) + B(i,j);
		}
	}

    return ret;
}


// addition with type promotion: matrix slice + matrix slice
template <typename T1, typename T2, const std::size_t M, const std::size_t N, const std::size_t P, const std::size_t Q, const std::size_t X, const std::size_t Y>
const matrix<typename promotion_trait<T1,T2>::promoted_type, X, Y> 
operator+ (const matrix_slice<T1,M,N,X,Y> &A, const matrix_slice<T2,P,Q,X,Y> &B)
{
    matrix<typename promotion_trait<T1,T2>::promoted_type, X, Y> ret;

    for (std::size_t i = 0; i < X; ++i) {
		for (std::size_t j = 0; j < Y; ++j) {
			ret(i,j) = static_cast<typename promotion_trait<T1,T2>::promoted_type>(A(i, j)) + 
                static_cast<typename promotion_trait<T1,T2>::promoted_type>(B(i, j));
		}
	}

    return ret;
}


// addition with type promotion: matrix + matrix slice
template <typename T1, typename T2, const std::size_t P, const std::size_t Q, const std::size_t X, const std::size_t Y>
const matrix<typename promotion_trait<T1,T2>::promoted_type, X, Y> 
operator+ (const matrix<T1,X,Y> &A, const matrix_slice<T2,P,Q,X,Y> &B)
{
    matrix<typename promotion_trait<T1,T2>::promoted_type, X, Y> ret;

    for (std::size_t i = 0; i < X; ++i) {
		for (std::size_t j = 0; j < Y; ++j) {
			ret(i,j) = static_cast<typename promotion_trait<T1,T2>::promoted_type>(A(i, j)) + 
                static_cast<typename promotion_trait<T1,T2>::promoted_type>(B(i, j));
		}
	}

    return ret;
}


// addition with type promotion: matrix slice + matrix
template <typename T1, typename T2, const std::size_t M, const std::size_t N, const std::size_t X, const std::size_t Y>
const matrix<typename promotion_trait<T1,T2>::promoted_type, X, Y> 
operator+ (const matrix_slice<T1,M,N,X,Y> &A, const matrix<T2,X,Y> &B)
{
    matrix<typename promotion_trait<T1,T2>::promoted_type, X, Y> ret;

    for (std::size_t i = 0; i < X; ++i) {
		for (std::size_t j = 0; j < Y; ++j) {
			ret(i,j) = static_cast<typename promotion_trait<T1,T2>::promoted_type>(A(i, j)) + 
                static_cast<typename promotion_trait<T1,T2>::promoted_type>(B(i, j));
		}
	}

    return ret;
}


//////// ////////
// subtraction
//////// ////////

// subtraction: matrix slice - matrix slice
template <typename T, const std::size_t M, const std::size_t N, const std::size_t P, const std::size_t Q, const std::size_t X, const std::size_t Y>
const matrix<T, X, Y> 
operator- (const matrix_slice<T,M,N,X,Y> &A, const matrix_slice<T,P,Q,X,Y> &B)
{
    matrix<T, X, Y> ret;

    for (std::size_t i = 0; i < X; ++i) {
		for (std::size_t j = 0; j < Y; ++j) {
			ret(i,j) = A(i,j) - B(i,j);
		}
	}

    return ret;
}


// matrix - matrix slice
template <typename T, const std::size_t P, const std::size_t Q, const std::size_t X, const std::size_t Y>
const matrix<T, X, Y> 
operator- (const matrix<T,X,Y> &A, const matrix_slice<T,P,Q,X,Y> &B)
{
    matrix<T, X, Y> ret;

    for (std::size_t i = 0; i < X; ++i) {
		for (std::size_t j = 0; j < Y; ++j) {
			ret(i,j) = A(i,j) - B(i,j);
		}
	}

    return ret;
}


// matrix slice - matrix
template <typename T, const std::size_t M, const std::size_t N, const std::size_t X, const std::size_t Y>
const matrix<T, X, Y> 
operator- (const matrix_slice<T,M,N,X,Y> &A, const matrix<T,X,Y> &B)
{
    matrix<T, X, Y> ret;

    for (std::size_t i = 0; i < X; ++i) {
		for (std::size_t j = 0; j < Y; ++j) {
			ret(i,j) = A(i,j) - B(i,j);
		}
	}

    return ret;
}

// subtraction with type promotion: matrix slice - matrix slice
template <typename T1, typename T2, const std::size_t M, const std::size_t N, const std::size_t P, const std::size_t Q, const std::size_t X, const std::size_t Y>
const matrix<typename promotion_trait<T1,T2>::promoted_type, X, Y> 
operator- (const matrix_slice<T1,M,N,X,Y> &A, const matrix_slice<T2,P,Q,X,Y> &B)
{
    matrix<typename promotion_trait<T1,T2>::promoted_type, X, Y> ret;

    for (std::size_t i = 0; i < X; ++i) {
		for (std::size_t j = 0; j < Y; ++j) {
			ret(i,j) = static_cast<typename promotion_trait<T1,T2>::promoted_type>(A(i, j)) - 
                static_cast<typename promotion_trait<T1,T2>::promoted_type>(B(i, j));
		}
	}

    return ret;
}


// subtraction with type promotion: matrix - matrix slice
template <typename T1, typename T2, const std::size_t P, const std::size_t Q, const std::size_t X, const std::size_t Y>
const matrix<typename promotion_trait<T1,T2>::promoted_type, X, Y> 
operator- (const matrix<T1,X,Y> &A, const matrix_slice<T2,P,Q,X,Y> &B)
{
    matrix<typename promotion_trait<T1,T2>::promoted_type, X, Y> ret;

    for (std::size_t i = 0; i < X; ++i) {
		for (std::size_t j = 0; j < Y; ++j) {
			ret(i,j) = static_cast<typename promotion_trait<T1,T2>::promoted_type>(A(i, j)) - 
                static_cast<typename promotion_trait<T1,T2>::promoted_type>(B(i, j));
		}
	}

    return ret;
}


// subtraction with type promotion: matrix slice - matrix
template <typename T1, typename T2, const std::size_t M, const std::size_t N, const std::size_t X, const std::size_t Y>
const matrix<typename promotion_trait<T1,T2>::promoted_type, X, Y> 
operator- (const matrix_slice<T1,M,N,X,Y> &A, const matrix<T2,X,Y> &B)
{
    matrix<typename promotion_trait<T1,T2>::promoted_type, X, Y> ret;

    for (std::size_t i = 0; i < X; ++i) {
		for (std::size_t j = 0; j < Y; ++j) {
			ret(i,j) = static_cast<typename promotion_trait<T1,T2>::promoted_type>(A(i, j)) - 
                static_cast<typename promotion_trait<T1,T2>::promoted_type>(B(i, j));
		}
	}

    return ret;
}


//////// ////////
// multiplication
//////// ////////

// matrix_slice * matrix_slice
template <typename T, const std::size_t M, const std::size_t N, const std::size_t P, const std::size_t Q, const std::size_t X, const std::size_t Y, const std::size_t W>
const matrix<T, X, W> 
operator* (const matrix_slice<T,M,N,X,Y> &A, const matrix_slice<T,P,Q,Y,W> &B)
{
    matrix<T, X, W> ret;

    for (std::size_t i = 0; i < X; ++i) {
   		for (std::size_t j = 0; j < W; ++j) {
		    ret(i, j) = 0;
		    for (std::size_t k = 0; k < Y; ++k) {
   				ret(i, j) += A(i, k) * B(k, j);
		    }
	    }
    }

    return ret;
}



// matrix * matrix slice
template <typename T, const std::size_t P, const std::size_t Q, const std::size_t X, const std::size_t Y, const std::size_t W>
const matrix<T, X, W> 
operator* (const matrix<T,X,Y> &A, const matrix_slice<T,P,Q,Y,W> &B)
{
    matrix<T, X, W> ret;

    for (std::size_t i = 0; i < X; ++i) {
   		for (std::size_t j = 0; j < W; ++j) {
		    ret(i, j) = 0;
		    for (std::size_t k = 0; k < Y; ++k) {
   				ret(i, j) += A(i, k) * B(k, j);
		    }
	    }
    }

    return ret;
}


// matrix slice * matrix
template <typename T, const std::size_t M, const std::size_t N, const std::size_t X, const std::size_t Y, const std::size_t W>
const matrix<T, X, W> 
operator* (const matrix_slice<T,M,N,X,Y> &A, const matrix<T,Y,W> &B)
{
    matrix<T, X, W> ret;

    for (std::size_t i = 0; i < X; ++i) {
   		for (std::size_t j = 0; j < W; ++j) {
		    ret(i, j) = 0;
		    for (std::size_t k = 0; k < Y; ++k) {
   				ret(i, j) += A(i, k) * B(k, j);
		    }
	    }
    }

    return ret;
}

// matrix_slice * matrix_slice with type promotion
template <typename T1, typename T2, const std::size_t M, const std::size_t N, const std::size_t P, const std::size_t Q, const std::size_t X, const std::size_t Y, const std::size_t W>
const matrix<typename promotion_trait<T1,T2>::promoted_type, X, W> 
operator* (const matrix_slice<T1,M,N,X,Y> &A, const matrix_slice<T2,P,Q,Y,W> &B)
{
    matrix<typename promotion_trait<T1,T2>::promoted_type, X, W> ret;

    for (std::size_t i = 0; i < X; ++i) {
   		for (std::size_t j = 0; j < W; ++j) {
		    ret(i, j) = 0;
		    for (std::size_t k = 0; k < Y; ++k) {
   				ret(i, j) += static_cast<typename promotion_trait<T1,T2>::promoted_type>(A(i, k)) * 
                    static_cast<typename promotion_trait<T1,T2>::promoted_type>(B(k, j));
		    }
	    }
    }

    return ret;
}


// matrix * matrix slice with type promotion
template <typename T1, typename T2, const std::size_t P, const std::size_t Q, const std::size_t X, const std::size_t Y, const std::size_t W>
const matrix<typename promotion_trait<T1,T2>::promoted_type, X, W> 
operator* (const matrix<T1,X,Y> &A, const matrix_slice<T2,P,Q,Y,W> &B)
{
    matrix<typename promotion_trait<T1,T2>::promoted_type, X, W> ret;

    for (std::size_t i = 0; i < X; ++i) {
   		for (std::size_t j = 0; j < W; ++j) {
		    ret(i, j) = 0;
		    for (std::size_t k = 0; k < Y; ++k) {
   				ret(i, j) += static_cast<typename promotion_trait<T1,T2>::promoted_type>(A(i, k)) * 
                    static_cast<typename promotion_trait<T1,T2>::promoted_type>(B(k, j));
		    }
	    }
    }

    return ret;
}


// matrix slice * matrix with type promotion
template <typename T1, typename T2, const std::size_t M, const std::size_t N, const std::size_t X, const std::size_t Y, const std::size_t W>
const matrix<typename promotion_trait<T1,T2>::promoted_type, X, W> 
operator* (const matrix_slice<T1,M,N,X,Y> &A, const matrix<T2,Y,W> &B)
{
    matrix<typename promotion_trait<T1,T2>::promoted_type, X, W> ret;

    for (std::size_t i = 0; i < X; ++i) {
   		for (std::size_t j = 0; j < W; ++j) {
		    ret(i, j) = 0;
		    for (std::size_t k = 0; k < Y; ++k) {
   				ret(i, j) += static_cast<typename promotion_trait<T1,T2>::promoted_type>(A(i, k)) * 
                    static_cast<typename promotion_trait<T1,T2>::promoted_type>(B(k, j));
		    }
	    }
    }

    return ret;
}


//////// ////////
// scalar mult.
//////// ////////

// scalar * matrix slice
template <typename Ts, const std::size_t M, const std::size_t N, const std::size_t X, const std::size_t Y>
const matrix<Ts, X, Y> 
operator* (const Ts &op1, const matrix_slice<Ts,M,N,X,Y> &op2) 
{
    matrix<Ts, X, Y> ret;

    for (std::size_t i = 0; i < X; ++i) {
		for (std::size_t j = 0; j < Y; ++j) {
			ret(i,j) = op1 * op2(i,j);
		}
	}

    return ret;
}


// matrix slice * scalar
template <typename Ts, const std::size_t M, const std::size_t N, const std::size_t X, const std::size_t Y>
const matrix<Ts, X, Y> 
operator* (const matrix_slice<Ts,M,N,X,Y> &op2, const Ts &op1) 
{
    matrix<Ts, X, Y> ret;

    for (std::size_t i = 0; i < X; ++i) {
		for (std::size_t j = 0; j < Y; ++j) {
			ret(i,j) = op1 * op2(i,j);
		}
	}

    return ret;
}


// scalar * matrix slice with type promotion
template <typename T1, typename T2, const std::size_t M, const std::size_t N, const std::size_t X, const std::size_t Y>
const matrix<typename promotion_trait<T1,T2>::promoted_type, X, Y> 
operator* (const T1 &op1, const matrix_slice<T2,M,N,X,Y> &op2) 
{
    matrix<typename promotion_trait<T1,T2>::promoted_type, X, Y> ret;

    for (std::size_t i = 0; i < X; ++i) {
		for (std::size_t j = 0; j < Y; ++j) {
			ret(i,j) = static_cast<typename promotion_trait<T1,T2>::promoted_type>(op1) * 
                static_cast<typename promotion_trait<T1,T2>::promoted_type>(op2(i,j));
		}
	}

    return ret;
}


// matrix slice * scalar with type promotion
template <typename T1, typename T2, const std::size_t M, const std::size_t N, const std::size_t X, const std::size_t Y>
const matrix<typename promotion_trait<T1,T2>::promoted_type, X, Y> 
operator* (const matrix_slice<T2,M,N,X,Y> &op2, const T1 &op1) 
{
    matrix<typename promotion_trait<T1,T2>::promoted_type, X, Y> ret;

    for (std::size_t i = 0; i < X; ++i) {
		for (std::size_t j = 0; j < Y; ++j) {
			ret(i,j) = static_cast<typename promotion_trait<T1,T2>::promoted_type>(op1) * 
                static_cast<typename promotion_trait<T1,T2>::promoted_type>(op2(i,j));
		}
	}

    return ret;
}


//////// ////////
// IO
//////// ////////


template <typename Ts, const std::size_t M, const std::size_t N, const std::size_t X, const std::size_t Y>
std::ostream& 
operator<<(std::ostream& os, const matrix_slice<Ts,M,N,X,Y>& m)
{
    for(std::size_t i = 0; i < X; ++i) {
        for(std::size_t j = 0; j < Y; ++j) {
            os << m(i,j) << " ";
	    }
	    os << "\n";
    }

    return os;
}


template <typename Ts, const std::size_t M, const std::size_t N, const std::size_t X, const std::size_t Y>
std::istream&
operator>>(std::istream& is, matrix_slice<Ts,M,N,X,Y>& m)
{
    for(std::size_t i = 0; i < X; ++i) {
        for(std::size_t j = 0; j < Y; ++j) {
            is >> m(i,j);
        }
    }

    return is;
}


} // namespace my


#endif // MATRIX_SLICE_INTEROP_HPP
