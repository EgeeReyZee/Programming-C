#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
 
typedef struct Complex {
    double x;
    double y;
} Complex;

Complex addComplex(Complex a, Complex b);
Complex squareComplex(Complex a);
Complex calculateQ(Complex a, Complex b, Complex c);

#endif