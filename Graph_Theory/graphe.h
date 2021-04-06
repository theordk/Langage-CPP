#ifndef GRAPHE_H
#define GRAPHE_H
#include <string>
#include <unordered_map>
#include "sommet.h"
#include "arretes.h"
#include <iostream>

class Graphe
{
    public:
        Graphe(std::string,std::string);
        Graphe(std::vector<Sommet*>, std::vector<Aretes*> m_aretes);

        void afficher() const;
        void dessiner(Svgfile& b);

        void Kruskal1(Svgfile& svgout, int choix_poids);

        std::vector<std::vector<bool>> compteur_binaire ();
        bool connex(std::vector<bool> graphe_con);
        std::vector<std::pair<Sommet*, int>> voisins (int som);
        bool estUnArbre();

        std::vector<Graphe*> remplir_graphe(std::vector<std::vector<bool>> sol_pareto);
        float poids1_tot ();
        float poids2_tot ();

        std::vector<Aretes*> trie_poids1();
        std::vector<Aretes*> trie_poids2();

        std::vector<std::vector<float>> matricedadjacence();
        void Dijkstra(int som_dep);

        void pareto(std::vector<Graphe*> solutions);

    protected:

    private:
        std::vector<Sommet*> m_sommets;
        std::vector<Aretes*> m_aretes;
};

#endif // GRAPHE_H
