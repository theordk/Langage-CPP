#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include<unordered_set>
#include "arretes.h"
#include "sommet.h"



Aretes::Aretes(int id_aretes, Sommet* som1,Sommet* som2,/*int som1, int som2,*/ float poids1,float poids2)
        : m_id_aretes{id_aretes},p_som1{som1}, p_som2{som2},m_poids1{poids1},m_poids2{poids2}
{
}

float Aretes::getPoids1() const
{
    return m_poids1;
}

float Aretes::getPoids2() const
{
    return m_poids2;
}

void Aretes::afficherDataAretes() const
{
    std::cout<<"    "<<m_id_aretes<<" : "<<"(somt1,som2)=("<<p_som1->getIdSom()<<","<<p_som2->getIdSom()<<")"<<std::endl;
    std::cout<<"        "<<"(poids1,poids2)=("<<m_poids1<<","<<m_poids2<<")"<<std::endl;
}

void Aretes::dessiner(Svgfile &b)
{
    b.addLine(p_som1->getX(),p_som1->getY(),p_som2->getX(),p_som2->getY(),"black");
    b.addText((p_som1->getX()+p_som2->getX())/2,(p_som1->getY()+p_som2->getY())/2-5,m_id_aretes,"green");
}

Aretes::~Aretes()
{
}
