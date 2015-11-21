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

int main() {

   // Constantes
   const int TAILLE_MATRICE_MAX = 50;
   const short RANDOM_MIN = 1;
   const short RANDOM_MAX = 4;
   const int NB_EXP_MIN = 1000;
   const int NB_EXP_MAX = 10000;
   const int LARGEUR_COLONNE_1 = 3;
   const int LARGEUR_COLONNE_2 = 25;

   // Variables
   int nbExperiences;
   int tailleMatrice = 2;
   int Ox;
   int Oy;
   bool murHaut;
   bool murBas;
   bool murDroite;
   bool murGauche;
   int randDeplacement;
   int nombreDeplacements;
   int nombreDeplacementsTotal;
   int limite_bas;
   int limite_haut;
   int limite_gauche;
   int limite_droite;
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
         cout << "La valeur que vous avez entree n'est pas comprise dans l'intervale"
                 << endl;
      }
   }
   while ((nbExperiences < NB_EXP_MIN or nbExperiences > NB_EXP_MAX) and cin.fail() == false);

   for (tailleMatrice; tailleMatrice <= TAILLE_MATRICE_MAX; tailleMatrice += 2)
   {
      limite_droite = limite_haut = tailleMatrice / 2;
      limite_gauche = limite_bas = tailleMatrice / -2;

      for (int i = 0; i < nbExperiences; i++)
      {
         Ox = 0;
         Oy = 0;
         murBas = false;
         murDroite = false;
         murGauche = false;
         murHaut = false;
         nombreDeplacementsTotal += nombreDeplacements;
         nombreDeplacements = 0;
         moyenneDeplacement = 0;

         while (!murBas || !murHaut || !murDroite || !murGauche)
         {
            randDeplacement = rand() % (RANDOM_MAX - RANDOM_MIN + 1) + RANDOM_MIN;

            switch (randDeplacement)
            {
               case 1:
               {
                  Ox++;
                  nombreDeplacements++;
                  break;
               }
               case 2:
               {
                  Ox--;
                  nombreDeplacements++;
                  break;
               }
               case 3:
               {
                  Oy++;
                  nombreDeplacements++;
                  break;
               }
               case 4:
               {
                  Oy--;
                  nombreDeplacements++;
                  break;
               }
            }

            if (Ox == limite_droite)
            {
               murDroite = 1;
               Ox--;
               nombreDeplacements++;
            }

            if (Ox == limite_gauche)
            {
               murGauche = 1;
               Ox++;
               nombreDeplacements++;
            }
            if (Oy == limite_haut)
            {
               murHaut = 1;
               Oy--;
               nombreDeplacements++;
            }
            if (Oy == limite_bas)
            {
               murBas = 1;
               Oy++;
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
   return EXIT_SUCCESS;
}