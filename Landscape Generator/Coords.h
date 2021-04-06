#ifndef COORDS_H_INCLUDED
#define COORDS_H_INCLUDED
#include <iostream>

class Coords
{
    private:
        double m_x;
        double m_y;
    public:
        Coords(double a, double b);
        Coords();
        ~Coords();
        void afficher();
        friend Coords operator+(const Coords& c1, const Coords& c2);
        friend Coords operator*(double m, const Coords& c);
        friend Coords operator/(const Coords& c,double m);
        double getx() const;
        double gety() const;
};

#endif // COORDS_H_INCLUDED
