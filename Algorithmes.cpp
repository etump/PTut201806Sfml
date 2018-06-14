//PROJET TUTORE: Le "SUPER-MARIN".
//Application Multimédia, construite avec la bibliothèque SFML.
//
//Algorithmes des séquences de couleurs
//par ROLDAN Margot, 06-2018

#define _USE_MATH_DEFINES

#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>

#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>

#include "FctGlobalesB.h"
#include "AllStrcB.h"
#include "L6B.h"

using namespace std;




void sEquence(Difficulte w, vector<int>& CouleursOrdi)
{
	int nombre_aleatoire = 0;
	srand(static_cast<int> (time(NULL))); // pour l'aléatoire

	cout << "pret?...";
	//system("cls");
	cout << w.NbreColorSeq << endl;

	//génération de la séquences de couleurs
	for (int k = 0; k < w.NbreColorSeq; k++)
	{
		cout << k << " couleur(s) placée(s)" << endl;
		nombre_aleatoire = 1 + rand() % (w.Level); //genère un nombre aléatoire de 0 à "Level".
		CouleursOrdi[k] = nombre_aleatoire;	//enregistre la sequence dans le tableau de question 

											/*										//affichage
											if (nombre_aleatoire == 1) { cout << "ROUGE" << endl; attendre(2); system("cls"); } //affiche couleur, attend 2sec et nettoie la fenetre
											if (nombre_aleatoire == 2) { cout << "MAGENTA" << endl; attendre(2); system("cls"); }
											if (nombre_aleatoire == 3) { cout << "CYAN" << endl; attendre(2); system("cls"); }
											if (nombre_aleatoire == 4) { cout << "VERT/GREEN" << endl; attendre(2); system("cls"); }
											if (nombre_aleatoire == 5) { cout << "BLUE" << endl; attendre(2); system("cls"); }
											if (nombre_aleatoire == 6) { cout << "YELLOW" << endl; attendre(2); system("cls"); }
											attendre(1);
											*/
	}
}


void AffichageCouleurs(sf::RenderWindow &window, Referentiel CtrRay, std::vector<int> CouleursOrdi, Difficulte duNiveau, sf::Sound sound[])
{
	double CouleurFond = 0;
	sf::Clock Horloge;
	sf::Time TPS = sf::seconds(static_cast<float> (0.9));
	double PI3 = M_PI / 3;

	float X0f = static_cast <float> (CtrRay.X0);
	float Y0f = static_cast <float> (CtrRay.Y0);


	for (int i = 0; i < CouleursOrdi.size(); i++)
	{
		sf::Color CouleurO = LVL6ConversionCouleur(CouleursOrdi[i]);
		CouleurO.a = 255;


		// création d'un nouveau vertex
		sf::Vertex V0;
		// on change sa position
		V0.position = sf::Vector2f(X0f, Y0f);
		// on change sa couleur
		V0.color = CouleurO;

		// création d'un nouveau vertex
		sf::Vertex V1;
		// on change sa position
		V1.position = sf::Vector2f(X0f + static_cast <float> (CtrRay.Rayon * cos(CouleursOrdi[i] * PI3 - PI3)),
			Y0f + static_cast<float>(CtrRay.Rayon * sin(CouleursOrdi[i] * PI3 - PI3)));
		// on change sa couleur
		V1.color = CouleurO;

		// création d'un nouveau vertex
		sf::Vertex V2;
		// on change sa position
		V2.position = sf::Vector2f(X0f + static_cast <float> (CtrRay.Rayon * cos(CouleursOrdi[i] * PI3)),
			Y0f + static_cast <float> (CtrRay.Rayon * sin(CouleursOrdi[i] * PI3)));
		// on change sa couleur
		V2.color = CouleurO;


		sf::VertexArray triangle(sf::Triangles, 3);
		triangle[0] = V0;
		triangle[1] = V1;
		triangle[2] = V2;

		cout << "couleur" << i << " : "  << CouleursOrdi[i] << endl;


		Horloge.restart();
		while (Horloge.getElapsedTime() <= sf::seconds(static_cast<float> (0.1))) //Noir de pause
		{
			CouleurFond++;
			window.clear(sf::Color::Black);
		//	dessinFond(window, CouleurFond);
			DrawLVL6(window, CtrRay, 0);
			window.display();

		}

		sound[CouleursOrdi[i]-1].play();

		Horloge.restart();
		while (Horloge.getElapsedTime() <= TPS)
		{
			CouleurFond++;
			window.clear(sf::Color::Black);
		//	dessinFond(window, CouleurFond);
			DrawLVL6(window, CtrRay, 0);
			window.draw(triangle);
			window.display();

		}


	}
}


bool Comparaison(int CoulO, int CoulJ)
{

	bool Gagnant; //True = gagné, false = erreur => arrêt ensuite de la partie	
	if (CoulJ == CoulO) { Gagnant = true; }
	else { Gagnant = false; }


	return Gagnant;
}