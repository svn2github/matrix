#include <iostream>
#include <complex>

#define COUTDELETE 1

#include "static_if.hpp"
#include "my/real_traits.hpp"
#include "my/vector.hpp"
#include "my/matrix.hpp"



template <typename T, size_t M, size_t N>
void test(T(&a)[M][N])
{

    my::matrix<T,M,N> m( (const T(&)[M][N]) a[0][0] );
    my::matrix<T,M,N> p(m);
    std::size_t s[] = {0,2}, t[] = {1,3};

    p = m;
    p(s,t) *= 100; // index slicing, like MATLAB p([0,2],[1,3])

    my::matrix<T,N,M> n( (const T(&)[N][M]) a[0][0] );
    my::matrix<T,N,M> q(n);

    q = n;
    q(s,t) *= -1; // index slicing

    std::cout << " p = \n" << p << std::endl;
    std::cout << " q = \n" << q << std::endl;

    std::cout << " m = \n" << m << std::endl;
    std::cout << " n = \n" << n << std::endl;


}




template <typename T>
void test2()
{
    T b[6][4] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 };
    test(b);
}

int main()
{
    test2<double>();
    test2<std::complex<double> >();

    return 0;
}
