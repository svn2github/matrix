Matrix Library in C++ (bonus: RK4 ODE solver)


Introduction:

This is my implementation of a minimalist dense matrix library in C++. It originated from an incomplete matrix library in C at circa 2007, which provided functionality just enough to allocate and deallocate memory, handle input and output, and do addition and multiplication for dense matrices, so that I could write an ODE solver in matrix jargon. I decided to rewrite it in C++, for the sake of operator overloading, so that the client code would looke a bit nicer. Template techniques are employed for the same purpose. For example, type promotions are handled, so as to allow operations involving, say, a matrix of double and another matrix of complex<double> without explicit conversion. Another consideration is efficiency. Rather than dynamic polymorphism, static dispatch is done for matrix conjugation and hermetian, differentiating real and complex types (to cope with std::conj() as it does not handle the cases of real types well). 


Demo:

A fourth order Runge-Kutta ODE solver (using just the vector portion of the library) and a sample program implementing the Hodgkin-Huxley model of cardioelectrophysiology is given.


What to do next (and what not to do):

MATLAB style slicing and Copy-On-Write is under consideration.

Matrix decomositions, i.e. LU, QR, EVD, SVD, etc. are certainly desired. It's more likely I'll interface with mature numerical libraries rather than roll my own.

Advanced template techniques (like expression template) are absent and will unlikely be considered. 
