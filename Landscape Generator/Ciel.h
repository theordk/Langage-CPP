#ifndef CIEL_H_INCLUDED
#define CIEL_H_INCLUDED

#include <iostream>
#include <list>
#include <ctime>
#include <cstdlib>
#include "Coords.h"
#include "SVGFILE.h"
#include "UTIL.h"

using namespace util;


class Astre
{
    public:
        Astre(double posx, double posy, int r, int rr, int rg, int rb);
        ~Astre()=default;
        virtual void afficher();
        virtual void dessiner(Svgfile &svgtest, std::mt19937 seed);
        void setRayon(int nouveauRayon);

    protected:
        Coords m_position;
        int m_rayon;
        Couleur m_color;
};

class AstreElliptique : public Astre
{
    public:
        AstreElliptique(double posx, double posy, int r, int rr, int rg, int rb, int rr1, int rg1, int rb1, int rr2, int rg2,int rb2, int r2=0);
        virtual void dessiner(Svgfile& svgtest, std::mt19937 seed);
        virtual void afficher();
    protected:
        int m_rayon2;
        Couleur m_colorEllipse2;
        Couleur m_color2;
};

class AstreLune : public Astre
{
    public:
        AstreLune(double posx, double posy, int r, int taille, int choix,int rr=255, int rg=255, int rb=255);
        virtual void dessiner(Svgfile &svgtest, std::mt19937 seed);
    private:
        int m_tailleCroissant;          ///limiter a 10-35
        int m_choix;
};

class AstreEtoile : public Astre
{
    public:
        AstreEtoile(double posx, double posy, int r=6, int rr=255, int rg=255, int rb=255);
        void dessiner(Svgfile &svgtest, std::mt19937 seed);

};


class AstreSoleil : public Astre
{
    public:
        AstreSoleil(double posx, double posy, int r, int rr=255, int rg=255, int rb=0);
        void dessiner(Svgfile &svgtest, std::mt19937 seed);
};




class Ciel
{
    public :
        Ciel(int nbAstre);
        void setNbEtoiles(int nouveauNbEtoile);
        int getNbEtoiles();
        void afficher();
        void dessiner(Svgfile &svgout, std::mt19937 seed);
        void remplir(int densiteEtoiles, double &xSoleil, std::mt19937 seed);
        void ajouterLune(std::mt19937 &seed, int rightLeft);
        void ajouterSoleil(std::mt19937 &seed, int rightLeft, double &xSoleil);
        void ajouterEtoile(std::mt19937 &seed);
        void ajouterEtoileAlea(std::mt19937 &seed);
        void supprEtoile();
        void ajouterPlanete(std::mt19937 seed);
        std::vector<Astre*> getCollection();
        void supprAstre();
        void modifierRayon(int nouveauRayon, int rang);

    private :
        std::vector<Astre*> m_collectionPlanete;
        int m_nbEtoiles;
};



#endif // CIEL_H_INCLUDED
