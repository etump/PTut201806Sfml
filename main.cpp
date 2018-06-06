#include <iostream>
#include <cmath>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>


#include "AllFctB.h"
using namespace std;

int main(int argc, char* argv[]) 
	{
////////////////////////////////////////////VARIABLES/////////////////////////////////////////////

	bool ATwaDJwai = false;			//tour du joueur
	bool Recommencer = true;		//fin du jeu si "false"
	bool FinClic = true;			//d�tection de fin de clic
	int PosTab = 0;					//Position dans les tableaux de s�quence de couleurs


	Difficulte duNiveau;			// Difficult� du niveau (augmente avec les manches)
	 duNiveau.Level = 1;					//Quelle image
	 duNiveau.NbreColorSeq = 3;				//Nbre de couleurs � retrouver
	 duNiveau.TempsLimite = sf::seconds(3); //Temps de r�ponse limite


	Referentiel CtrRay1;			// R�f�rentiel pour centrer l'image 
									//(affichage en 2/3 du c�t� le plus court de la fen�tre)
	CtrRay1.X0 = 400;						//Milieu de la largeur
	CtrRay1.Y0 = 300;						//Milieu de la hauteur
	CtrRay1.Rayon = 100;					//Rayon de la figure ( => 1/3 c�t� court)
	

	PartImage Partie;				//Choix de la couleur du joueur
	Partie.P0 = 0;							//Partie de la figure au d�but du clic
	Partie.P1 = 0;							//Partie de la figure � cet instant
	Partie.Choix = 0;						//D�cision


	vector<int> CouleursO(duNiveau.NbreColorSeq, 0);	//Tableau dynamique pour les couleurs Ordinateur
	vector<int> CouleursJ(duNiveau.NbreColorSeq, 0);	//Tableau dynamique pour les couleurs Joueur
	

	//Fen�tre cr��e
	sf::RenderWindow window(sf::VideoMode(800, 600), "Le SUPER-MARIN arrive en magasin!");

	

//Son de lancement de jeu	
	sf::SoundBuffer Buffer;
	if (!Buffer.loadFromFile("lavalidation.ogg"))
		return -1;
	sf::Sound Sound;
	Sound.setBuffer(Buffer);
	Sound.play();
	
	
	
	sf::Music music;
	if (!music.openFromFile("lavalidation.wav"))
		return -1; // erreur
	music.play();
	

	
	



/////////////////////////BOUCLE FENETRE = CONTINUE TANT QUE LA FENETRE EST OUVERTE///////////////////////////
		while (window.isOpen())
		{	

			Requilibrage(CtrRay1, window);		

	//Evenement pour savoir ce que fait le joueur
	sf::Event event;







//////////////////// Switch � mettre ici //////////////////

			if(ATwaDJwai == false)
			{ 
			//// Ordinateur affiche la sequence de couleur	
			

				ATwaDJwai = true;
				cout << "Fin de la s�quence de la manche" << endl << "A toi de jouer!" << endl;
//Son � ajouter ici				
			}


			else
			{
			///// Joueur peut selectionner les couleurs (modification de "Partie" en fonction des d�cisions du joueur
				EventsLVL1(event, Recommencer, Partie, window, CtrRay1, FinClic);
			



				if (FinClic == true && Partie.Choix != 0) 
				//Si le clic est valid� => Relachement Leftclic + d�but et fin du clic dans une m�me zone
				{
					CouleursJ[PosTab] = Partie.Choix;
				}
				
				
				
				if (PosTab >= duNiveau.NbreColorSeq)
				//Si le joueur arrive � la derni�re couleur trouv�e
				{
					NiveauAugmente(CouleursO, CouleursJ, duNiveau, PosTab);
					ATwaDJwai = false;
				}
			}



///////////////////////// jusqu'ici (le switch)			
			



			///////////////////Afficher regles du jeu //tant que K =0 



			// effacement de la fen�tre en noir//////////////////////////////////////////
			window.clear(sf::Color::Black);


			// c'est ici qu'on dessine tout////////////////////////////////////////////
			// window.draw(...);
			DrawLVL1(window, CtrRay1, Partie.P1);

			
			// fin de la frame courante, affichage /////////////////////////////////////////
			window.display();








			if (Recommencer != true)
			{
				cout << endl << "Fin du jeu" << endl;
				window.close();
			}
		}

		return 0;
	}