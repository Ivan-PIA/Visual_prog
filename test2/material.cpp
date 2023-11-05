#include "material.h"



double Get_Glass(double freq){
    return (2 + 0.2*freq);
}

double Get_Glass_IRR(double freq){
    return (23 + 3.0 * freq);
}
double Get_Concrete(double freq){
    return (5 + 4.0 * freq);
}
double Get_Wood(double freq){
    return (4.85 + 0.12 * freq);
}
