#include <iostream>
#include <cmath>

#include "my/vector.hpp"
#include "ode/runge_kutta.hpp"

typedef my::vector<double,2> vector;
const double PI = 3.14159265358979323846;

vector f(double t, vector r) { // dr/dt = f(t,r)
    vector ret;
    ret(0) = cos(t);
    ret(1) = -sin(t);
    return ret;
}

int main()
{
    double a[]={0,1}; // initial value
    vector v(a);
    ODE::RK4(f, v, 0., 2 * PI, 0.01);
    return 0;
}
