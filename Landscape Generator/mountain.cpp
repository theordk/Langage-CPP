#include "mountain.h"

/// class Mountain

Mountain::Mountain(double posx, double posy, int largeur, int hauteur, int r, int g, int b):
m_base{posx,posy},m_largeur{largeur}, m_hauteur{hauteur}, m_color{r,g,b}
{}


void Mountain::afficher()
{
    m_base.afficher();
    std::cout<<" largeur:"<<m_largeur<<" hauteur:"<<m_hauteur<<" ";
    m_color.afficher();
}


void Mountain::dessiner(Svgfile &svgtest,double xSoleil)
{
    int ombre=50;
    if (xSoleil<m_base.getx()+m_largeur/2)
        ombre=-ombre;
    svgtest.addTriangle(m_base.getx(),m_base.gety(),m_base.getx()+m_largeur/2,m_base.gety(),m_base.getx()+(m_largeur/2),m_base.gety()-m_hauteur,Svgfile::makeRGB(m_color.getr(),m_color.getg(),m_color.getb()));
    svgtest.addTriangle(m_base.getx()+m_largeur/2,m_base.gety(),m_base.getx()+m_largeur,m_base.gety(),m_base.getx()+(m_largeur/2),m_base.gety()-m_hauteur,Svgfile::makeRGB(m_color.getr()+ombre,m_color.getg()+ombre,m_color.getb()+ombre));
}


/// class Chain

Chain::Chain(int mini, int maxi, int nbMountain):m_miniH{mini}, m_maxiH{maxi}, m_nbMountain{nbMountain}
{}

std::vector<Mountain*> Chain::getCollection()
{
    return m_mountainChain;
}

int Chain::getMini()
{
    return m_miniH;
}
int Chain::getMaxi()
{
    return m_maxiH;
}


void Chain::changerMiniMaxi(int nouveauMini, int nouveauMaxi)
{
    m_miniH=nouveauMini;
    m_maxiH=nouveauMaxi;
}

void Chain::remplir(std::mt19937 seed, int mini, int maxi, int nbMontagnes)
{
    m_miniH=mini;
    m_maxiH=maxi;
    if(nbMontagnes==0)
        m_nbMountain=util::alea(40, 70, seed);
    else
        m_nbMountain=nbMontagnes;
    for(int i=0;i<m_nbMountain;++i)
    {
        m_mountainChain.push_back(new Mountain{(double)util::alea(0, 900, seed),400,util::alea(50, 200, seed),util::alea(m_miniH, m_maxiH, seed),util::alea(26, 170, seed),util::alea(13, 70, seed),util::alea(0, 1, seed)});
    }
}

void Chain::dessiner(Svgfile &svgtest, double xSoleil)
{
    for(const auto& it : m_mountainChain)
    {
        it->dessiner(svgtest, xSoleil);
    }
}

void Chain::supprMountain()
{
    m_mountainChain.erase(m_mountainChain.begin());
}



