#ifndef WEIGHT_H
#define WEIGHT_H

class Weight
{
public:
    Weight();

    double v;
    double vMin, vOld;

    Weight &operator=(const double &rvalue);
    Weight &operator+=(const double &right);

    double operator*(const double &right);

    bool operator<=(const double &right);
    bool operator<(const double &right);
};

#endif // WEIGHT_H
