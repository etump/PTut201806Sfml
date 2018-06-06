#define _USE_MATH_DEFINES
#include <iostream>
#include<cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "AllFctB.h"

using namespace std;




/////////////// Level 1 //////// (hexagone = 6 triangles)
sf::Color Lvl1ConversionCouleur(int PartieFigure)
{
	sf::Color couleur(255,255,255,255);
	switch (PartieFigure)
	{
		/*
		sf::Color::Black;
		sf::Color::White;
		sf::Color::Red;
		sf::Color::Green;
		sf::Color::Blue;
		sf::Color::Yellow;
		sf::Color::Magenta;
		sf::Color::Cyan;
		*/

	case 1:
		couleur = sf::Color::Red;
		break;
	case 2:
		couleur = sf::Color::Green;
		break;
	case 3:
		couleur = sf::Color::Blue;
		break;
	case 4:
		couleur = sf::Color::Yellow;
		break;
	case 5:
		couleur = sf::Color::Cyan;
		break;
	case 6:
		couleur = sf::Color::Magenta;
		break;

	default:
		break;
	}
	return couleur;
}

sf::VertexArray Lvl1Triangle(int PartieFigure, Referentiel CtrRay)
{
	double PI3 = M_PI / 3;
	sf::Color CouleurO = Lvl1ConversionCouleur(PartieFigure);
	float X0f = static_cast <float> (CtrRay.X0);
	float Y0f = static_cast <float> (CtrRay.Y0);

	// création d'un nouveau vertex
	sf::Vertex V0;
	// on change sa position
	V0.position = sf::Vector2f(X0f, Y0f);
	// on change sa couleur
	V0.color = CouleurO;

	// création d'un nouveau vertex
	sf::Vertex V1;
	// on change sa position
	V1.position = sf::Vector2f(X0f + static_cast <float> (CtrRay.Rayon * cos(PartieFigure * PI3 - PI3)),
		Y0f + static_cast<float>(CtrRay.Rayon * sin(PartieFigure * PI3 - PI3)));
	// on change sa couleur
	V1.color = CouleurO;

	// création d'un nouveau vertex
	sf::Vertex V2;
	// on change sa position
	V2.position = sf::Vector2f(X0f + static_cast <float> (CtrRay.Rayon * cos(PartieFigure * PI3)),
		Y0f + static_cast <float> (CtrRay.Rayon * sin(PartieFigure * PI3)));
	// on change sa couleur
	V2.color = CouleurO;


	sf::VertexArray triangle(sf::Triangles, 3);
	triangle[0] = V0;
	triangle[1] = V1;
	triangle[2] = V2;

	return triangle;
}

int Lvl1PositionSouris(sf::Window &window, Referentiel CtrRay, int Xs, int Ys)
{

	int PartieCiblee = 0;
	double rayonD = sqrt( (Xs - CtrRay.X0)*(Xs - CtrRay.X0) + (Ys - CtrRay.Y0)*(Ys - CtrRay.Y0) );
	double RayonD = static_cast <double> (CtrRay.Rayon);
	
	if (RayonD <= rayonD)
	{
		PartieCiblee = 0;
	}
	else
	{
		double Angle = 3 / M_PI  * AngleSouris(window, CtrRay);
		if (0 <= Angle && Angle < 1)
		{
			PartieCiblee = 1;
		}
		else if (1 <= Angle && Angle < 2)
		{
			PartieCiblee = 2;
		}
		else if (2 <= Angle && Angle < 3 )
		{
			PartieCiblee = 3;
		}
		else if (3 <= Angle && Angle < 4 )
		{
			PartieCiblee = 4;
		}
		else if (4  <= Angle && Angle < 5 )
		{
			PartieCiblee = 5;
		}
		else if (5 <= Angle && Angle < 6 )
		{
			PartieCiblee = 6;
		}
		else
		{
			cout << "erreur angle impossible" << endl << Angle << endl;
		}
	}
	return PartieCiblee;
}


void DrawLVL1(sf::RenderWindow &window, Referentiel CtrRay1, int PartieClic)
{

	if (PartieClic != 0)
	{
		sf::VertexArray Surbrillance = Lvl1Triangle(PartieClic, CtrRay1);
		Surbrillance[0].color.a = 170;
		Surbrillance[1].color.a = 170;
		Surbrillance[2].color.a = 170;
		window.draw(Surbrillance);
	}


	for (int i = 1; i < 7; i++)
	{
		if (i != PartieClic)
		{
			window.draw(Lvl1Triangle(i, CtrRay1));
		}
	}

	return;
}


//Boucle d'évenement: -> Partie appuyée par le joueur
void EventsLVL1(sf::Event &event ,bool &Recommencer ,PartImage& Partie, sf::Window &window, Referentiel CtrRay1, bool &FinClic)
{
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
					Partie.P0 = Lvl1PositionSouris(window, CtrRay1, event.mouseButton.x, event.mouseButton.y);
					FinClic = false;
				}
				//Recuperation de la partie instantanée choisie
				Partie.P1 = Lvl1PositionSouris(window, CtrRay1, event.mouseButton.x, event.mouseButton.y);
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
			break;

		default:
			break;
		}

	}
}