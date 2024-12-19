#include "functions.h"

Complex addComplex(Complex a, Complex b) {
    Complex sum;
    sum.x = a.x + b.x;
    sum.y = a.y + b.y;
    return sum;
}

Complex squareComplex(Complex a) {
    Complex squared;
    squared.x = a.x * a.x - a.y * a.y;
    squared.y = 2 * a.x * a.y;
    return squared;
}

Complex calculateQ(Complex a, Complex b, Complex c) {
    Complex sum = addComplex(a, squareComplex(b));
    sum = addComplex(sum, addComplex(b, c));
    return sum;
}