#include <fstream>
#include <iostream>
#include <stack>
#include "graphe.h"
#include<algorithm>

Graphe::Graphe(std::string nomFichier1,std::string nomFichier2)   ///fichier 1 = sommets + coordonees ET arete + sommets relies
{
    ///fichier 2  = aretes + nb de poids + aretes, poids1 et 2

    ///Test ouverture des fichiers 1 et 2
    std::ifstream ifs1{nomFichier1};
    if (!ifs1)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier1 );
    std::ifstream ifs2{nomFichier2};
    if (!ifs2)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier2 );

    ///Parcours fichiers 1 et 2

    ///Test ordre fichier1 = nb de sommets
    int ordre;
    ifs1 >> ordre;
    if ( ifs1.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");

    ///Test sur les sommets du fichier 1 : leur id, leur coord x et y
    int id1;
    float x,y;
    //lecture des sommets
    for (int i=0; i<ordre; ++i)
    {
        ifs1>>id1;
        if(ifs1.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifs1>>x;
        if(ifs1.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifs1>>y;
        if(ifs1.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        m_sommets.push_back({new Sommet{id1,x,y}});
    }

    ///Test taille fichier 1 = nombre d'aretes
    int taille1;
    ifs1 >> taille1;
    if ( ifs1.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");

    ///Test pour la premiere ligne du 2eme fichier : la taille et le nb de poids par arete
    int taille2;
    int nb_poids;
    ifs2 >> taille2 >> nb_poids;
    if ( ifs2.fail() )
        throw std::runtime_error("Probleme lecture taille ou nb de poids du graphe");

    ///Test aretes fichier 1 : leur sommet 1 et sommet 2
    /// + Test aretes fichier 2 : les id des aretes avec leurs 2 poids respectifs
    std::string id2;
    int som1, som2;
    float poids1, poids2;

    for (int i=0; i<taille1; ++i)
    {
        ifs1>>id1;
        if(ifs1.fail())
            throw std::runtime_error("Probleme lecture id aretes fichier 1");
        ifs1>>som1;
        if(ifs1.fail())
            throw std::runtime_error("Probleme lecture sommet1 aretes fichier 1");
        ifs1>>som2;
        if(ifs1.fail())
            throw std::runtime_error("Probleme lecture sommet2 aretes fichier 1");
        ifs2>>id2;
        if(ifs2.fail())
            throw std::runtime_error("Probleme lecture id aretes fichier 2");
        ifs2>>poids1;
        if(ifs2.fail())
            throw std::runtime_error("Probleme lecture poids1 aretes fichier 2");
        ifs2>>poids2;
        if(ifs2.fail())
            throw std::runtime_error("Probleme lecture poids1 aretes fichier 2");

        Sommet* p_som1=nullptr;
        Sommet* p_som2=nullptr;

        for (auto it: m_sommets)
        {
            if(it->getIdSom()==som1)
                p_som1=it;

            if(it->getIdSom()==som2)
                p_som2=it;
        }

        m_aretes.push_back(new Aretes{id1,p_som1,p_som2,poids1,poids2});
    }
}

Graphe::Graphe(std::vector<Sommet*> som, std::vector<Aretes*> ar):m_sommets{som},m_aretes{ar}
{

}

std::vector<Aretes*> Graphe::trie_poids1()
{
    std::sort(m_aretes.begin(), m_aretes.end(), [](Aretes* a1, Aretes* a2)
    {
        return a1->getPoids1() < a2->getPoids1();
    });
    return m_aretes;
}

std::vector<Aretes*> Graphe::trie_poids2()
{
    std::sort(m_aretes.begin(), m_aretes.end(), [](Aretes* a1, Aretes* a2)
    {
        return a1->getPoids2() < a2->getPoids2();
    });
    return m_aretes;
}

std::vector<std::pair<Sommet*, int>> Graphe::voisins (int som)
{
    std::vector<std::pair<Sommet*,int>> vois;
    for(size_t i = 0; i < m_aretes.size(); ++i)
    {
        if(m_aretes[i]->getSom1()->getIdSom()==som)
        {
            vois.push_back(std::make_pair(m_aretes[i]->getSom2(),i));
        }
        else if(m_aretes[i]->getSom2()->getIdSom()==som)
        {
            vois.push_back(std::make_pair(m_aretes[i]->getSom1(),i));
        }
    }
    return vois;
}

bool Graphe::estUnArbre()
{
    std::vector<bool> decouverts(m_sommets.size(), false);
    std::vector<bool> a_decouvertes(m_aretes.size(), false);
    std::stack<Sommet *> pile;

    pile.push(m_sommets[0]);

    bool cyclique = false;

    while(!pile.empty())
    {
        Sommet *s = pile.top();
        pile.pop();

        for(std::pair<Sommet*,int> &n : voisins(s->getIdSom()))
        {
            if(!decouverts[n.first->getIdSom()])
            {
                pile.push(n.first);
                a_decouvertes[n.second]=true;
            }
            else if(!a_decouvertes[n.second])
            {
                cyclique = true;
            }
        }

        decouverts[s->getIdSom()]=true;
    }

    if(count(decouverts.begin(),decouverts.end(),true)!=m_sommets.size())
    {
        return false;
    }
    else if(cyclique)
    {
        return false;
    }
    else
    {
        return true;
    }
}


void Graphe::Kruskal1(Svgfile& svgout, int choix_poids)
{
    std::vector<Aretes*> areteselected;    ///vecteur contenant les aretes selectionnées pour l'apm
    std::vector<Sommet*> sommets_krusakl = m_sommets; ///vecteur avec tous mes sommets

    std::vector<Aretes*> c_aretes(m_aretes); /// creer un nv vecteur qui a les mm aretes que mon vecteur de base (m_aretes)

    if (choix_poids == 1)
    {
        std::sort(c_aretes.begin(), c_aretes.end(), [](Aretes* a1, Aretes* a2)
        {
            return a1->getPoids1() < a2->getPoids1();
        });
    }
    if (choix_poids == 2)
    {
        std::sort(c_aretes.begin(), c_aretes.end(), [](Aretes* a1, Aretes* a2)
        {
            return a1->getPoids2() < a2->getPoids2();
        });
    }

    unsigned int i, j=0, m;

    std::vector <int> connex; /// tableau de connexité

    /// on remplit le taleau, de 1 à X (numéro des sommets)
    for(i=0; i<c_aretes.size(); i++) ///PK M.ARETES.SIZE()
        connex.push_back(i);

    while ( areteselected.size() != m_sommets.size()-1 ) /// Attention : condition qui fonctionne juste pr les graphes connexes
    {
        int ics1 = connex[c_aretes[j]->getSom1()->getIdSom()];
        int ics2 = connex[c_aretes[j]->getSom2()->getIdSom()];

        if(ics1 != ics2) ///si ils sont dif ils prennent la meme valeur et arete selctionee
        {
            //std::cout << "arete selectionnee" << std::endl;

            areteselected.push_back(c_aretes[j]); /// remplir le vecteur d'aretes juste avec les aretes selectionees
            c_aretes[j]->afficherDataAretes();

            for(m=0; m<connex.size(); m++)
                if(connex[m] == ics1) /// si on a trouvé le sommet dans le vector connex
                {
                    connex[m] = ics2; /// on donne au sommet lié par l'arrete le même numéro que le sommet recherché
                    //std::cout << "conexe modifie" << std::endl;
                }
        }
        j++;
    }

    /// Appelle la fonction dessiner pour afficher mon arbre de Kruskal
    for (auto g1: areteselected)
    {
        g1->dessiner(svgout);
    }
    for (auto g1: sommets_krusakl)
    {
        g1->dessiner(svgout);
    }

    /// réucpère les poids totaux de mon arbre de kruskal en parcourant ses aretes
    float P1=0,P2=0;
    for (size_t i=0; i<areteselected.size(); i++)
    {
        P1 += areteselected[i]->getPoids1();
        P2 += areteselected[i]->getPoids2();
    }
    //std::cout<<"poids total 1 : "<< P1 << std::endl;
    //std::cout<<"poids total 2 : "<< P2 << std::endl;
    svgout.addText(100,600,"Poids totaux : ","black");
    svgout.addText(200,600,"(","black");
    svgout.addText(205,600,P1,"black");
    svgout.addText(222,600,",","black");
    svgout.addText(227,600,P2,"black");
    svgout.addText(244,600,")","black");
}

void Graphe::afficher() const
{
    /*
    std::cout<<"graphe : "<<std::endl;
    std::cout<<std::endl;

    std::cout<<"sommet : "<<std::endl;
    std::cout<<"ordre : "<<m_sommets.size()<<std::endl;
    */

    for (auto elem1 : m_sommets)
    {
        elem1->afficherDataSommet();
    }
    //std::cout << std::endl;

    /*
    std::cout<<"arete : "<<std::endl;
    std::cout<<"taille : "<<m_aretes.size()<<std::endl;
    */

    for (auto elem2 : m_aretes)
    {
        elem2->afficherDataAretes();
    }
    //std::cout << std::endl;
}


void Graphe::dessiner(Svgfile &b)
{
    for (auto elem1 : m_sommets)
    {
        elem1->dessiner(b);
    }
    for (auto elem1 : m_aretes)
    {
        elem1->dessiner(b);
    }

}

std::vector<std::vector<bool>> Graphe::compteur_binaire ()
{
    int nbaretes=m_aretes.size();

    std::vector<bool> NbBinaire; ///vecteur de nb binaire : 0 ou 1
    std::vector<std::vector<bool>> tabcombinaisons; ///tableau qui contient toutes les combinaisons avec 1 combinaison == 1 vecteur bool
    for(auto i=0; i<nbaretes; ++i)
    {
        bool nouveau=0;
        NbBinaire.push_back(nouveau); ///on remplie le vecteur de bolléen
    }

    for(auto j=0; j<pow(2,nbaretes); ++j)
    {
        int k=j;
        int n=nbaretes-1;
        do
        {
            if((k-pow(2,n))<0)
            {
                NbBinaire[n]=0;
            }
            else
            {
                k=(k-pow(2,n));
                NbBinaire[n]=1;
            }
            n--;
        }
        while(n>=0);


        tabcombinaisons.push_back(NbBinaire);
    }

    /*
    std::cout << "Toutes les combinaisons du graphe" << std::endl;
    for (auto n=0; n<(int)tabcombinaisons.size(); n++) ///affichage du tableau contenant les 2^n combinaisons
    {
        for (auto i=0; i <(int)tabcombinaisons[n].size(); i++)
            std::cout <<tabcombinaisons[n][i];
        std::cout<<std::endl;
    }
    */

    std::cout<<std::endl;

    ///début du tri1

    std::vector<std::vector<bool>> combi_tri_1; ///vecteur contenant les vecteurs de bool qui ont (ordre - 1) sommets <=> les bons

    for (auto n=0; n<(int)tabcombinaisons.size(); n++)
    {
        int cpt1=0;
        for (auto i=0; i <(int)tabcombinaisons[n].size(); i++)
        {
            if(tabcombinaisons[n][i]==1)
                cpt1++;
        }

        if(cpt1 == (int)m_sommets.size()-1 )
        {
            combi_tri_1.push_back(tabcombinaisons[n]);
        }
    }

    return combi_tri_1;

    ///Affichage tri1
    /*
    std::cout << "apres le tri 1" << std::endl;
    for (auto n=0; n<(int)combi_tri_1.size(); n++)
    {
        for (auto i=0; i <(int)combi_tri_1[n].size(); i++)
            std::cout <<combi_tri_1[n][i];
        std::cout<<std::endl;
    }

    std::cout << "tri 2 taille : " << combi_tri_1.size() << std::endl;

    std::cout << std::endl;
    */


    ///début du tri2

    std::vector<std::vector<bool>> combi_tri_2;


    for(auto n=0; n<(int)combi_tri_1.size(); n++)
    {
        if(connex(combi_tri_1[n]) ==  true) /// récupère le true/false de la fonction bool : connex et push_back si true
            combi_tri_2.push_back(combi_tri_1[n]);
    }

    ///Affichage tri2
    /*
    std::cout << "apres le tri 2" << std::endl;
    for (auto n=0; n<(int)combi_tri_2.size(); n++)
    {
        for (auto i=0; i <(int)combi_tri_2[n].size(); i++)
            std::cout <<combi_tri_2[n][i];
        std::cout<<std::endl;
    }
    */

    //std::cout << "tri 2 taille : " <<combi_tri_2.size() << std::endl;

    return combi_tri_2;
}

bool Graphe::connex(std::vector<bool> graphe_con)
{
    std::vector<int> connex;
    std::vector<Aretes*> vec_aretes;

    for(auto i=0; i<(int)m_sommets.size(); i++) ///je remplie mon tableau de connexite
        connex.push_back(i);

    for(auto x=0; x <(int)graphe_con.size(); x++) ///je parcours mon 1er tableau trié
    {
        if(graphe_con[x] == 1) ///si le vecteur a un bit = 1
        {
            //std::cout << "arete : " << n << std::endl;


            int j=abs(x-(m_aretes.size()-1));

            int ics1, ics2;
            int a1, a2;

            for (auto elem : m_aretes)
            {
                if (elem->getIdArete() == j)
                {
                    ics1 = connex[elem->getSom1()->getIdSom()]; /// ics1 et ics2 prennent la valeur du som1 du tab de connexite
                    ics2 = connex[elem->getSom2()->getIdSom()];
                    a1  = elem->getSom1()->getIdSom();
                    a2  =  elem->getSom2()->getIdSom();
                }
            }

            if(connex[ics1] != connex[ics2]) /// si les 2 valeurs sont diferentes
            {
                connex[a1] = -1; /// on leur attribue une valeur différente de toutes les autres
                connex[a2] = -1;
            }
        }
    }

    int cpt=0;
    for(auto y=0; y<(int)connex.size(); y++) /// je parcours mon vecteur de connexite
    {
        if (connex[y] == (-1))
        {
            cpt++;
        }
    }

    if (cpt==(int)m_sommets.size()) ///si le compteur de -1 = taille tableau connexité
        return true; ///le graphe est connex donc on renvoie true
    else
        return false;
}




std::vector<Graphe*> Graphe::remplir_graphe(std::vector<std::vector<bool>> sol_pareto)  ///recoit en paramètre les 8 sol sous forme de bool
{
    std::vector<Graphe*> pareto;

    for (size_t i=0; i<sol_pareto.size(); i++) /// je parcours mes X solutions sous forme de bool
    {
        std::vector<Aretes*> nv_aretes;
        for (size_t j=0; j<sol_pareto[i].size(); j++)
        {
            if (sol_pareto[i][j] == true)  /// si il y a une arete
            {
                nv_aretes.push_back(m_aretes[j]);
            }
        }
        pareto.push_back(new Graphe{m_sommets,nv_aretes});
    }
    //std::cout<<"test"<<std::endl;
    return pareto;
}

float Graphe::poids1_tot ()
{
    float poids = 0;
    for (size_t i=0; i<m_aretes.size(); i++)
    {
        poids += m_aretes[i]->getPoids1();
    }
    return poids;
}

float Graphe::poids2_tot()
{
    float poids = 0;
    for (size_t i=0; i<m_aretes.size(); i++)
    {
        poids += m_aretes[i]->getPoids2();
    }
    return poids;
}

void Graphe::pareto(std::vector<Graphe*> solutions)
{
    Svgfile svg("pareto.svg");
    svg.addGrid(); // Affichage grille

    //svg.addLine(solutions[0]->poids1_tot()*15-30,800-solutions[0]->poids2_tot()*10+150,solutions[0]->poids1_tot()*15-30,800-solutions[0]->poids2_tot()*10-400,"black");  // Axe des ordonnées
    //svg.addText(solutions[0]->poids1_tot()*15-45,800-solutions[0]->poids2_tot()*10-405,"Poids 2","black"); // "y : Cout 2"
    //svg.addLine(solutions[0]->poids1_tot()*15-30,800-solutions[0]->poids2_tot()*10+150,solutions[0]->poids1_tot()*15-30+600,800-solutions[0]->poids2_tot()*10+150,"black"); // Axe des abscisses
    //svg.addText(solutions[0]->poids1_tot()*15-30+605,800-solutions[0]->poids2_tot()*10+150,"Poids 1","black"); // "x : Cout 1"

    ///parmis ces solutions, je vais chercher les solutions NON dominées

    std::vector<Graphe*> sol_pareto;

    ///je trie mes solutions par leurs poids1 croissants et poids2 croissants à valeures poids1 égales
    std::sort(solutions.begin(), solutions.end(), [](Graphe* g1, Graphe* g2)
    {
        return g1->poids1_tot() < g2->poids1_tot() || (g1->poids1_tot() == g2->poids1_tot() && g1->poids2_tot() < g2->poids2_tot());
    });

    sol_pareto.push_back(solutions[0]); /// quoi qu'il arrive ma première solution est pareto
    svg.addDisk(solutions[0]->poids1_tot()*15-150,700-solutions[0]->poids2_tot()*10,3,"green"); ///je l'affiche en vert


    float poids_ref_2 = solutions[0]->poids2_tot(); ///poids de ref2 est le poids 2 de ma première sol
    std::cout <<"pareto 0 -> poids 1 : " <<solutions[0]->poids1_tot()<<", poids 2  : "<<solutions[0]->poids2_tot() << std::endl<<std::endl;

    for (size_t j=1; j<solutions.size(); j++) ///je démarre a 1 car la première est deja sol
    {
        if (solutions[j]->poids2_tot() < poids_ref_2) ///si le poids total 2 de ma solution j < poids ref (oui pour la première)
        {
            sol_pareto.push_back(solutions[j]); ///alors c une solution de pareto
            svg.addDisk(solutions[j]->poids1_tot()*15-150,700-solutions[j]->poids2_tot()*10,3,"green"); ///je l'affiche en vert

            poids_ref_2 = solutions[j]->poids2_tot();  ///le poids de ref prend la valeur du poids2 total de ma nv solution
            std::cout <<"pareto "<<j<< "-> poids 1 : " <<solutions[j]->poids1_tot()<<", poids 2  : "<<solutions[j]->poids2_tot() << std::endl;

            Svgfile currsvg(std::to_string(j)+".svg"); ///fichier qui dessine les graphe de chacune de mes sol de pareto
            solutions[j]->dessiner(currsvg);
        }
        if(solutions[j]->poids2_tot() > poids_ref_2)
        {
            svg.addDisk(solutions[j]->poids1_tot()*15-150,700-solutions[j]->poids2_tot()*10,3,"red"); ///si NON Pareto = rouge
            //std::cout << "non retenues -> P1: " << solutions[j]->poids1_tot()<< " P2: " << solutions[j]->poids2_tot()<<std::endl;
        }
    }
    std::cout <<"nb sol pareto : "<<sol_pareto.size()<<std::endl;
}


std::vector<std::vector<float>> Graphe::matricedadjacence()
{
    std::vector<std::vector<float>> Mat_adj;
    std::vector <float> initialisation;
    int taillesommet=m_sommets.size();
    std::cout<<m_sommets.size()<<std::endl;
    for(auto i=0; i<(int)taillesommet; i++)
    {
        for(auto j=0; j<(int)taillesommet; j++)
        {
            initialisation.push_back(0);
        }
        Mat_adj.push_back(initialisation);
    }

//    for(auto m=0; m<(int)taillesommet; m++)
//    {
//        for(auto n=0; n<(int)taillesommet; n++)
//        {
//            std::cout<<Mat_adj[m][n]<<" ";
//        }
//        std::cout<<std::endl;
//    }


    for(auto x=0; x<(int)taillesommet; x++)
    {
        for(auto y=0; y<(int)taillesommet; y++)
        {
            for(auto z=0; z<(int)m_aretes.size(); z++)
            {
                if( x==m_aretes[z]->getSom1()->getIdSom()&& y==m_aretes[z]->getSom2()->getIdSom())
                    //if(x==m_aretes[z]->getSom1()->getIdSom() && y==m_aretes[z]->getSom2()->getIdSom())  ///marche que si somet de l'arete est de type sommet
                {
                    std::cout<<"Poids 2: "<< m_aretes[z]->getPoids2()<<std::endl;
                    Mat_adj[x][y]=m_aretes[z]->getPoids2();
                    Mat_adj[y][x]=m_aretes[z]->getPoids2();
                    std::cout<<"matrice: "<<Mat_adj[x][y]<<std::endl;

                }
            }
        }
    }
    for(auto i=0; i<(int)taillesommet; i++)
    {
        for(auto j=0; j<(int)taillesommet; j++)
        {
            std::cout<<Mat_adj[i][j]<<" ";
        }
        std::cout<<std::endl;
    }

    return Mat_adj;
}



void Graphe::Dijkstra(int som_dep)
{
    //graphe Dijdij;
    std::vector<std::vector<float>> mat_adj_ponderee=matricedadjacence();
    std::vector<int> SommetMarques;
    std::vector <int> predecesseur;
    std::vector<float> DistanceMini;
    int xmin=0;
    float poids_min=9999999; ///distance min du prochain sommet à marquer
    int nb_som_marques=0;



    for(auto i=0; i<(int)m_sommets.size(); i++)
    {
        SommetMarques.push_back(0);
        predecesseur.push_back(-1);
        DistanceMini.push_back(99999999);
    }
    DistanceMini[som_dep]=0;
    //poids_min=infini;

    while(nb_som_marques <(int)m_sommets.size())
    {

        poids_min=9999999;

        for(auto x=0; x<(int)m_sommets.size(); x++)
        {
            if(SommetMarques[x]==0 && DistanceMini[x]<poids_min)
            {
                xmin = x ;
                poids_min = DistanceMini[x];
            }
        }

        SommetMarques[xmin]=1;
        nb_som_marques++;

        for(auto y=0; y<(int)m_sommets.size(); y++)
        {
            if((mat_adj_ponderee[xmin][y]!=0) &&  (SommetMarques[y]==0) && (DistanceMini[xmin] + mat_adj_ponderee[xmin][y] < DistanceMini[y]))
            {
                DistanceMini[y]=DistanceMini[xmin] + mat_adj_ponderee[xmin][y];
                predecesseur[y]=xmin;

            }
        }

    }

    for(auto i=0; i<(int)predecesseur.size(); ++i)
    {
        std::cout<<predecesseur[i]<<"->";
    }
}




/*void pareto(std::vector<Graphe*> solutions)
{
    Svgfile svg("pareto.svg");
    svg.addGrid();
    //std::cout << "pareto ?" <<std::endl;

    ///parmis ces solutions, je vais chercher les solutions NON dominées

    std::vector<Graphe*> sol_pareto;

    std::sort(solutions.begin(), solutions.end(), [](Graphe* g1, Graphe* g2)
    {
        return g1->poids1_tot() < g2->poids1_tot(); ///mes graphes sont triés par poids1
    });

    float poids_ref = 1000000; ///poids 2 de ref que je vais comparer aux autres : un infini
    //float last_val_poids1 = 0;

    for (auto j=0; j<(int)solutions.size(); j++)
    {
        if ( (solutions[j]->poids2_tot() < poids_ref)&& (solutions[j]->poids1_tot() != solutions[j+1]->poids1_tot())
        {
                sol_pareto.push_back(solutions[j]);
                poids_ref = solutions[j]->poids2_tot();

                svg.addDisk(solutions[j]->poids1_tot()*15,800-solutions[j]->poids2_tot()*10,5,"green");
                Svgfile currsvg(std::to_string(j)+".svg");

                solutions[j]->dessiner(currsvg);

            //std::cout <<"poids tot 1 : " <<solutions[j]->poids1_tot() << std::endl;
            //std::cout <<"poids tot 2 : " <<solutions[j]->poids2_tot() << std::endl<<std::endl;
        }
        if ( (solutions[j]->poids2_tot() < poids_ref) && (solutions[j]->poids1_tot() == solutions[j+1]->poids1_tot())
        {
            for( auto i=0; i<(int)solutions.size(); i++)
            {
                while( solutions[i]->poids1_tot() == solutions[i+1]->poids1_tot())
                {
                    if ( solutions[i+1]->poids2_tot() < solutions[i]->poids2_tot())
                    {
                        poids_ref=solutions[i+1]->poids2_tot() ;
                        solutions[j]=solutions[i+1];
                    }
                }
            }

                sol_pareto.push_back(solutions[j]);
                poids_ref = solutions[j]->poids2_tot();

                svg.addDisk(solutions[j]->poids1_tot()*15,800-solutions[j]->poids2_tot()*10,5,"green");
                Svgfile currsvg(std::to_string(j)+".svg");

                solutions[j]->dessiner(currsvg);

        }
        else
        {
            svg.addDisk(solutions[j]->poids1_tot()*15,800-solutions[j]->poids2_tot()*10,5,"red");
        }
    }
}*/



























