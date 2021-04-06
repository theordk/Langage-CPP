#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include <string>
#include <random>
#include <ctime>
#include <iostream>

namespace util
{

class Couleur
{
    public:
        Couleur(int rr, int rg, int rb);
        void afficher();
        int getr();
        int getg();
        int getb();

    private:
        int m_r;
        int m_g;
        int m_b;
};

/// L'appel de cette fonction redirige les
/// donn�es du fichier dont le nom est pass�
/// en param�tre vers std::cin
/// On "simule" les frappes clavier ce qui
/// permet de tester sans avoir � retaper
/// � chaque fois les m�me donn�es
/// temporisation : nombre de milliseconde entre chaque frappe clavier
/// couleur : colorisation (WINDOWS seulement https://ss64.com/nt/color.html
///                         pr�fixer par 0x, exemple 0x1a vert sur fond bleu)
void startAutoCin(std::string fileName, size_t temporisation=0, short couleur=0);

/// Cette fonction doit �tre appel�e pour
/// terminer la saisie automatique et retrouver
/// un comportement normal (saisir au clavier)
void stopAutoCin();

/// Vide tampon clavier
void videCin();

/// Cette fonction retourne un entier al�atoire dans [min...max]
int alea(int min, int max);
double aleatoire(int mini, int maxi);
int aleatoire_int(int mini, int maxi);

int alea(int min, int max, std::mt19937& randGen);
double alea(double min, double max,  std::mt19937& randGen);
void testAlea();

/// Le code qui suit est sp�cifique aux plateformes Windows
/// et ne concerne ni macOS ni les Linux
#ifdef _WIN32
void accentsPourWindows();
#endif // _WIN32

}


#endif // UTIL_H_INCLUDED
