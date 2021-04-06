#include "Coords.h"

Coords::Coords(double a, double b): m_x{a}, m_y{b}
{}

Coords::~Coords()
{}

Coords::Coords()
{
    std::cout << "init manuel, veuillez entrer x et y svp" << std::endl;
    std::cin >> m_x;
    std::cin >> m_y;
    std::cout << std::endl;
}

void Coords::afficher()
{
    std::cout << "x:" << m_x << " y:" << m_y ;
}

Coords operator+(const Coords& c1, const Coords& c2)
{
    Coords result(0,0);
    result.m_x=c1.m_x+c2.m_x;
    result.m_y=c1.m_y+c2.m_y;
    return result;
}

Coords operator*(double m, const Coords& c)
{
    Coords result(0,0);
    result.m_x=c.m_x*m;
    result.m_y=c.m_y*m;
    return result;
}

Coords operator/(const Coords& c,double m)
{
    Coords result(0,0);
    result.m_x=c.m_x/m;
    result.m_y=c.m_y/m;
    return result;
}

double Coords::getx() const
{
    return m_x;
}

double Coords::gety() const
{
    return m_y;
}
