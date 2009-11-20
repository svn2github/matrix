#include <iostream>
#include <cstdlib>
#include <complex>

#include "static_if.hpp"
#include "countof.hpp"
#include "my/real_traits.hpp"
#include "my/vector.hpp"
#include "my/matrix.hpp"



template <typename T, typename U, size_t M, size_t N>
void foo(T(&a)[M][N], U dummy)
{
    std::size_t s[] = {0,2}, t[] = {1,3};

    my::matrix<T,M,N> m( (const T(&)[M][N]) a[0][0] );
    my::matrix<U,M,N> p( m );

    my::matrix_slice<T,M,N,countof(s),countof(s)> ms1(m, s, s);
    my::matrix_slice<T,M,N,countof(s),countof(t)> ms2(m, s, t);
    my::matrix_slice<T,M,N,countof(t),countof(s)> ms3(m, t, s);
    my::matrix_slice<T,M,N,countof(t),countof(t)> ms4(m, t, t);

    my::matrix_slice<U,M,N,countof(s),countof(s)> ms(m, s, s);

    std::cout << " m = \n" << m << std::endl;
    std::cout << " ms1 = \n" << ms1 << std::endl;
    std::cout << " ms2 = \n" << ms2 << std::endl;
    std::cout << " ms3 = \n" << ms3 << std::endl;
    std::cout << " ms4 = \n" << ms4 << std::endl;

    +(+ms1); +(-ms2); -(+ms3); -(-ms4);

    ms1 + ms2; ms3 - ms4;
    ms2 * ms3; ms3 * ms2;

    ms1 + ms; ms1 - ms; 
    ms + ms1; ms - ms1;
    ms1 * ms; ms * ms1;

    ms1 *= 1;
    ms1 *= 1L;
    ms1 *= 1.0f;
    ms1 *= 1.0;

    std::cout << " 2 ms1 = \n" << 2 * ms1 << std::endl;
    std::cout << " 3 ms2 = \n" << ms2 * 3 << std::endl;
    
    std::cout << " 4 ms3 = \n" << 4.0 * ms3 << std::endl;
    std::cout << " 5 ms4 = \n" << ms4 * 5.0 << std::endl;

    std::cout << "ms2 * ms3 = \n" << ms2 * ms3 << std::endl;
    std::cout << "ms3 * ms2 = \n" << ms3 * ms2 << std::endl;

    ms1 = -ms1;
    ms2(0,0) = 30; ms2(1,1) = -30;
    ms4 = (+ms4).T() + (-ms4).T();
    std::cout << " m = \n" << m << std::endl;
    std::cout << " ms1 = \n" << ms1 << std::endl;
    std::cout << " ms2 = \n" << ms2 << std::endl;
    std::cout << " ms3 = \n" << ms3 << std::endl;
    std::cout << " ms4 = \n" << ms4 << std::endl;

}


template <typename T, typename U>
void test2()
{
    T b[][6] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 };
    foo(b,(U)0);
}

int main()
{
    
    test2<short,double>();
    test2<int,double>();
    test2<long,double>();
    test2<long long,double>();
    test2<float,double>();
    test2<double,double>();
    test2<long double,double>();
    

    test2<short,float>();
    test2<int,float>();
    test2<long,float>();
    test2<long long,float>();
    test2<float,float>();
    test2<double,float>();

    
    test2<short,std::complex<double> >();
    test2<int,std::complex<double> >();
    test2<long,std::complex<double> >();
    test2<long long,std::complex<double> >();
    test2<float,std::complex<double> >();
    test2<double,std::complex<double> >();
    

    test2<short,std::complex<float> >();
    test2<int,std::complex<float> >();
    test2<long,std::complex<float> >();
    test2<long long,std::complex<float> >();
    test2<float,std::complex<float> >();
    test2<double,std::complex<float> >();

    return 0;
}
