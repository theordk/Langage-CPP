#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <locale>
#include <iostream>
#include <list>
#include <ctime>
#include <cstdlib>
#include <string>
#include "Coords.h"
#include "SVGFILE.h"
#include "UTIL.h"
#include "Ciel.h"
#include "mountain.h"
#include "Prairie.h"
#include "ville.h"

void menu(Ciel plan4, Chain plan3, Ville plan2, Prairie plan1, std::mt19937 seed, double xSoleil);
void remplir(Ciel &plan4, Chain &plan3, Ville &plan2, Prairie &plan1, std::mt19937 seed, double xSoleil);

void augmenterDensiteBatiments(Ville &plan2, std::mt19937 seed, int niveau);
void reduireDensiteBatiments(Ville &plan2, std::mt19937 seed, int niveau);
void modifierGraineVille(Ville &plan2, std::mt19937 seed);
void eraseVille(Ville &plan2);
void modifierCouleurBatiments(Ville &plan2, std::mt19937 seed);

void menuModif(int variableChoix,Ciel &plan4, Chain &plan3, Ville &plan2, Prairie &plan1, int xSoleil, std::mt19937 seed, std::mt19937 &seedActuel);

void augmenterDensiteEtoiles(Ciel &plan4, std::mt19937 seed, int nbEtoile);
void reduireDensiteEtoiles(Ciel &plan4, std::mt19937 seed, int nbEtoile);
void modifierGraineCiel(Ciel &plan4, std::mt19937 seed, double xSoleil);
void eraseCiel(Ciel &plan4);

void modifierTailleEtoiles(Ciel &plan4, int taille);
std::mt19937 convertNumeroSeed(int numero);


void modifierHauteurMontagne(Chain &plan3, int mini, int maxi, std::mt19937 seed);
void modifierGraineMontagne(Chain &plan3, std::mt19937 seed);
void modifierDensiteMontagnes(Chain &plan3, std::mt19937 seed, int nbMontagnes);

#endif // MENU_H_INCLUDED
