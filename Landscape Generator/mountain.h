#ifndef MOUNTAIN_H_INCLUDED
#define MOUNTAIN_H_INCLUDED
#include <iostream>
#include <list>
#include <ctime>
#include <cstdlib>
#include "Coords.h"
#include "SVGFILE.h"
#include "UTIL.h"
#include "Ciel.h"

using namespace util;

class Mountain
{
    public:
        Mountain(double posx, double posy, int largeur, int hauteur, int r, int g, int b);
        void afficher();
        void dessiner(Svgfile &svgtest, double xSoleil);

    protected:
        Coords m_base;
        int m_largeur;
        int m_hauteur;
        Couleur m_color;
};


class Chain
{
    public:
        Chain(int mini=100, int maxi=150, int nbMountain=0);
        void remplir(std::mt19937 seed, int mini, int maxi, int nbMontagnes=0);
        void dessiner(Svgfile &svgtest, double xSoleil);
        std::vector<Mountain*> getCollection();
        int getMini();
        int getMaxi();
        void changerMiniMaxi(int nouveauMini, int nouveauMaxi);
        void supprMountain();
    private:
        std::vector<Mountain*> m_mountainChain;
        int m_miniH;
        int m_maxiH;
        int m_nbMountain;
};





#endif // MOUNTAIN_H_INCLUDED
