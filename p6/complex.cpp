/*
 * file: complex.cpp
 * This is the implementation of our complex number
 * class whose interface resides in the file complex.h
 */

#include "complex.h"

#include <cmath> // for the square root function needed for norm()

complex::complex(double re, double im)
{
	//initialize the real and imaginary parts:
	real = re;
	imag = im;
}

complex::complex(const complex& z)
{
	//we need to make *this a copy of z:
	real = z.real;
	imag = z.imag;
}

ostream& operator<<(ostream& o, const complex& z)
{
	o << "(" << z.real;
	if(z.imag>=0)
		o << " + " << z.imag;
	else
		o << " - " << -z.imag;
	o << "i)";
	return o;
}

istream& operator>>(istream& i, complex& z)
{
	return (i>> z.real >> z.imag);
}

complex complex::conj()
{
	complex temp;
	temp.real = real;
	temp.imag = -imag;
	return temp;
	/* NOTE: alternatively, you could use a constructor to make a
	 * new complex number with the right real and imaginary parts,
	 * and return it straight away: */
	// return complex(real,-imag);
}

complex::complex()
{
	real = 0;
	imag = 0;
}

double complex::norm()
{
	/* TODO: write this */
	/* the norm is both x and y squared and added together*/
	double retVal = real*real + imag*imag ;

	return retVal;
}

complex operator+(const complex& w, const complex& z)
{
	complex retVal;
	retVal.real = w.real + z.real;
	retVal.imag = w.imag + z.imag;
	return retVal;
	/* again, this could also be written as: */
	// return complex(w.real+z.real,w.imag+z.imag);
}

complex operator-(const complex& w)
{
	/* TODO: write this */
	complex retVal;
	retVal.real = 0-(w.real); //Just does the negative of the real numbr
	retVal.imag = 0-(w.imag); //Just does the negative of the imag number
	/* NOTE: this is unary negation, not subtraction. */
	return retVal; 
}

complex operator-(const complex& w, const complex& z)
{
	/* TODO: write this */
	/*complex retVal;
	retVal.real = w.real - z.real;
	retVal.imag = w.imag - z.imag;
	return retVal;*/
	return w+(-z);
}

complex operator*(const complex& w, const complex& z)
{
	/* TODO: write this */
	
	complex retVal;
	retVal.real = (w.real*z.real) - (w.imag*z.imag);
	retVal.imag = (w.real*z.imag) + (w.imag*z.real);
	return retVal;
	
	//return complex(w.real*z.real, w.imag*z.imag); 
	//Note written same way I just did it to be simpler
}

complex operator/(complex& w, complex& z)
{
	/* TODO: write this */
	return complex(w.real/z.real, w.imag/z.imag);
}

complex operator^(const complex& w, int a)
{
	/* NOTE: there are much more efficient ways to do exponentiation,
	 * but it won't make much difference for our application. */
	complex retVal(1,0); //initialize it to 1
	for(int i=0; i<a; i++)
		retVal = retVal*w;
	return retVal;
}
