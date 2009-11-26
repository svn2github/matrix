#include <iostream>
#include <cstdlib>
#include <complex>

#include "static_if.hpp"
#include "countof.hpp"
#include "my/real_traits.hpp"
#include "my/vector.hpp"
#include "my/matrix.hpp"



template <typename T, size_t M, size_t N>
void foo(T(&a)[M][N])
{
    std::size_t s[] = {1,2,3,0}, t[] = {0,1,2};
    std::size_t u[] = {0,1,2,3}, v[] = {0,1,2};

    my::matrix<T,M,N> m( (const T(&)[M][N]) a[0][0] );

    // explicit usage of matrix_slice objects 
    // is for testing purpose only
    // use 'matrix-name(row-indices, col-indices)' for client code
    my::matrix_slice<T,M,N,countof(s),countof(t)> ms(m, s, t);
    my::matrix_slice<T,M,N,countof(u),countof(v)> ms1(m, u, my_range(0,3,1));

    std::cout << my_range(0,10,1) << std::endl;

    std::cout << " m = \n" << m << std::endl;
    std::cout << " ms = \n" << ms << std::endl;
    std::cout << " ms1 = \n" << ms1 << std::endl;

    ms = m;

    std::cout << " m = \n" << m << std::endl;
    std::cout << " ms = \n" << ms << std::endl;

    ms += m;

    std::cout << " m = \n" << m << std::endl;
    std::cout << " ms = \n" << ms << std::endl;

    ms -= m;

    std::cout << " m = \n" << m << std::endl;
    std::cout << " ms = \n" << ms << std::endl;

    m = ms;

    std::cout << " m = \n" << m << std::endl;
    std::cout << " ms = \n" << ms << std::endl;

    m += ms;

    std::cout << " m = \n" << m << std::endl;
    std::cout << " ms = \n" << ms << std::endl;

    m -= ms;

    std::cout << " m = \n" << m << std::endl;
    std::cout << " ms = \n" << ms << std::endl;

    ms = ms1;

    std::cout << " m = \n" << m << std::endl;
    std::cout << " ms = \n" << ms << std::endl;
    std::cout << " ms1 = \n" << ms1 << std::endl;

    ms += ms1;

    std::cout << " m = \n" << m << std::endl;
    std::cout << " ms = \n" << ms << std::endl;
    std::cout << " ms1 = \n" << ms1 << std::endl;

    ms -= ms1;

    std::cout << " m = \n" << m << std::endl;
    std::cout << " ms = \n" << ms << std::endl;
    std::cout << " ms1 = \n" << ms1 << std::endl;

}


template <typename T, typename U>
void test2()
{
    T b[][3] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    foo(b);
}

int main()
{
    test2<double,double>();
    return 0;
}
