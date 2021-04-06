#ifndef PRAIRIE_H_INCLUDED
#define PRAIRIE_H_INCLUDED

#include <iostream>
#include "Coords.h"
#include "SVGFILE.h"
#include <list>
#include "UTIL.h"
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace util;

class Vegetation
{
public:
    Vegetation(double posx, double posy, double hauteur, double largeur, int rr, int rg, int rb);
    ~Vegetation()=default;
    virtual void afficher();
    double getOrdre() const
    {
        return m_position.gety();
    }
    virtual void dessiner(Svgfile &svgtest, std::mt19937 seed)=0;

protected:
    Coords m_position;
    Couleur m_color;
    double m_hauteur;
    double m_largeur;
};

class Arbre : public Vegetation
{
public:
    Arbre(double posx, double posy, double hauteur, double largeur, double angle, int rr, int rg, int rb);
    virtual void dessiner(Svgfile &svgtest, std::mt19937 seed);
private:
    double m_angle;
};

class Buisson : public Vegetation
{
public:
    Buisson(double posx, double posy, double hauteur, double largeur, double angle, int rr=255, int rg=255, int rb=255);
    virtual void dessiner(Svgfile &svgtest, std::mt19937 seed);
private:
    double m_angle;
};

class Fleur : public Vegetation
{
public:
    Fleur(double posx, double posy, double hauteur, double largeur, int rr=255, int rg=255, int rb=255);
    void dessiner(Svgfile &svgtest, std::mt19937 seed);

};


class Prairie
{
public :
    Prairie(int nbVegetation);

    void afficher();
    void trierVegetation();
    void dessiner(Svgfile &svgout, std::mt19937 seed);
    void remplir(int densite_vege, std::mt19937 seed);

private :
    std::vector<Vegetation*> m_collectionVegetation;
    int m_nbVegetation;
};

#endif // PRAIRIE_H_INCLUDED
