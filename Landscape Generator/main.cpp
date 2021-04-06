#include <iostream>
#include <random>
#include <ctime>
#include "util.h"
#include "Ciel.h"
#include "Prairie.h"
#include "Coords.h"
#include "math.h"
#include "mountain.h"
#include "Menu.h"
#include"ville.h"



int main()
{
    double xSoleil=0.0;
    std::srand(std::time(nullptr));
    int graine=aleatoire_int(1,1000);
    std::mt19937 seed{graine};

    Ciel plan4(1);
    Chain plan3;
    Ville plan2(3);
    Prairie plan1(3);

    menu(plan4, plan3, plan2, plan1, seed, xSoleil);

    return 0;
}
