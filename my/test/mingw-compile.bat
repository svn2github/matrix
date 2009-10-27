:: type 'mingw-compile <progname>' to compile
:: where <progname> is one of my_matrix.cpp/my_vector.cpp/ode_rk4.cpp
:: make sure MinGW can be reached via PATH

@g++.exe -DNOTHROW -I%~dp0\..\include %* 2>&1
