#include "Trigon.h"

#include <cmath>

Trigon::Trigon()
{

}

void Trigon::initializationC(Trigon &tr, const double &allX, const double &minX,
                                   const double &h, const double &i, const double &n)
{
    tr.initialization(allX, minX, h, i, n);
}

double Trigon::func(const double x) const
{
    if (x < this->xH)
        {
            return 2 * this->h * (x - this->x1) / (this->x2 - this->x1);
        }
        else
        {
            return 2 * this->h * (x - this->x2) / (this->x1 - this->x2);
        }
}

double Trigon::funcC(const Trigon &tr, const double x)
{
    return tr.func(x);
}

void Trigon::initialization(const double &allX, const double &minX, const double &h, const double &i, const double &n)
{
    if (i == 0)
    {
        this->x1=minX - h/2;
        this->x2=minX + h/2;
    }
    else
    {
        if (i == n)
        {
            this->x1 = allX - h/2 + minX;
            this->x2 = allX + h/2 + minX;
        }
        else
        {
            this->x1=allX*(i/n) - h/2 + minX;
            this->x2=allX*(i/n) + h/2 + minX;
        }
    }
    this->xH=(this->x1 + this->x2) / 2;
}
