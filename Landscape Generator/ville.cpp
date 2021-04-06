#include"ville.h"

///Classe Ville
Ville::Ville(int nbBatiments)
    :m_nbBatiments{nbBatiments}
{}


void Ville::setNbBatiments(int nouveauNbBatiments)
{
    m_nbBatiments=nouveauNbBatiments;
}

int Ville::getNbBatiments()
{
    return m_nbBatiments;
}

std::vector<Batiments*> Ville::getCollection()
{
    return m_collectionBatiments;
}

void Ville::remplir(int densiteBatiments, std::mt19937 seed)
{
    double angle;

    for(int i=0; i<alea(3,5,seed)*densiteBatiments; ++i)        ///Nombre d'iles
    {
        m_xColline.push_back((double)alea(50,950,seed));
        for(int u=0; u<alea(1,3,seed); ++u)                     ///Nombre de maisons par ile
        {
            angle=(double) alea(-30,30,seed);
            m_collectionBatiments.push_back(new BatimentMaison{m_xColline[i]+248*sin(angle*3.14159265/180),600-248*cos(angle*3.14159265/180),-angle,(double)alea(35,50,seed),(double)alea(35,50,seed),alea(0,255,seed),alea(0,255,seed),alea(0,255,seed)});
        }

        for(int u=0; u<alea(1,2,seed); ++u)                     ///Nombre d'immeubles par ile
        {
            m_collectionBatiments.push_back(new BatimentImmeuble{(double)alea(m_xColline[i]-30,m_xColline[i]+30,seed),(double)alea(375,400,seed),(double)alea(50,100,seed),(double)alea(100,170,seed),alea(0,255,seed),alea(0,255,seed), alea(0,255,seed),(double)alea(20,30,seed),(double)alea(5,10,seed)});
        }
    }
    this->trierBatiments();
}

/// Une fonction de détermination d'ordre
/// changer le sens de l'inégalité si ça trie à l'envers !
bool comparerOrdreBat(Batiments* B1,Batiments* B2)
{
    return B1->getOrdre() < B2->getOrdre();
}

void Ville::trierBatiments()
{
    /// Dans le paramètre fonction à la fin on ne met PAS de parenthèses d'appel
    std::sort(m_collectionBatiments.begin(), m_collectionBatiments.end(), comparerOrdreBat );
}


void Ville::dessiner(Svgfile &svgout, std::mt19937 seed)
{
    for (size_t i=0;i<m_xColline.size();++i)
        svgout.addDisk(m_xColline[i] ,600,250, Svgfile::makeRGB(60,160,60),1);

    for(const auto& it : m_collectionBatiments)
    {
        it->dessiner(svgout, seed);
    }
}

void Ville::ajouterBatiments(std::mt19937 seed)
{
    m_collectionBatiments.push_back(new BatimentImmeuble{(double)alea(1,900,seed),(double)alea(402,440,seed),(double)alea(50,100,seed),(double)alea(100,170,seed),alea(0,255,seed),alea(0,255,seed),
                                            alea(0,255,seed),(double)alea(20,30,seed),(double)alea(5,10,seed)});
    //m_collectionBatiments.push_back(new BatimentMaison{(double)util::alea(1, 1000, seed),(double)util::alea(1, 400, seed)});
}

void Ville::ajouterBatimentsAlea(std::mt19937 &seed)
{
    m_collectionBatiments.push_back(new BatimentImmeuble{(double)alea(1,900,seed),(double)alea(402,440,seed),(double)alea(50,100,seed),(double)alea(100,170,seed),alea(0,255,seed),alea(0,255,seed),
                                            alea(0,255,seed),(double)alea(20,30,seed),(double)alea(5,10,seed)});
    //m_collectionBatiments.push_back(new BatimentMaison{(double)util::alea(1, 1000, seed),(double)util::alea(1, 400, seed)});
}

void Ville::supprBatiments()
{
    m_collectionBatiments.erase(m_collectionBatiments.begin()+m_collectionBatiments.size()-1);
}

void Ville::modifierCol(Couleur nv_col,int rang)
{
    m_collectionBatiments[rang]->setCol(nv_col);
}

///Classe Batiments
Batiments::Batiments(double posx, double posy, double largeur, double hauteur, int rr, int rg, int rb)
    :m_position{posx,posy},m_largeur{largeur},m_hauteur{hauteur},m_color{rr,rg,rb}
{}

void Batiments::afficher()
{
    m_position.afficher();
    std::cout<<" largeur:"<<m_largeur<<" ";
    std::cout<<" hauteur:"<<m_hauteur<<" ";
    m_color.afficher();
}

void Batiments::setCol(Couleur nv_col)
{
    this->m_color=nv_col;
}

void Batiments::dessiner(Svgfile &svgtest, std::mt19937 seed)
{
    svgtest.addRectangle(m_position.getx(),m_position.gety(),m_largeur,m_hauteur,Svgfile::makeRGB(m_color.getr(),m_color.getg(),m_color.getb()));
}

///1ere fille : Immeuble
BatimentImmeuble::BatimentImmeuble(double posx, double posy, double largeur, double hauteur,int rr, int rg, int rb, double nbfenetres, double etages)
    :Batiments{posx,posy,largeur,hauteur,rr,rg,rb},m_nbfenetres{nbfenetres},m_etages{etages}
{
}

void BatimentImmeuble::afficher()
{
    m_position.afficher();
    m_color.afficher();
}

void BatimentImmeuble::dessiner(Svgfile& svgtest, std::mt19937 seed)
{
    ///affichage de l'immeuble
    svgtest.addRectangle(m_position.getx()-m_largeur/2,m_position.gety()-m_hauteur,m_largeur,m_hauteur,Svgfile::makeRGB(m_color.getr(),m_color.getg(),m_color.getb()),20,180);
    //Svgfile::makeRGB(m_color.getr(),m_color.getg(),m_color.getb())



    int nbF = m_nbfenetres/m_etages;  //nb de fenetre par etage
    int l=5;  //largeur ET hauteur des fenetres

    double X = (m_largeur-(nbF*l))/(nbF+1);  //espace entre les fenêtres
    double Y = (m_hauteur-(m_etages*l))/(m_etages+1)/2;  //espace entre les fenêtres en Y deux fois inf a la largeur

    float largeur_porte = m_largeur/6.6;
    float hauteur_porte = (m_hauteur - ((m_etages*(l+Y))+8))/2;  // /2 -> sinon la porte est trop haute pcq espace entre les etages diminués
    float x_porte = m_position.getx()-m_largeur/2+((m_largeur/2)-(largeur_porte/2));
    float y_porte = m_position.gety()-m_hauteur+m_hauteur-hauteur_porte;

    for(int i=1; i<=m_etages+2; ++i) // +2 -> on rajoute encore 2 etages pour combler le vide
    {
        double yn=m_position.gety()-m_hauteur+i*Y+(i-1)*l;  // position en y de la i-eme fenetre
        for(int k=1; k<=nbF; ++k)
        {
            double xn=m_position.getx()-(m_largeur/2)+k*X+(k-1)*l;  // position en x de la k-eme fenetre
            //std::cout<<xn<<";"<<yn<<std::endl;
            /// affichage des fenetres
            svgtest.addRectangle(xn,yn,l,l,Svgfile::makeRGB(255,255,0));  //aléatoire : alea(0,255),alea(0,255),alea(0,255)
        }
    }
    ///affichage de la porte
    svgtest.addRectangle(x_porte,y_porte,largeur_porte,hauteur_porte-2.5,Svgfile::makeRGB(m_color.getr()-40,m_color.getg()+80,m_color.getb()+40));
}

///2eme classe fille : Maison
BatimentMaison::BatimentMaison(double posx,double posy,double angle,double largeur,double hauteur,int rr,int rg,int rb)
    :Batiments{posx,posy,largeur,hauteur,rr,rg,rb},m_angle{angle}
{
}

void BatimentMaison::afficher()
{
    m_position.afficher();
    m_color.afficher();
}

void BatimentMaison::dessiner(Svgfile &svgtest,std::mt19937 seed)
{
    int x1,y1,x2,y2,x3,y3;

    ///Base
    svgtest.addRectangleTrigo(m_position.getx(),m_position.gety(),m_hauteur,m_largeur,m_angle, Svgfile::makeRGB(m_color.getr(),m_color.getg(),m_color.getb()));

    ///Porte
    svgtest.addRectangleTrigo(m_position.getx(),m_position.gety(),m_hauteur/3,m_largeur/4,m_angle, Svgfile::makeRGB(m_color.getr()-50,m_color.getg()-20,m_color.getb()+40));

    ///Fenetres
    x1=m_position.getx()-((m_hauteur/2)*sin(m_angle*3.14159265/180))-cos(m_angle*3.14159265/180)*m_largeur/4;
    y1=m_position.gety()-((m_hauteur/2)*cos(m_angle*3.14159265/180))+sin(m_angle*3.14159265/180)*m_largeur/4;
    x2=m_position.getx()-((m_hauteur/2)*sin(m_angle*3.14159265/180))+cos(m_angle*3.14159265/180)*m_largeur/4;
    y2=m_position.gety()-((m_hauteur/2)*cos(m_angle*3.14159265/180))-sin(m_angle*3.14159265/180)*m_largeur/4;

    svgtest.addRectangleTrigo(x1,y1,m_hauteur/4,m_largeur/4,m_angle, Svgfile::makeRGB(255,255,0),1);
    svgtest.addRectangleTrigo(x2,y2,m_hauteur/4,m_largeur/4,m_angle, Svgfile::makeRGB(255,255,0),1);
    svgtest.addLine(x1,y1,x1-((m_hauteur/4)*sin(m_angle*3.14159265/180)),y1-((m_hauteur/4)*cos(m_angle*3.14159265/180)));
    svgtest.addLine(x2,y2,x2-((m_hauteur/4)*sin(m_angle*3.14159265/180)),y2-((m_hauteur/4)*cos(m_angle*3.14159265/180)));

    ///Toit
    x1=m_position.getx()-((5*m_hauteur/3)*sin(m_angle*3.14159265/180));
    y1=m_position.gety()-((5*m_hauteur/3)*cos(m_angle*3.14159265/180));
    x2=m_position.getx()-(9*m_hauteur/10)*sin(m_angle*3.14159265/180)-cos(m_angle*3.14159265/180)*m_largeur;
    y2=m_position.gety()-(9*m_hauteur/10)*cos(m_angle*3.14159265/180)+sin(m_angle*3.14159265/180)*m_largeur;
    x3=m_position.getx()-(9*m_hauteur/10)*sin(m_angle*3.14159265/180)+cos(m_angle*3.14159265/180)*m_largeur;
    y3=m_position.gety()-(9*m_hauteur/10)*cos(m_angle*3.14159265/180)-sin(m_angle*3.14159265/180)*m_largeur;
    svgtest.addTriangle(x1,y1,x2,y2,x3,y3,Svgfile::makeRGB(m_color.getr()-50,m_color.getg()-20,m_color.getb()+40));

}
