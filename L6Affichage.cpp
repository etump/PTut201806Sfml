//PROJET TUTORE: Le "SUPER-MARIN".
//Application Multim�dia, construite avec la biblioth�que SFML.
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
	bool FinClic = true;			//d�tection de fin de clic

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			Recommencer = false;
			//lancera la fermeture de la fen�tre et message de fin de partie
			break;

		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (FinClic == true) // Si d�but du clic
				{
					Partie.P0 = LVL6PositionSouris(window, CtrRay1, event.mouseButton.x, event.mouseButton.y);

				}
				FinClic = false;
				//Recuperation de la partie instantan�e choisie
				Partie.P1 = LVL6PositionSouris(window, CtrRay1, event.mouseButton.x, event.mouseButton.y);
			}
			break;

		case sf::Event::MouseButtonReleased:
			if (Partie.P0 == Partie.P1)
			{
				Partie.Choix = Partie.P0;
				//Si le joueur n'a pas chang� la souris de couleur, on sauvegarde sa d�cision.
			}
			Partie.P0 = 0;
			Partie.P1 = 0;
			FinClic = true;

			if (Partie.Choix != 0)
				//Si le clic est valid� => Relachement Leftclic + d�but et fin du clic dans une m�me zone
			{
				CouleursJ[PositionTableau] = Partie.Choix;

			}

			break;

		default:
			break;
		}

	}
}