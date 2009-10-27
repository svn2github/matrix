#ifndef HODGKIN_HUXLEY_HPP
#define HODGKIN_HUXLEY_HPP

#include "constants.hpp"
#include "my/vector.hpp"

namespace hh{

double alpham(double v);
double alphan(double v);
double alphah(double v);
double betam(double v);
double betan(double v);
double betah(double v);
double izero(double t);

my::vector<double,4> init();
my::vector<double,4> f(double t, my::vector<double,4> r);

} // namespace hh

#endif // HODGKIN_HUXLEY_HPP

