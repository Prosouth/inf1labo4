/*
 -----------------------------------------------------------------------------------
 Laboratoire : INF01
 Fichier     : Labo_04.cpp
 Auteur(s)   : Julien Blanc et Sébastien Saez
 Date        : 19.11.2015

 But         : Le but de ce programme et de déterminer expérimentalement la relation
 *             entre la taille d'une matrice de taille NxN (N de 2 à 50 compris,
 *             pair et de type entier) et le nombre de déplacements moyens 
 *             effectués par un pointeur robot se déplaçant aléatoirement d'une 
 *             unité dans les 4 directions possibles (haut, bas, gauche, droite). 
 *             Ceci afin de pouvoir définir la fonction exprimant la relation entre 
 *             L et N, tel que L = f(N).

 Remarque(s) : - À chaque fois que le robot heurte l'un des bord de la matrice, il
 *               effectue un déplacement d'une unité dans la direction opposée à 
 *               celle qu'il suivait avant la collision
 * 
 *             - Le programme fourni exactement le même résultat à chaque nouvelle
 *               simulation indépendamment du compilateur utilisé
 * 
 *             - La saisie utilisateur est entièrement contrôlée et les erreurs
 *               détectées lors  de la saisie. La demande de saisie est effectuée
 *               tant que celle-ci n'est pas correcte. Un message d'information
 *               est affiché à l'utilisateur en cas de saisie incorrecte 

 Compilateur : MinGW-g++ 4.8.1
 -----------------------------------------------------------------------------------
 */
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <limits>

using namespace std;

// Constantes
const int TAILLE_MATRICE_MAX = 50; //taille maximale de la matrice
const unsigned short RANDOM_MIN = 1;   //valeur minimum du random
const unsigned short RANDOM_MAX = 4;   //valeur maximum du random
const unsigned int NB_EXP_MIN = 1000;  //nombre minimum d'expériences possible
const unsigned int NB_EXP_MAX = 10000; //nombre maximum d'expériences possible
const unsigned int MOITIER_SUPERIEURE_MATRICE = 2; /*divise la matrice en deux et  
                                                     définit sa partie supérieure*/
const int MOITIER_INFERIEURE_MATRICE = -2;         /*divise la matrice en deux et
                                                    définit sa partie inférieure*/

int main() {

   // Variables
   unsigned int nbExperiences;   //saisie utilisateur
   unsigned int nombreDeplacements = 0;
   int randDeplacement;  //valeur aléatoire générée par le déplacement
   int limiteHaut;   //limite supérieure de la matrice
   int limiteDroite; //limite droite de la matrice
   int limiteBas;    //limite inférieure de la matrice
   int limiteGauche; //limite gauche de la matrice
   int coordonneeDeX;   
   int coordonneeDeY;
   bool murHaut;  //Détermine si le mur haut a été touché
   bool murBas;   //Déterminie si le mur bas a été touché
   bool murDroite;   //Détermine si le mur droite a été touché
   bool murGauche;   //Détermine si le mur gauche a été touché
   bool testNbUser = false;   //Détermine si la saisie utilisateur est correcte
   double moyenneDeplacement; //
   double nombreDeplacementsTotal = 0; /* Stock le nombre de déplacement total 
                                          pour chaque itération */
   
   //Boucle de contrôle de la saisie de l'utilisateur
   do
   {
      cout << "Veuillez entrer le nombre d'experimentations a effectuer. "
              "(Nombre compris entre 1000 et 10000):" << endl << endl;
      cin >> nbExperiences;
      cout << endl;
      
      /* Détection et correction de l'état du flux en cas de saisie par 
         l'utilisateur d'une valeur autre qu'un nombre */  
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
      }
      
      /* Test la saisie d'une valeur différente que celle expectée,
       affiche un message d'information à l'utilisateur. */
      if ((nbExperiences < NB_EXP_MIN or nbExperiences > NB_EXP_MAX)
          and cin.fail() == false)
      {
         cout << "La valeur que vous avez entree n'est pas correcte."
                 " Veuillez recommencer." << endl << endl;
      }
      //Si la saisie est correcte, sort de la boucle.
      else
      {
         testNbUser = true;
      }
   }
   //La demande de saisie est répétée tant que celle-ci n'est pas correcte
   while (!testNbUser);
 
   // affichage de la métadonnée du tableau
   cout << "Taille de la matrice" << setw(36) 
        << "Moyenne du nombre de deplacements" << endl;
   cout << setw(53) << "du robot (nombre de sauts)" << endl;
   cout << setfill('-') << setw(56) << "-" << setfill(' ') << endl << endl;

   /* Boucle permettant d'augmenter la taille de la matrice de 2 en partant de
      sa taille minimale (2) jusqu'à la taille maximale définie en constante */
   for (int tailleMatrice = 2 ; tailleMatrice <= TAILLE_MATRICE_MAX; tailleMatrice += 2)
   {
      // initialisation des limites de la matrice
      limiteDroite = limiteHaut = tailleMatrice / MOITIER_SUPERIEURE_MATRICE;
      limiteGauche = limiteBas = tailleMatrice / MOITIER_INFERIEURE_MATRICE;
      
      /* Boucle permettant d'effectuer le nombre d'expériences désirées par
         l'utilisateur */
      for (unsigned int i = 0; i < nbExperiences; i++)
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
         
         /* Boucle déplaçant aléatoirement le compteur robot dans chaque direction
            tant qu'il n'aura pas heurté les 4 murs de la matrice au moins une fois */
         while (!murBas or !murHaut or !murDroite or !murGauche)
         {
            //initilisation du déplacement aléatoire du robot
            randDeplacement = rand() % (RANDOM_MAX - RANDOM_MIN + 1) + RANDOM_MIN;
            
            //déplacement du robot en fonction du nombre aléatoire obtenu
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

            /* Conditions traitants les actions à effectuer lorsque le robot 
               atteind le bord de la grille */
            if (coordonneeDeX == limiteDroite)
            {
               murDroite = 1;
               coordonneeDeX--;
               nombreDeplacements++;
            }

            if (coordonneeDeX == limiteGauche)
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
      
      /* calcule de la moyenne du nombre de déplacement effectué par le robot dans
         chaque matrice */
      moyenneDeplacement = (nombreDeplacementsTotal / nbExperiences);
      
      //affichage du tableau des résultats des tests
      cout << "Matrice: " << setw(3) 
           << tailleMatrice << " X " << setw(2) << tailleMatrice
           << setw(25) << fixed << setprecision(3) 
           << moyenneDeplacement << endl;
      moyenneDeplacement = 0;
      nombreDeplacementsTotal = 0;
   }
   
   cout << endl;
   cout << "Appuyez sur une touche pour continuer...";
   cin.get();
   return EXIT_SUCCESS;
}