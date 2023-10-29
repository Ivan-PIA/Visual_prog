#ifndef MATERIAL_H
#define MATERIAL_H


class Material
{
    private:

    public:
        Material();
        double Get_Glass(double freq);
        double Get_Glass_IRR(double freq);
        double Get_Concrete(double freq);
        double Get_Wood(double freq);

};

#endif // MATERIAL_H
