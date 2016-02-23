#include "Weight.h"

Weight::Weight()
{

}

Weight &Weight::operator=(const double &rvalue)
{
    this->v = rvalue;
    return *this;
}

Weight &Weight::operator+=(const double &right)
{
    this->v += right;
    return *this;
}

double Weight::operator*(const double &right)
{
    return this->v * right;
}

bool Weight::operator<=(const double &right)
{
    return this->v <= right;
}

bool Weight::operator<(const double &right)
{
    return this->v < right;
}
