#include <iostream>
#include "graphe.h"
#include<string>

void pareto(std::vector<Graphe*> g);

int main()
{
    Svgfile svgout("krusakl.svg");
    Graphe g{"triville.txt","triville_weights_0.txt"};
    /*std::vector<std::vector<float>> MA;
    MA=g.matricedadjacence();*/

    int choix;
    std::cout << "Faire le tri du graphe par les Poids 1 ou Poids 2 ?" << std::endl;
    std::cin>> choix;

    g.afficher();
    std::cout << "Kruskal = aretes selectionees par l'algo : " << std::endl;
    g.Kruskal1(svgout,choix);


    std::vector<Graphe*> graphes = g.remplir_graphe(g.compteur_binaire());
    std::vector<Graphe*> g_trie;

    //std::cout<<"avant tri 2 "<<graphes.size()<<std::endl;

    for(size_t i=0; i<graphes.size(); i++)
    {
        bool b = graphes[i]->estUnArbre();
        //std::cout<<b<<std::endl;
        if (b)
        {
            g_trie.push_back(graphes[i]);
        }

    }

    std::cout<<"après tri "<<g_trie.size()<<std::endl;
    g.pareto(g_trie);

/*
   int i=0;
    g.Dijkstra(i);*/

    return 0;
}
