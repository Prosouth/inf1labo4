/*
 -----------------------------------------------------------------------------------
 Laboratoire : INF01
 Fichier     : Labo_04_blanc_saez.cpp
 Auteur(s)   : Julien Blanc et Sébastien Saez
 Date        : 19.11.2015

 But         : <à compléter>

 Remarque(s) : <à compléter>

 Compilateur : MinGW-g++ 4.8.1
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
   int compteurRobot;
   int nombreDeplacements;
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
      murBas = false;
      murDroite = false;
      murGauche = false;
      murHaut = false;
      nombreDeplacements = 0;
      limite_droite = limite_haut = tailleMatrice / 2;
      limite_gauche = limite_bas = tailleMatrice / -2;

      for (int i = 0; i < nbExperiences; i++)
      {
         Ox = (tailleMatrice / 2);
         Oy = (tailleMatrice / 2);

         while (!murBas and !murHaut and !murDroite and !murGauche)
         {
            randDeplacement = rand() % (RANDOM_MAX - RANDOM_MIN + 1) + RANDOM_MIN;

            switch (randDeplacement)
            {
               case 1:
               {
                  Ox++;
                  compteurRobot++;
                  break;
               }
               case 2:
               {
                  Ox--;
                  compteurRobot++;
                  break;
               }
               case 3:
               {
                  Oy++;
                  compteurRobot++;
                  break;
               }
               case 4:
               {
                  Oy++;
                  compteurRobot++;
                  break;
               }
            }

            if (Ox == limite_droite)
            {
               murDroite = 1;
               Ox--;
               compteurRobot++;
            }

            if (Ox == limite_gauche)
            {
               murGauche = 1;
               Ox++;
               compteurRobot++;
            }
            if (Oy == limite_haut)
            {
               murHaut = 1;
               Oy--;
               compteurRobot++;
            }
            if (Oy == limite_bas)
            {
               murBas = 1;
               Oy++;
               compteurRobot++;
            }

         }
         
         nombreDeplacements += compteurRobot;
         
      }
      moyenneDeplacement = (nombreDeplacements / nbExperiences);

      cout << "Matrice: " << setw(LARGEUR_COLONNE_1) 
              << tailleMatrice << " X " << tailleMatrice << " est de : "
              << setw(LARGEUR_COLONNE_2) << moyenneDeplacement << endl;
   }
   return EXIT_SUCCESS;
}