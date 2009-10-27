#include <iostream>
#include <complex>

#include "static_if.hpp"
#include "my/real_traits.hpp"
#include "my/vector.hpp"

using namespace my;

template <typename T>
void test()
{


T a[][3] = {1,0,0,
            0,1,0,
            0,0,1,
            1,1,1 };


vector<T,3> v[] = { a[0], a[1], a[2], a[3] };

v[0] *= 3.14159;
v[1] += v[0];
v[2] -= v[0];

std::complex<float> cf = 1;
std::complex<double> cg = 1;

cf * v[3];
v[3] * cf;

cg * v[3];
v[3] * cg;


typename static_if<real_trait<T>::is_real, float, std::complex<float> >::Type f = 1;
typename static_if<real_trait<T>::is_real, double, std::complex<double> >::Type g = 1;

v[3] *= f;
v[3] *= g;

std::cout << 2 * v[3] << "\n"
          << v[3] * 3 << "\n"
          << 4.0f * v[3] << "\n"
          << v[3] * 5.0f << "\n"
          << 6.0 * v[3] << "\n"
          << v[3] * 7.0 << std::endl;

std::cout << -(+v[0]) << "\n"
          << +(-v[0]) << "\n"
          << v[1] + v[2] << "\n"
          << v[1] - v[2] << "\n"
          << v[3] * v[3] << std::endl;

}

template <typename T, typename U, size_t N>
void test()
{
    int a[N];
    for (size_t i = 0; i<N; ++i) {
        a[i] = i;
    }

    vector<T,N> v(a);
    vector<U,N> w(a);

    std::cout << "(" << 2.0f * v + w << ")\n(" << 3.0 * v - w << ")\n" ;
    std::cout << "(" << w + (-v) << ")\n(" << w - (+v) << ")\n";
    std::cout << v * w << std::endl;
    std::cout << w * v << std::endl;
    std::cout << std::endl;
}

int main()
{
    
    
    test<float>();
    test<double>();
    test<long double>();

    test<std::complex<float> >();
    test<std::complex<double> >();
    test<std::complex<long double> >();


    test<float,double,3>();
    test<float,long double,3>();
    test<double,long double,3>();

    test<std::complex<float>, std::complex<double>,3>();
    test<std::complex<float>, std::complex<long double>,3>();
    test<std::complex<double>, std::complex<long double>,3>();

    test<float,std::complex<float>,3>();
    test<float,std::complex<double>,3>(); 
    test<float,std::complex<long double>,3>(); 

    test<double,std::complex<float>,3>(); 
    test<double,std::complex<double>,3>();
    test<double,std::complex<long double>,3>();

    test<long double,std::complex<float>,3>(); 
    test<long double,std::complex<double>,3>();
    test<long double,std::complex<long double>,3>();

    return 0;
}

