/*
 -----------------------------------------------------------------------------------
 Laboratoire : 04
 Fichier     : Labo_04_blanc_saez.cpp
 Auteur(s)   : Julien Blanc et Sébastien Saez
 Date        : 19.11.2015

 But         : Le but de l'application est de simuler le nombre de déplacements que 
 *             ferait un robot sur les ségments d'une matrice de N x N. A chaque
 *             fois que le robot heurte les bords de la matrice, il fait se déplace
 *             d'un segment dans le sens opposé.

 Remarque(s) : 

 Compilateur : g++ 5.2.0
 -----------------------------------------------------------------------------------
 */
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <limits>

using namespace std;

// Constantes
const unsigned short RANDOM_MIN = 1;
const unsigned short RANDOM_MAX = 4;
const unsigned int NB_EXP_MIN = 1000;
const unsigned int NB_EXP_MAX = 10000;
const unsigned int LARGEUR_COLONNE_1 = 3;
const unsigned int LARGEUR_COLONNE_2 = 20;
const unsigned int TAILLE_MATRICE_MAX = 50;

int main() {

   // Variables
   unsigned short randDeplacement;
   unsigned int nombreDeplacements = 0;
   unsigned int nombreDeplacementsTotal = 0;
   unsigned int nbExperiences;
   unsigned int limiteHaut;
   unsigned int limiteDroite;
   int limiteBas;
   int limiteGauche;
   int coordonneeDeX;
   int coordonneeDeY;
   bool murHaut;
   bool murBas;
   bool murDroite;
   bool murGauche;
   double moyenneDeplacement;

   do
   {
      cout << "Veuillez entrer le nombre d'experimentations a effectuer "
              "(entre 1000 et 10000 compris):" << endl;
      cin >> nbExperiences;

      if (cin.fail())
      {
         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
      }

      if ((nbExperiences < NB_EXP_MIN or nbExperiences > NB_EXP_MAX) and cin.fail() == false)
      {
         cout << "La valeur que vous avez entree n'est pas comprise dans l'intervalle"
              << endl;
      }
   }
   while ((nbExperiences < NB_EXP_MIN or nbExperiences > NB_EXP_MAX) and cin.fail() == false);

   for (int tailleMatrice = 2; tailleMatrice <= TAILLE_MATRICE_MAX; tailleMatrice += 2)
   {
      limiteDroite = limiteHaut = tailleMatrice / 2;
      limiteGauche = limiteBas = tailleMatrice / -2;

      for (int i = 0; i < nbExperiences; i++)
      {
         coordonneeDeX = 0;
         coordonneeDeY = 0;
         murBas = false;
         murDroite = false;
         murGauche = false;
         murHaut = false;
         nombreDeplacementsTotal += nombreDeplacements;
         nombreDeplacements = 0;
         moyenneDeplacement = 0;

         while (!murBas or !murHaut or !murDroite or !murGauche)
         {
            randDeplacement = rand() % (RANDOM_MAX - RANDOM_MIN + 1) + RANDOM_MIN;

            switch (randDeplacement)
            {
               case 1:
               {
                  coordonneeDeX++;
                  break;
               }
               case 2:
               {
                  coordonneeDeX--;
                  break;
               }
               case 3:
               {
                  coordonneeDeY++;
                  break;
               }
               case 4:
               {
                  coordonneeDeY--;
                  break;
               }
            }
            nombreDeplacements++;


            if (coordonneeDeX == limiteDroite)
            {
               murDroite = 1;
               coordonneeDeX--;
               nombreDeplacements++;
            }

            if (0x == limiteGauche)
            {
               murGauche = 1;
               coordonneeDeX++;
               nombreDeplacements++;
            }
            if (coordonneeDeY == limiteHaut)
            {
               murHaut = 1;
               coordonneeDeY--;
               nombreDeplacements++;
            }
            if (coordonneeDeY == limiteBas)
            {
               murBas = 1;
               coordonneeDeY++;
               nombreDeplacements++;
            }  
         }                
      }
      moyenneDeplacement = (nombreDeplacementsTotal / nbExperiences);

      cout << "Matrice: " << setw(LARGEUR_COLONNE_1) 
           << tailleMatrice << " X " << tailleMatrice << " est de : "
           << setw(LARGEUR_COLONNE_2) << moyenneDeplacement << endl;
      moyenneDeplacement = 0;
      nombreDeplacementsTotal = 0;
   }
   
   cout << "Appuyez sur une touche pour continuer...";
   cin.get();
   return EXIT_SUCCESS;
}