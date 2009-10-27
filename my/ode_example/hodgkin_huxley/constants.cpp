#include "constants.hpp"

namespace hh{

const double C = 1.0;			// membrane capacitance per unit area 
const double G_Na_MAX = 120;		// maximum possible sodium conductance 
const double G_K_MAX = 36;		// maximum possible potassium conductance 
const double G_L_MAX = 0.3;		// maximum possible leakage conductance 
const double E_Na = 115;		// sodium membrane potential 
const double E_K = -12;			// potassium membrane potential 
const double E_L = 10.6;		// leakage membrane potential 
const double V_HOLD = -70;		// voltage prior to t0 
const double V_START = -55;		// voltage right after t0 
const double T0 = 0;			// starting time of experiment 
const double T_MAX = 64;		// duration of experiment 
const double STEP_SIZE = 1./1024;	// partition integral interval into STEPS sub-intervals 
const double I_P = 15;			// current applied 
const double T0_P = 10;			// starting time of pulse 
const double T1_P = 11;			// stopping time of pulse 

} // namespace hh
