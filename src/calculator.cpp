#include "calculator.h"

int Calculator::Add(double a, double b)
{
    return static_cast<int>(a + b + 0.5);
}

int Calculator::Sub(double a, double b)
{
    return Add(a, -b);
}

