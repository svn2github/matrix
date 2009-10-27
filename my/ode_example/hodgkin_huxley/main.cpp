#include <iostream>

#include "my/vector.hpp"
#include "ode/runge_kutta.hpp"
#include "hodgkin_huxley.hpp"



int main()
{
    ODE::RK4(hh::f, hh::init(), hh::T0, hh::T_MAX, hh::STEP_SIZE);
    return 0;
}


