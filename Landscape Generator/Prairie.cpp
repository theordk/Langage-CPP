#include "Prairie.h"
#include "UTIL.h"

/// class prairie

Prairie::Prairie(int nbVegetation):m_nbVegetation{nbVegetation}
{}


void Prairie::remplir(int densite_vege, std::mt19937 seed)
{
    /// Fleurs
    for(int i=0; i<(double)alea(60,100,seed)*densite_vege; ++i)
        m_collectionVegetation.push_back(new Fleur{(double)alea(20, 990, seed),(double)alea(450, 900, seed),10,10,255,255,255});

    /// Buissons
    for(int i=0; i<(double)alea(100,200,seed)*densite_vege; ++i)
        m_collectionVegetation.push_back(new Buisson{(double)alea(20, 980, seed),(double)alea(450, 900, seed),(double)alea(15,30,seed),(double)alea(2,6,seed), (double)alea(-25,25,seed),50,190,40});

    /// Arbres
    for(int i=0; i<(double)alea(25,40,seed)*densite_vege; ++i)
        m_collectionVegetation.push_back(new Arbre{(double)alea(20,950,seed),(double)alea(450, 900, seed),(double)alea(100,150,seed),(double)alea(40,70,seed),(double)alea(-40,40,seed),70,170,20});
}

void Prairie::afficher()
{
    for(const auto& vt : m_collectionVegetation)
    {
        vt->afficher();
    }
}

void Prairie::dessiner(Svgfile &svgout,std::mt19937 seed)
{
    for(const auto& vt : m_collectionVegetation)
    {
        vt->dessiner(svgout, seed);
    }
}


/// class mère Vegetation

Vegetation::Vegetation(double posx, double posy, double hauteur, double largeur, int rr, int rg, int rb)
    :m_position{posx,posy}, m_color{rr,rg,rb}, m_hauteur{hauteur},m_largeur{largeur}
{}

void Vegetation::afficher()
{
    m_position.afficher();
    std::cout<<" hauteur:"<<m_hauteur<< " largeur:"<<m_largeur<<" ";
    m_color.afficher();
}

/// Une fonction de détermination d'ordre
/// changer le sens de l'inégalité si ça trie à l'envers !
bool comparerOrdreVege(Vegetation* V1,Vegetation* V2)
{
    return V1->getOrdre() < V2->getOrdre();
}

void Prairie::trierVegetation()
{
    /// Dans le paramètre fonction à la fin on ne met PAS de parenthèses d'appel
    std::sort(m_collectionVegetation.begin(), m_collectionVegetation.end(), comparerOrdreVege);
}

/// class fille Arbre

Arbre::Arbre(double posx, double posy, double hauteur, double largeur, double angle, int rr, int rg, int rb)
    :Vegetation{posx,posy,hauteur,largeur,rr,rg,rb}, m_angle{angle}
{}

void Arbre::dessiner(Svgfile& svgtest, std::mt19937 seed)
{
    double angle=m_angle;
    double x=m_position.getx();
    double y=m_position.gety();
    double r=m_hauteur, rad;
    double ep=m_largeur;

    svgtest.addShadow(x,y,ep,10,Svgfile::makeRGB(m_color.getr()-40,m_color.getg()-40,m_color.getb()-40));
    for (int i=0; i<2; ++i)
    {
        for (int i=0; i<(double)alea(2,4,seed); ++i)
        {
            rad=angle*3.14159265/180;
            svgtest.addTriangleTrigo(x,y,r, angle, ep/5, Svgfile::makeRGB(m_color.getr(),m_color.getg()-100,m_color.getb()));
            svgtest.addEllipse(x-r*sin(rad),y-r*cos(rad),20, 10,Svgfile::makeRGB(m_color.getr(),m_color.getg(),m_color.getb()));

            r=r/3;
            x= x-r*sin(rad);
            y= y-r*cos(rad);
            angle=-angle;
        }
        ep=ep/2;
        angle=-m_angle;
        rad=angle*3.14159265/180;
        r=m_hauteur/(double)alea(2.5,4.0,seed);
        x=m_position.getx()-2*r*sin(-rad);
        y=m_position.gety()-2*r*cos(rad);
    }
    //svgtest.addDisk(x,y-r*cos(rad), 20,Svgfile::makeRGB(m_color.getr(),m_color.getg(),m_color.getb()));
    //svgtest.addEllipse(x-r*sin(rad),y-r*cos(rad),m_largeur/2, m_hauteur/6,Svgfile::makeRGB(m_color.getr(),m_color.getg(),m_color.getb()));
}

/// class Buisson

Buisson::Buisson(double posx, double posy, double hauteur, double largeur, double angle, int rr, int rg, int rb)
    :Vegetation{posx,posy,hauteur,largeur,rr,rg,rb}, m_angle{angle}
{}

void Buisson::dessiner(Svgfile &svgtest, std::mt19937 seed)
{
    double angle=m_angle;
    double x=m_position.getx();
    double y=m_position.gety();
    double r=m_hauteur, rad;

    for(int i=0; i<(double)alea(4,6,seed); ++i)
    {
        for(int i=0; i<(double)alea(4,6,seed); ++i)
        {
            svgtest.addPolygoneTrigo(x,y,r, angle, m_largeur/2, Svgfile::makeRGB(m_color.getr(),m_color.getg()-100,m_color.getb()));
            rad=angle*3.14159265/180;
            x= x-r*sin(rad);
            y= y-r*cos(rad);
            r=r/2;
            angle=2*angle;
        }
        angle=(double)alea(-m_angle,m_angle-1,seed);
        r=m_hauteur;
        x=m_position.getx();
        y=m_position.gety();
    }
}


/// class Fleur

Fleur::Fleur(double posx, double posy, double hauteur, double largeur, int rr, int rg, int rb)
    :Vegetation{posx,posy,hauteur,largeur,rr,rg,rb}
{}

void Fleur::dessiner(Svgfile &svgtest, std::mt19937 seed)
{
    svgtest.addEllipse(m_position.getx(),m_position.gety(), m_largeur/2, m_hauteur,Svgfile::makeRGB(m_color.getr(),m_color.getg(),m_color.getb()));
    svgtest.addEllipse(m_position.getx(),m_position.gety(),m_largeur, m_hauteur/2,Svgfile::makeRGB(m_color.getr(),m_color.getg(),m_color.getb()));
    svgtest.addDisk(m_position.getx(),m_position.gety(),m_hauteur/3,Svgfile::makeRGB(m_color.getr(),m_color.getg(),0));
}

