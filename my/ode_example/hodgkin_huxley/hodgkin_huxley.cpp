#include "hodgkin_huxley.hpp"

namespace hh{

double alpham(double v)	{ return 1.0  * ( ( v - 25) / 10 ) / (1 - exp( -( v - 25) / 10) ); }

double alphan(double v)	{ return 0.1  * ( ( v - 10) / 10 ) / (1 - exp( -( v - 10) / 10) ); }

double alphah(double v)	{ return 0.07 * exp( -v / 20 ); }

double betam(double v)	{ return 4.0  * exp( -v / 18 ); }

double betan(double v)	{ return 0.125* exp( -v / 80 ); }

double betah(double v)	{ return 1 / ( 1 + exp( -( v - 30) / 10 ) ); }

// double izero(double t)	{ return 0; }
double izero(double t)	{ return ( (T0_P < t) && (t < T1_P) ) ? I_P : 0; }


my::vector<double,4> 
init()
{
	my::vector<double,4> ret;

	ret(0) = alpham(V_HOLD) / (alpham(V_HOLD) + betam(V_HOLD) );
	ret(1) = alpham(V_HOLD) / (alphan(V_HOLD) + betan(V_HOLD) );
	ret(2) = alpham(V_HOLD) / (alphah(V_HOLD) + betah(V_HOLD) );
	ret(3) = V_START;

	return ret;
}


my::vector<double,4> 
f(double t, my::vector<double,4> r)
{
	my::vector<double, 4> ret;
	double g_Na, g_K, g_l, g_tot, e;

	g_Na = G_Na_MAX * pow(r(0), 3) * r(2);
	g_K  = G_K_MAX  * pow(r(1), 4);
	g_l  = G_L_MAX;
	g_tot = g_Na + g_K + g_l;
	e = ( g_Na * E_Na + g_K * E_K + g_l * E_L ) / g_tot;

	ret(0) = alpham(r(3)) * (1 - r(0)) - betam(r(3)) * r(0);
	ret(1) = alphan(r(3)) * (1 - r(1)) - betan(r(3)) * r(1);
	ret(2) = alphah(r(3)) * (1 - r(2)) - betah(r(3)) * r(2);
	ret(3) = ( izero(t) - g_tot * (r(3) - e) ) / C;

	return ret;
}


} // namespace hh
