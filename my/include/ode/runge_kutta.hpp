#ifndef RUNGE_KUTTA_HPP
#define RUNGE_KUTTA_HPP

// runge_kutta.hpp

#include <iostream>

#include "my/vector.hpp"


namespace ODE { 
        
        template<typename Ts, size_t N >
        void RK4( my::vector<Ts, N>(*f)(Ts, my::vector<Ts, N>),  // y = f(t, x)
                  my::vector<Ts, N> r, // initial value
                  Ts ti,  // initial time
                  Ts tf,  // final time
                  Ts h ) // step size
        {

            Ts half = h / 2;
            Ts sixth = h / 6;

            my::vector<Ts, N> k1, k2, k3, k4;

            for( Ts t = ti; t < tf; ) {

                k1 = f(t, r);
                k2 = f(t + half, r + half * k1);
                k3 = f(t + half, r + half * k2);
                k4 = f(t + h, r + h * k3);

                t += h;
                r += (k1 + 2 * (k2 + k3) + k4) * sixth;

                std::cout << t << " " << r << "\n"; 

            }

        }


} // namespace ODE


#endif // RUNGE_KUTTA_HPP
