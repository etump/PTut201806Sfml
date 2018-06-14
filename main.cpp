//PROJET TUTORE: Le "SUPER-MARIN".
//Application Multim�dia, construite avec la biblioth�que SFML.
//
//Programme principal
//par DAVENEL Titouan, 06-2018.


//le terme variable "globale" sera utilis� lorsqu'une variable a des valeurs diff�rentes selon les op�rations � effectuer.

#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

#include <SFML\System.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

#include "AllStrcB.h"
#include "FctGlobalesB.h"
#include "L6B.h"
#include "SonsB.h"
#include "AlgorithmeB.h"

using namespace std;




int main(int argc, char* argv[])
{


	sf::SoundBuffer Buffer;			//Buffer g�n�ral de Son
	sf::Sound Sound;				//Son g�n�ral



	if (!Buffer.loadFromFile("Julo.wav"))
	{
		fstream FluxError;
		FluxError.open("Error.txt", ios::out);
		FluxError << "erreur chargement son" << endl;
	}
	Sound.setBuffer(Buffer);
	Sound.play();

///////////////////////////////////////////////////VARIABLES/////////////////////////////////////////////

	bool ATwaDJwai = false;			//tour du joueur
	bool Recommencer = true;		//fin du jeu si "false"

	Difficulte duNiveau;			// Difficult� du niveau (augmente avec les manches)
	duNiveau.Level = 6;						// Nbre de couleurs dans la figure (6 ou 4)
	duNiveau.NbreColorSeq = 3;				//Nbre de couleurs � retrouver

	Referentiel CtrRay1;			// R�f�rentiel pour centrer l'image (affichage en 2/3 du c�t� le plus court de la fen�tre)
	CtrRay1.X0 = 400;						//Milieu de la largeur
	CtrRay1.Y0 = 300;						//Milieu de la hauteur
	CtrRay1.Rayon = 100;					//Rayon de la figure ( => 1/3 c�t� court)

	PartImage Partie;				//Choix de la couleur du joueur
	Partie.P0 = 0;							//Partie de la figure au d�but du clic
	Partie.P1 = 0;							//Partie de la figure � cet instant
	Partie.Choix = 0;						//D�cision


	vector<int> CouleursO(duNiveau.NbreColorSeq, 0);	//Tableau dynamique pour les couleurs Ordinateur
	vector<int> CouleursJ(duNiveau.NbreColorSeq, 0);	//Tableau dynamique pour les couleurs Joueur
	int PosTab = 0;					//Position dans les tableaux de s�quence de couleurs

	sf::SoundBuffer BuffNotesLVL6[6];	//Tableau contenant les sons de la figure, pr�charg�s
	sf::Sound NotesLVL6[6];				//Tableau contenant les sons de la figure, pr�charg�s

	double couleurdeFond = 0;			//Base pour la couleur du fond

	sf::Clock Horloge;			//Horloge de temps globale
	sf::Time Temps;					//Temps global



//////////Chargement des Notes ///////////////////
	if (!BuffNotesLVL6[0].loadFromFile("Xilo1.wav"))
		return -1;
	if (!BuffNotesLVL6[1].loadFromFile("Xilo2.wav"))
		return -1;
	if (!BuffNotesLVL6[2].loadFromFile("Xilo3.wav"))
		return -1;
	if (!BuffNotesLVL6[3].loadFromFile("Xilo4.wav"))
		return -1;
	if (!BuffNotesLVL6[4].loadFromFile("Xilo5.wav"))
		return -1;
	if (!BuffNotesLVL6[5].loadFromFile("Xilo6.wav"))
		return -1;

	for (int ii = 0; ii < 6; ii++)
	{
		NotesLVL6[ii].setBuffer(BuffNotesLVL6[ii]);

	}




//////////////////////////////////////////// LANCEMENT DE L'APPLICATION ////////////////////////////////////////////

	//Fen�tre cr��e
	sf::RenderWindow window(sf::VideoMode(800, 600), "Le SUPER-MARIN arrive en magasin!");


	window.clear(sf::Color::Black);
	window.display();	
	
	//Son de lancement de jeu	
	/*if (!Buffer.loadFromFile("lavalidation.wav"))
		return -1;
	Sound.setBuffer(Buffer);
	Sound.play();*/

	//_sleep(3);
	/*
	sf::Music music;
	if (!music.openFromFile("lavalidation.wav"))
	return -1; // erreur
	music.play();
	*/
		//Evenement pour savoir ce que fait le joueur
		sf::Event event;





	/////////////////////////BOUCLE FENETRE = CONTINUE TANT QUE LA FENETRE EST OUVERTE///////////////////////////
	while (window.isOpen())
	{

		Requilibrage(CtrRay1, window);



		// effacement de la fen�tre en noir//////////////////////////////////////////
	//	window.clear(sf::Color::Black);

//Couleurs "eteintes"
		//puis allum�e lorsque clic ou affichage

		//Texte + son chagement de manche



		if (ATwaDJwai == false)
		{
			/*if (!Buffer.loadFromFile("/Sons/ADE.wav"))
				return -1;
			Sound.setBuffer(Buffer);
			Sound.play();*/
			


			sEquence(duNiveau, CouleursO);



			AffichageCouleurs(window, CtrRay1, CouleursO, duNiveau, NotesLVL6);
			//// Ordinateur affiche la sequence de couleur	

			ATwaDJwai = true;
			cout << "Fin de la s�quence de la manche" << endl << "A toi de jouer!" << endl;
			//Son � ajouter ici				
		}


		else
		{
			///// Joueur peut selectionner les couleurs (modification de "Partie" en fonction des d�cisions du joueur
			EventsLVL6(event, Recommencer, Partie, window, CtrRay1, PosTab, CouleursJ);


			if (CouleursJ[PosTab] != 0)
			{
				if (Comparaison(CouleursO[PosTab], CouleursJ[PosTab]))
				{
					PosTab += 1;
				}
				else
				{
					if (!Buffer.loadFromFile("Julo.wav"))
					{
						fstream FluxError;
						FluxError.open("Error.txt", ios::out);
						FluxError << "erreur chargement son" << endl;
					}
					Sound.setBuffer(Buffer);
					Sound.play();
					cout << " PERDU " << endl;
					Recommencer = false;

				}
			}


			if (PosTab >= duNiveau.NbreColorSeq)
				//Si le joueur arrive � la derni�re couleur trouv�e
			{
				
				NiveauAugmente(CouleursO, CouleursJ, duNiveau, PosTab);
				if (!Buffer.loadFromFile("lavalidation.wav"))
				{
					fstream FluxError;
					FluxError.open("Error.txt", ios::out);
					FluxError << "erreur chargement son" << endl;
				}
				Sound.setBuffer(Buffer);
				Sound.play();
	


				ATwaDJwai = false;
			}
		}

			





		// effacement de la fen�tre en noir//////////////////////////////////////////
		window.clear(sf::Color::Black);


		// c'est ici qu'on dessine tout////////////////////////////////////////////
		// window.draw(...);
		dessinFond(window, couleurdeFond);

		DrawLVL6(window, CtrRay1, Partie.P1);

		// fin de la frame courante, affichage /////////////////////////////////////////
		window.display();








		if (Recommencer != true)
		{
			cout << endl << "Fin du jeu" << endl;
			window.close();
		}
	}


	int Banane;
	cin >> Banane;

	return 0;
}
