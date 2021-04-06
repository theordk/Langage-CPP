#ifndef ARRETES_H_INCLUDED
#define ARRETES_H_INCLUDED
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "sommet.h"

class Aretes
{
public :
    Aretes(int,Sommet*,Sommet*,float,float);
    ~Aretes();
    void afficherDataAretes() const;
    void dessiner(Svgfile &b);

    float getPoids1 () const;
    float getPoids2 () const;

    Sommet* getSom1 () const {return p_som1;}
    Sommet* getSom2 () const {return p_som2;}

    int getIdArete ()const {return m_id_aretes;}



private :
        /// Données spécifiques a l'arete
        int m_id_aretes;
        Sommet* p_som1,*p_som2;
        float m_poids1, m_poids2;

};


#endif // ARRETES_H_INCLUDED
