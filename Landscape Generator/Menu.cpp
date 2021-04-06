#include "Menu.h"

void menu (Ciel plan4, Chain plan3, Ville plan2, Prairie plan1, std::mt19937 seed, double xSoleil)
{
    int variableSortie=1;
    int variableChoix;

    std::mt19937 seedP1=seed;
    std::mt19937 seedP2=seed;
    std::mt19937 seedP3=seed;
    std::mt19937 seedP4=seed;
    std::mt19937 seedActuel=seed;

    remplir(plan4,plan3,plan2,plan1,seed,xSoleil);
    //dessin(plan4,plan3,plan2,plan1,xSoleil,seed);

    do
    {
        std::cout<<std::endl<<"Selectionnez l'action a effectuer : "
                 <<std::endl<<"1 Dessiner"
                 <<std::endl<<"2 Nouveau terrain"
                 <<std::endl<<"3 Modifier un plan"
                 <<std::endl<<"0 Quitter"
                 <<std::endl<<"Choisissez le numero de l'action a effectuer : ";
        std::cin>>variableSortie;
        std::cout<<std::endl;

        switch(variableSortie)
        {
        case 1:
        {
            Svgfile svgout;
            svgout.addRectangle(0,0,1000,400,Svgfile::makeRGB(11,22,77));
            plan4.dessiner(svgout, seed);
            plan3.dessiner(svgout, xSoleil);
            plan2.dessiner(svgout,seed);

            svgout.addRectGrad(0,400,1000,500,Svgfile::makeRGB(60,160,60),Svgfile::makeRGB(50,120,50));
            plan1.dessiner(svgout,seed);

            std::cout<<"Dessin effectue"<<std::endl;
            break;
        }


        case 2:
            remplir(plan4,plan3,plan2,plan1,seed,xSoleil);
            std::cout<<"Nouveau terrain cree"<<std::endl;

            break;
        case 3:
            do
            {
                std::cout<<"Choisissez un plan a modifier : "<<std::endl
                         <<"1 Prairie "<<std::endl
                         <<"2 Ville "<<std::endl
                         <<"3 Montagne "<<std::endl
                         <<"4 Ciel "<<std::endl
                         <<"0 Annuler"<<std::endl;
                std::cin>>variableChoix;
            }
            while((variableChoix<0)||(variableChoix>4));
            switch (variableChoix)
            {
            case 1:
                seedActuel=seedP1;
                break;
            case 2:
                seedActuel=seedP2;
                break;
            case 3:
                seedActuel=seedP3;
                break;
            case 4:
                seedActuel=seedP4;
                break;
            }
            if (variableChoix!=0)
                menuModif(variableChoix,plan4,plan3,plan2,plan1,xSoleil,seed,seedActuel);
            break;
        }
        //dessin(plan4,plan3,plan2,plan1,xSoleil,seed);
    }
    while(variableSortie != 0);
}

void menuModif(int variableChoix,Ciel &plan4, Chain &plan3, Ville &plan2, Prairie &plan1, int xSoleil, std::mt19937 seed, std::mt19937 &seedActuel)
{
    std::string phrase;
    int choixAction;
    int valSeed;
    int nbElement;
    switch (variableChoix)
    {
    case 4:
        phrase="des etoiles";
        break;
    case 3:
        phrase="des montagnes";
        break;
    case 2:
        phrase="des batiments";
        break;
    case 1:
        phrase="de la vegetation";
        break;
    }
    do
    {
        std::cout<<std::endl<<"Selectionnez l'action a effectuer : "

                 <<std::endl<<"1 Changer la valeur de la graine du plan"
                 <<std::endl<<"2 Augmenter densite "<<phrase
                 <<std::endl<<"3 Reduire la densite "<<phrase;
        if (variableChoix!=2)
            std::cout<<std::endl<<"4 Modifier la taille "<<phrase;
        else
            std::cout<<std::endl<<"4 Modifier la couleur "<<phrase;

        std::cout<<std::endl<<"0 Quitter"
                 <<std::endl<<"Choisissez le numero de l'action a effectuer : ";
        std::cin>>choixAction;
        std::cout<<std::endl;
    }
    while((choixAction<0)||(choixAction>4));

    switch (choixAction)
    {

    case 1:

        std::cout<<"Changer la graine:  "<<std::endl;
        std::cout<<"Entrez la valeur de la graine : ";
        std::cin>>valSeed;
        std::cout<<std::endl;
        seedActuel=convertNumeroSeed(valSeed);
        if (variableChoix==4)
            modifierGraineCiel(plan4,seedActuel,xSoleil);
        if (variableChoix==3)
            modifierGraineMontagne(plan3,seedActuel);
        if (variableChoix==2)
            modifierGraineVille(plan2,seedActuel);

        break;

    case 2:
        std::cout<<"Augmenter densite "<<phrase<<std::endl;
        std::cout<< "Saisir la densite : ";
        std::cin >> nbElement;
        std::cout << std::endl;
        if (variableChoix==4)
            augmenterDensiteEtoiles(plan4,seedActuel,nbElement);
        if (variableChoix==3)
            modifierDensiteMontagnes(plan3,seedActuel,nbElement);
        if (variableChoix==2)
            augmenterDensiteBatiments(plan2,seedActuel,nbElement);
        break;

    case 3:
        std::cout<<"Reduire densite "<<phrase<<std::endl;
        std::cout<< "Saisir la densite : ";
        std::cin >> nbElement;
        std::cout << std::endl;
        if (variableChoix==4)
            reduireDensiteEtoiles(plan4,seedActuel,nbElement);
        if (variableChoix==3)
            modifierDensiteMontagnes(plan3,seedActuel,nbElement);
        if (variableChoix==2)
            reduireDensiteBatiments(plan2,seedActuel,nbElement);
        break;

    case 4:
        if (variableChoix!=2)
        {
            std::cout<<"Modifier taille "<<phrase<<std::endl;
            std::cout<< "Saisir la taille : ";
            std::cin >> nbElement;
            std::cout << std::endl;
            if (variableChoix==4)
                modifierTailleEtoiles(plan4,nbElement);
            if (variableChoix==3)
                modifierHauteurMontagne(plan3,nbElement-10,nbElement+10,seed);
        }
        else
            modifierCouleurBatiments(plan2,seedActuel);
        break;
    }

}



void remplir(Ciel &plan4, Chain &plan3, Ville &plan2, Prairie &plan1, std::mt19937 seed, double xSoleil)
{
    plan4.remplir(1,xSoleil, seed);
    plan3.remplir(seed,100,150);
    plan2.remplir(1,seed);
    plan1.remplir(1,seed);
}
void augmenterDensiteEtoiles(Ciel &plan4, std::mt19937 seed, int nbEtoile)
{
    for(int i=0; i<nbEtoile; ++i)
        plan4.ajouterEtoileAlea(seed);
    plan4.setNbEtoiles(plan4.getNbEtoiles()+nbEtoile);
}

void reduireDensiteEtoiles(Ciel &plan4, std::mt19937 seed, int nbEtoile)
{
    for(int i=0; i<nbEtoile; ++i)
        plan4.supprEtoile();
    plan4.setNbEtoiles(plan4.getNbEtoiles()-nbEtoile);
}

void modifierGraineCiel(Ciel &plan4, std::mt19937 seed, double xSoleil)
{
    eraseCiel(plan4);
    plan4.remplir(1,xSoleil,seed);
}
void eraseCiel(Ciel &plan4)
{
    //std::cout<<plan4.getCollection().size()<<std::endl;
    size_t nb=plan4.getCollection().size();
    //std::cout<<nb<<std::endl;
    for(size_t i=0; i<nb; ++i)
    {
        plan4.supprAstre();
    }

}

std::mt19937 convertNumeroSeed(int numero)
{
    std::mt19937 seed{numero};
    return seed;
}


void modifierTailleEtoiles(Ciel &plan4, int taille)
{
    size_t nb=plan4.getNbEtoiles();
    for(size_t i=(plan4.getCollection().size())-nb; i<plan4.getCollection().size(); ++i)
    {
        plan4.modifierRayon(taille,i);
    }
}

/// Montagnes
void modifierHauteurMontagne(Chain &plan3, int mini, int maxi, std::mt19937 seed)
{
    for(size_t i=0; i<plan3.getCollection().size(); ++i)
    {
        plan3.supprMountain();
    }
    plan3.remplir(seed,mini,maxi);
}

void modifierGraineMontagne(Chain &plan3, std::mt19937 seed)
{
    for(size_t i=0; i<plan3.getCollection().size(); ++i)
    {
        plan3.supprMountain();
    }
    plan3.remplir(seed,plan3.getMini(),plan3.getMaxi());
}

void modifierDensiteMontagnes(Chain &plan3, std::mt19937 seed, int nbMontagnes)
{
    for(size_t i=0; i<plan3.getCollection().size(); ++i)
    {
        plan3.supprMountain();
    }
    plan3.remplir(seed,plan3.getMini(),plan3.getMaxi(),nbMontagnes);
}


///Parametre ville

void augmenterDensiteBatiments(Ville &plan2, std::mt19937 seed, int niveau)
{
    for(int i=0; i<niveau; ++i)
    {
        plan2.ajouterBatimentsAlea(seed);
    }
    plan2.setNbBatiments(plan2.getNbBatiments()+niveau);
}

void reduireDensiteBatiments(Ville &plan2, std::mt19937 seed, int niveau)
{
    for(int i=0; i<niveau; ++i)
    {
        plan2.supprBatiments();
    }
    plan2.setNbBatiments(plan2.getNbBatiments()-niveau);
}

void modifierGraineVille(Ville &plan2, std::mt19937 seed)
{
    eraseVille(plan2);
    plan2.remplir(1,seed);
}
void eraseVille(Ville &plan2)
{
    //std::cout<<plan4.getCollection().size()<<std::endl;
    size_t nb=plan2.getCollection().size();
    //std::cout<<nb<<std::endl;
    for(size_t i=0; i<nb; ++i)
    {
        plan2.supprBatiments();
    }

}

void modifierCouleurBatiments(Ville &plan2, std::mt19937 seed)
{
    ///size_t nb=plan2.getNbBatiments();
    for(size_t i=0; i<plan2.getCollection().size(); ++i)
    {
        Couleur nv_col {util::alea(0,255,seed),util::alea(0,255,seed),util::alea(0,255,seed)};
        plan2.modifierCol(nv_col,i);
    }
}

