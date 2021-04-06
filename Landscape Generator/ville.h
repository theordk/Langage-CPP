#ifndef VILLE_H_INCLUDED
#define VILLE_H_INCLUDED

#include "Coords.h"
#include "SVGFILE.h"
#include "util.h"
#include "math.h"

#include <list>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace util;

class Batiments
{
    public:
        Batiments(double posx, double posy, double largeur, double hauteur, int rr, int rg, int rb);
        ///Batiments();
        virtual ~Batiments()=default;
        virtual void afficher();
        virtual void dessiner(Svgfile &svgtest, std::mt19937 seed);
        void setCol(Couleur nv_col);

        double getOrdre() const
        { return m_position.gety(); }
        //bool compare(Batiments const & other) const;

    protected:
        Coords m_position;
        double m_largeur;
        double m_hauteur;
        Couleur m_color;
};

class BatimentImmeuble : public Batiments
{
    public:
        BatimentImmeuble(double posx,double posy,double largeur,double hauteur,int rr,int rg,int rb,double nbfenetres,double etages);

        //void dessiner_immeuble(Svgfile& svgout, double x, double y);

        virtual void dessiner(Svgfile& svgtest,std::mt19937 seed);
        virtual void afficher();

    private:
        double m_nbfenetres;
        double m_etages;
};

class BatimentMaison : public Batiments
{
    public:
        BatimentMaison(double posx,double posy,double angle,double largeur,double hauteur,int rr,int rg,int rb);

        void dessiner(Svgfile& svgtest,std::mt19937 seed);
        void afficher();
    private:
        double m_angle;
};


class Ville
{
    public :
        Ville(int nbBatiments);

        void afficher();
        void dessiner(Svgfile &svgout, std::mt19937 seed);
        void remplir(int densiteBatiments, std::mt19937 seed);
        void trierBatiments();

        int getNbBatiments();
        void setNbBatiments(int nouveauNbBatiments);
        std::vector<Batiments*> getCollection();

        void ajouterBatiments(std::mt19937 seed);
        void ajouterBatimentsAlea(std::mt19937 &seed);
        void supprBatiments();
        void modifierCol(Couleur nv_col,int rang);
        //void modifierHauteur(int nv_hauteur, int rang);

    private :
        ///std::list<Batiments*> m_collectionBatiments;
        std::vector<Batiments*> m_collectionBatiments;
        int m_nbBatiments;
        std::vector<double> m_xColline;
};
#endif // VILLE_H_INCLUDED
