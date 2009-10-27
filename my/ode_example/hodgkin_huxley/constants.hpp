#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace hh{

extern const double C;		// membrane capacitance per unit area 
extern const double G_Na_MAX;	// maximum possible sodium conductance 
extern const double G_K_MAX;	// maximum possible potassium conductance 
extern const double G_L_MAX;	// maximum possible leakage conductance 
extern const double E_Na;	// sodium membrane potential 
extern const double E_K;	// potassium membrane potential 
extern const double E_L;	// leakage membrane potential 
extern const double V_HOLD;	// voltage prior to t0 
extern const double V_START;	// voltage right after t0 
extern const double T0;		// starting time of experiment 
extern const double T_MAX;	// duration of experiment 
extern const double STEP_SIZE;	// partition integral interval into STEPS sub-intervals 
extern const double I_P;	// current applied 
extern const double T0_P;	// starting time of pulse 
extern const double T1_P;	// stopping time of pulse 

} // namespace hh

#endif // CONSTANTS_HPP 
