#include "Ciel.h"

/// class ciel

Ciel::Ciel(int nbAstre)
{
    nbAstre=0;
    m_nbEtoiles=nbAstre;
}

void Ciel::setNbEtoiles(int nouveauNbEtoile)
{
    m_nbEtoiles=nouveauNbEtoile;
}

int Ciel::getNbEtoiles()
{
    return m_nbEtoiles;
}

std::vector<Astre*> Ciel::getCollection()
{
    return m_collectionPlanete;
}


void Ciel::remplir(int densiteEtoiles, double &xSoleil, std::mt19937 seed)
{
    int posSol=util::alea(1,2,seed);
    int posLune;
    if(posSol==1)
    {
        xSoleil=(double)util::alea(850, 950, seed);
        posLune=2;
    }
    else
    {
        xSoleil=(double)util::alea(50, 150, seed);
        posLune=1;
    }


    /// Sun
    this->ajouterSoleil(seed,posSol,xSoleil);

    /// lune
    this->ajouterLune(seed,posLune);

    /// Planet
    for(int i=0;i<util::alea(1, 3, seed)*densiteEtoiles;++i)
        this->ajouterPlanete(seed);

    /// Stars
    for(int i=0;i<util::alea(5, 8, seed)*densiteEtoiles;++i)
    {
        this->ajouterEtoile(seed);
        m_nbEtoiles++;
    }
}

void Ciel::afficher()
{
    for(const auto& it : m_collectionPlanete)
    {
        it->afficher();
    }
}

void Ciel::dessiner(Svgfile &svgout, std::mt19937 seed)
{
    for(const auto& it : m_collectionPlanete)
    {
        it->dessiner(svgout, seed);
    }
}

void Ciel::ajouterLune(std::mt19937 &seed, int rightLeft)
{
    /// Lune
    int choix=util::alea(1,3,seed);
    if(rightLeft==2)
        m_collectionPlanete.push_back(new AstreLune{(double)util::alea(50, 100, seed),(double)util::alea(60, 100, seed),50,25,choix});
    else
        m_collectionPlanete.push_back(new AstreLune{(double)util::alea(850, 950, seed),(double)util::alea(60, 100, seed),50,25,choix});

}

void Ciel::ajouterSoleil(std::mt19937 &seed, int rightLeft, double &xSoleil)
{
    m_collectionPlanete.push_back(new AstreSoleil{xSoleil,(double)util::alea(60, 100, seed),50});
}

void Ciel::ajouterEtoile(std::mt19937 &seed)
{
    m_collectionPlanete.push_back(new AstreEtoile{(double)util::alea(1, 1000, seed),(double)util::alea(1, 400, seed)});
}

void Ciel::ajouterEtoileAlea(std::mt19937 &seed)
{
    m_collectionPlanete.push_back(new AstreEtoile{(double)util::alea(1, 1000, seed),(double)util::alea(1, 400, seed)});
}

void Ciel::supprEtoile()
{
    m_collectionPlanete.erase(m_collectionPlanete.begin()+m_collectionPlanete.size()-1);
}

void Ciel::ajouterPlanete(std::mt19937 seed)
{
    double y=(double)util::alea(1, 350, seed);
    if(y>=250)
        m_collectionPlanete.push_back(new AstreElliptique{(double)util::alea(50,950, seed),y,util::alea(30, 100, seed),util::alea(0, 255, seed),util::alea(0, 255, seed),util::alea(0, 255, seed),util::alea(0, 255, seed),util::alea(0, 255, seed),util::alea(0, 255, seed),util::alea(0, 255, seed),util::alea(0, 255, seed),util::alea(0, 255, seed)});
    else
        m_collectionPlanete.push_back(new AstreElliptique{(double)util::alea(250, 800, seed),y,util::alea(30, 100, seed),util::alea(0, 255, seed),util::alea(0, 255, seed),util::alea(0, 255, seed),util::alea(0, 255, seed),util::alea(0, 255, seed),util::alea(0, 255, seed),util::alea(0, 255, seed),util::alea(0, 255, seed),util::alea(0, 255, seed)});
}


void Ciel::supprAstre()
{
    m_collectionPlanete.erase(m_collectionPlanete.begin());
}


void Ciel::modifierRayon(int nouveauRayon, int rang)
{
    m_collectionPlanete[rang]->setRayon(nouveauRayon);
}
