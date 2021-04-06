#ifndef SOMMET_H
#define SOMMET_H
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "svgfile.h"

class Sommet
{
    public:
        Sommet(int,float,float);
        void afficherDataSommet() const;
        void dessiner(Svgfile &b);

        int getIdSom (){return m_id_som;}
        float getX(){return m_x;}
        float getY(){return m_y;}


    protected:

    private:
        int m_id_som;
        float m_x, m_y;
};

#endif // SOMMET_H
