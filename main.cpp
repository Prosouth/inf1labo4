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

      if ((nbExperiences < 1000 or nbExperiences > 10000) and cin.fail() == false)
      {
         cout << "La valeur que vous avez entree n'est pas comprise dans l'intervale"
                 << endl;
      }
   }
   while ((nbExperiences < 1000 or nbExperiences > 10000) and cin.fail() == false);

   for (tailleMatrice; tailleMatrice <= TAILLE_MATRICE_MAX; tailleMatrice += 2)
   {

      for (int i = 0; i < nbExperiences; i++)
      {
         Ox = (tailleMatrice / 2);
         Oy = (tailleMatrice / 2);

         do
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

            if (Ox == tailleMatrice)
            {
               murDroite = 1;
               Ox--;
               compteurRobot++;
            }

            if (Ox == 0)
            {
               murGauche = 1;
               Ox++;
               compteurRobot++;
            }
            if (Oy == tailleMatrice)
            {
               murHaut = 1;
               Oy--;
               compteurRobot++;
            }
            if (Oy == 0)
            {
               murBas = 1;
               Oy++;
               compteurRobot++;
            }

         }
         while (!murBas and !murHaut and !murDroite and !murGauche);
         nombreDeplacements += compteurRobot;
      }
      moyenneDeplacement = (nombreDeplacements / nbExperiences);

      cout << "La moyenne de nombre de deplacements du robot pour une matrice de taille "
              << tailleMatrice << " X " << tailleMatrice << " est de : "
              << moyenneDeplacement << endl;
   }
   return EXIT_SUCCESS;
}