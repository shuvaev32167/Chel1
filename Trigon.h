#ifndef TRIGON_H
#define TRIGON_H

class Trigon
{
public:
    Trigon();

    double x1, x2, xH;

    const double h = 1;

    void initialization(const double &allX, const double &minX,const double &h, const double &i, const double &n);

    static void initializationC(Trigon &tr, const double &allX, const double &minX, const double &h,
                               const double &i, const double &n);

    double func(const double x) const;

    static double funcC(const Trigon &tr, const double x);
};

#endif // TRIGON_H
