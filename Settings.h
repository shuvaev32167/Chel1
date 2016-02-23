#ifndef SETTINGS_H
#define SETTINGS_H

#include "Weight.h"

class Settings
{
public:
    static double iStep;
    static double eps_min;
    static double minX;
    static double maxX;
    static double allX;
    static double h_min;

    static int n, nn;
};

#endif // SETTINGS_H
