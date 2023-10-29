#include "propagation_model.h"
#include <iostream>
#include <cmath>


Propagation_Model::Propagation_Model()
{

}

double Uma_LOS(double d, float frec){
    return 28 + 22 * log10(d) + 20* log10(frec);
}
