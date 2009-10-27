:: type 'msvc-compile <progname>' to compile
:: where <progname> is one of my_matrix.cpp/my_vector.cpp/ode_rk4.cpp
:: note that MSVC requires several environment variables be set

@cl.exe %* /I%~dp0\..\include /EHsc 2>&1
