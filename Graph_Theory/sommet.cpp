#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include<unordered_set>
#include "sommet.h"
#include "svgfile.h"


Sommet::Sommet(int id_som,float x,float y):m_id_som{id_som},m_x{x},m_y{y}
{
}

void Sommet::afficherDataSommet() const
{
    std::cout<<"    "<<m_id_som<<" : "<<"(x,y)=("<<m_x<<","<<m_y<<")"<<std::endl;
}

void Sommet::dessiner(Svgfile &b)
{
    b.addDisk(m_x,m_y,10,"black");
    b.addText(m_x-4,m_y+5,m_id_som,"white");
}
