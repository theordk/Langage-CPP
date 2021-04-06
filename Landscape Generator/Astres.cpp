#include "Ciel.h"


/// class mère Astre

Astre::Astre(double posx, double posy, int r, int rr, int rg, int rb)
:m_position{posx,posy},m_rayon{r},m_color{rr,rg,rb}
{}

void Astre::afficher()
{
    m_position.afficher();
    std::cout<<" rayon:"<<m_rayon<<" ";
    m_color.afficher();
}

void Astre::dessiner(Svgfile &svgtest, std::mt19937 seed)
{
    svgtest.addDisk(m_position.getx(),m_position.gety(),m_rayon,Svgfile::makeRGB(m_color.getr(),m_color.getg(),m_color.getb()));
}

void Astre::setRayon(int nouveauRayon)
{
    this->m_rayon=nouveauRayon;
}

/// class fille AstreElliptique

AstreElliptique::AstreElliptique(double posx, double posy, int r, int rr, int rg, int rb, int rr1, int rg1, int rb1, int rr2, int rg2,int rb2, int r2)
:Astre{posx,posy,r,rr,rg,rb},m_colorEllipse2{rr1,rg1,rb1},m_color2{rr2,rg2,rb2}
{r2=r/3;
m_rayon2=r2;}

void AstreElliptique::dessiner(Svgfile& svgtest, std::mt19937 seed)
{
    svgtest.addEllipse(m_position.getx(),m_position.gety(),m_rayon,m_rayon2,Svgfile::makeRGB(m_color.getr(),m_color.getg(),m_color.getb()));
    svgtest.addEllipse(m_position.getx(),m_position.gety(),m_rayon-(m_rayon/10),m_rayon2-(m_rayon2/6),Svgfile::makeRGB(m_colorEllipse2.getr(),m_colorEllipse2.getg(),m_colorEllipse2.getb()));
    svgtest.addDiskGrad(m_position.getx(),m_position.gety(),(m_rayon/2),Svgfile::makeRGB(m_color2.getr(),m_color2.getg(),m_color2.getb()),Svgfile::makeRGB(alea(0,255,seed),alea(0,255,seed),alea(0,255,seed)));
}

void AstreElliptique::afficher()
{
    std::cout << "planet : ";
    m_position.afficher();
    std::cout<<" rayon1:"<<m_rayon<<" "<<"rayon2:"<<m_rayon2<<" ";
    m_color.afficher();
    m_colorEllipse2.afficher();
    m_color2.afficher();
}


/// class lune

AstreLune::AstreLune(double posx, double posy, int r, int taille, int choix, int rr, int rg, int rb)
 : Astre{posx,posy,r,rr,rg,rb},m_tailleCroissant{taille},m_choix{choix}
{}

void AstreLune::dessiner(Svgfile &svgtest, std::mt19937 seed)
{
    if(this->m_choix==1)
    {
        svgtest.addDisk(m_position.getx(),m_position.gety(),m_rayon,Svgfile::makeRGB(m_color.getr(),m_color.getg(),m_color.getb()));
        svgtest.addDisk(m_position.getx()+m_tailleCroissant,m_position.gety(),m_rayon,Svgfile::makeRGB(11,22,77));
    }
    if(this->m_choix==2)
    {
        svgtest.addDisk(m_position.getx(),m_position.gety(),m_rayon,Svgfile::makeRGB(m_color.getr(),m_color.getg(),m_color.getb()));
        svgtest.addDisk(m_position.getx()-m_tailleCroissant,m_position.gety(),m_rayon,Svgfile::makeRGB(11,22,77));
    }
    if(this->m_choix==3)
    {
        svgtest.addDisk(m_position.getx(),m_position.gety(),m_rayon,Svgfile::makeRGB(m_color.getr(),m_color.getg(),m_color.getb()));
    }
}

/// class Etoile

AstreEtoile::AstreEtoile(double posx, double posy, int r, int rr, int rg, int rb):Astre{posx,posy,r,rr,rg,rb}
{}

void AstreEtoile::dessiner(Svgfile &svgtest, std::mt19937 seed)
{
    svgtest.addRectangle(m_position.getx(),m_position.gety(),m_rayon,m_rayon,Svgfile::makeRGB(m_color.getr(),m_color.getg(),m_color.getb()));
    svgtest.addTriangle(m_position.getx(),m_position.gety(),m_position.getx()+m_rayon,m_position.gety(),(m_position.getx()+(m_position.getx()+m_rayon))/2,m_position.gety()-m_rayon,Svgfile::makeRGB(m_color.getr(),m_color.getg(),m_color.getb()));
    svgtest.addTriangle(m_position.getx(),m_position.gety()+m_rayon,m_position.getx()+m_rayon,m_position.gety()+m_rayon,(m_position.getx()+(m_position.getx()+m_rayon))/2,m_position.gety()+(2*m_rayon),Svgfile::makeRGB(m_color.getr(),m_color.getg(),m_color.getb()));
    svgtest.addTriangle(m_position.getx(),m_position.gety(),m_position.getx(),m_position.gety()+m_rayon,m_position.getx()-m_rayon,(m_position.gety()+(m_position.gety()+m_rayon))/2,Svgfile::makeRGB(m_color.getr(),m_color.getg(),m_color.getb()));
    svgtest.addTriangle(m_position.getx()+m_rayon,m_position.gety(),m_position.getx()+m_rayon,m_position.gety()+m_rayon,m_position.getx()+(2*m_rayon),(m_position.gety()+(m_position.gety()+m_rayon))/2,Svgfile::makeRGB(m_color.getr(),m_color.getg(),m_color.getb()));

}

/// class Soleil

AstreSoleil::AstreSoleil(double posx, double posy, int r, int rr, int rg, int rb) : Astre{posx,posy,r,rr,rg,rb}
{}

void AstreSoleil::dessiner(Svgfile &svgtest, std::mt19937 seed)
{
    svgtest.addDisk(m_position.getx(),m_position.gety(),m_rayon,Svgfile::makeRGB(m_color.getr(),m_color.getg(),m_color.getb()));
    svgtest.addShadow(m_position.getx(),m_position.gety(),m_rayon,m_rayon,Svgfile::makeRGB(255,128,0));
    svgtest.addCircle(m_position.getx(),m_position.gety(),m_rayon,3,Svgfile::makeRGB(255,128,0));
}


