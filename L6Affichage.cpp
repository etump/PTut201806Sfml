//PROJET TUTORE: Le "SUPER-MARIN".
//Application Multimédia, construite avec la bibliothèque SFML.
//
//
//par DAVENEL Titouan, 06-2018

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





void DrawLVL6(sf::RenderWindow &window, Referentiel CtrRay1, int PartieClic)
{

	if (PartieClic != 0)
	{
		sf::VertexArray Surbrillance = LVL6Triangle(PartieClic, CtrRay1);
		Surbrillance[0].color.a = 255;
		Surbrillance[1].color.a = 255;
		Surbrillance[2].color.a = 255;
		window.draw(Surbrillance);
	}


	for (int i = 1; i < 7; i++)
	{
		if (i != PartieClic)
		{
			window.draw(LVL6Triangle(i, CtrRay1));
		}
	}

	return;
}


void EventsLVL6(sf::Event &event, bool &Recommencer, PartImage& Partie, sf::Window &window, Referentiel CtrRay1, int PositionTableau, std::vector<int> & CouleursJ)
{
	bool FinClic = true;			//détection de fin de clic

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			Recommencer = false;
			//lancera la fermeture de la fenêtre et message de fin de partie
			break;

		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (FinClic == true) // Si début du clic
				{
					Partie.P0 = LVL6PositionSouris(window, CtrRay1, event.mouseButton.x, event.mouseButton.y);

				}
				FinClic = false;
				//Recuperation de la partie instantanée choisie
				Partie.P1 = LVL6PositionSouris(window, CtrRay1, event.mouseButton.x, event.mouseButton.y);
			}
			break;

		case sf::Event::MouseButtonReleased:
			if (Partie.P0 == Partie.P1)
			{
				Partie.Choix = Partie.P0;
				//Si le joueur n'a pas changé la souris de couleur, on sauvegarde sa décision.
			}
			Partie.P0 = 0;
			Partie.P1 = 0;
			FinClic = true;

			if (Partie.Choix != 0)
				//Si le clic est validé => Relachement Leftclic + début et fin du clic dans une même zone
			{
				CouleursJ[PositionTableau] = Partie.Choix;

			}

			break;

		default:
			break;
		}

	}
}