#include <iostream>
#include <complex>

#include "static_if.hpp"
#include "my/real_traits.hpp"
#include "my/vector.hpp"
#include "my/matrix.hpp"



template <typename S, typename T, typename U, size_t M, size_t N>
void foo(S(&a)[M][N], T t, U u)
{

    my::matrix<T,M,N> m( (const S(&)[M][N]) a[0][0] );
    my::matrix<U,M,N> p(m);

    my::matrix<U,N,M> n( (const S(&)[N][M]) a[0][0] );
    my::matrix<T,N,M> q(n);

    // support for assignment from array types is removed 
    // p = (const S(&)[M][N]) a[0][0];
    // q = (const S(&)[N][M]) a[0][0];

    std::cout << " p = \n" << p << std::endl;
    std::cout << " q = \n" << q << std::endl;

    std::cout << " m = \n" << m << std::endl;
    std::cout << " n = \n" << n << std::endl;

    std::cout << " m.T() = \n" << m.T() << std::endl;
    std::cout << " m.conj() = \n" << m.conj() << std::endl;
    std::cout << " m.H() = \n" << m.H() << std::endl;
    std::cout << " m.norm() = \n" << m.norm() << std::endl;

    p += m; 
    p -= m;

    q += n;
    q -= n;

    std::complex<float> cf = 1;
    std::complex<double> cg = 1;

    cf * p;
    p * cf;
    cf * q;
    q * cf;

    typename static_if<my::real_trait<T>::is_real, float, std::complex<float> >::Type f = 1;
    typename static_if<my::real_trait<T>::is_real, double, std::complex<double> >::Type g = 1;

    p *= f;
    p *= g;
    q *= f;
    q *= g;

    p *= 1;
    p *= 1L;
    p *= 1.0f;
    p *= 1.0;

    q *= 1;
    q *= 1L;
    q *= 1.0f;
    q *= 1.0;

    std::cout << " 2 m = \n" << 2 * m << std::endl;
    std::cout << " 3 m = \n" << m * 3 << std::endl;
    
    std::cout << " 4 n = \n" << 4.0 * n << std::endl;
    std::cout << " 5 n = \n" << n * 5.0 << std::endl;

    std::cout << "m * m* = \n" << m * m.H() << std::endl;
    std::cout << "m* * m = \n" << m.H() * m << std::endl;

    std::cout << "n * n* = \n" << n * n.H() << std::endl;
    std::cout << "n* * n = \n" << n.H() * n << std::endl;

    std::cout << "m * n = \n" << m * n << std::endl;
    std::cout << "n * m = \n" << n * m << std::endl;
}

template <typename Ts, size_t M>
void bar(Ts(&b)[M])
{

my::vector<Ts, M> u(b);

my::matrix<Ts,1,M> x((const Ts(&)[1][M])b[0]);
my::matrix<Ts,M,1> y((const Ts(&)[M][1])b[0]);
my::matrix<Ts,M,1> z((const my::vector<Ts,3>(&)[1])u);
my::matrix<Ts,1,M> w((const my::vector<Ts,3>(&)[1])u, 1);

std::cout << x << std::endl;
std::cout << y << std::endl;
std::cout << z << std::endl;
std::cout << w << std::endl;

std::cout << x * y << std::endl;
std::cout << my::row_vector(u) * my::col_vector(u) << std::endl;

if (M==3) { std::cout << my::cross(u) * my::col_vector(u) << std::endl; }

}

template <typename T>
void test()
{
    T a[3] = { 1, 2, 3 };
    bar(a);
}

template <typename S, typename T, typename U>
void test2()
{
    S b[3][4] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    foo(b,(T)0,(U)0);
}

int main()
{
    
    test<short>();
    test<int>();
    test<long>();
    test<long long>();
    test<float>();
    test<double>();
    test<long double>();
    test<std::complex<float> >();
    test<std::complex<double> >();
    test<std::complex<long double> >();
    

    
    test2<short,double,double>();
    test2<int,double,double>();
    test2<long,double,double>();
    test2<long long,double,double>();
    test2<float,double,double>();
    test2<double,double,double>();
    test2<long double,double,double>();
    

    test2<short,float,double>();
    test2<int,float,double>();
    test2<long,float,double>();
    test2<long long,float,double>();
    test2<float,float,double>();
    test2<double,float,double>();

    
    test2<short,std::complex<double>,std::complex<double> >();
    test2<int,std::complex<double>,std::complex<double> >();
    test2<long,std::complex<double>,std::complex<double> >();
    test2<long long,std::complex<double>,std::complex<double> >();
    test2<float,std::complex<double>,std::complex<double> >();
    test2<double,std::complex<double>,std::complex<double> >();
    

    test2<short,std::complex<float>,std::complex<double> >();
    test2<int,std::complex<float>,std::complex<double> >();
    test2<long,std::complex<float>,std::complex<double> >();
    test2<long long,std::complex<float>,std::complex<double> >();
    test2<float,std::complex<float>,std::complex<double> >();
    test2<double,std::complex<float>,std::complex<double> >();

    return 0;
}
