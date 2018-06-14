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

using namespace std;


sf::VertexArray LVL6Triangle(int PartieFigure, Referentiel CtrRay)
{
	double PI3 = M_PI / 3;
	sf::Color CouleurO = LVL6ConversionCouleur(PartieFigure);
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
	V1.position = sf::Vector2f(X0f + static_cast <float> (CtrRay.Rayon * cos((PartieFigure -1) * PI3 )),
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



sf::Color LVL6ConversionCouleur(int PartieFigure)
{
	sf::Color couleur(255, 255, 255, 255);
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
		couleur = sf::Color(255, 0,0,170); // Rouge
		break;
	case 2:
		couleur = sf::Color(150, 0, 200, 170);//violet
		break;
	case 3:
		couleur = sf::Color(225, 225, 0, 170);//jaune pas trop claire
		break;
	case 4:
		couleur = sf::Color(25, 200, 25, 170); // beau vert
		break;
	case 5:
		couleur = sf::Color(0,0,255,170); //Bleu
		break;
	case 6:
		couleur = sf::Color(250, 120, 0, 170); // orange
		break;

	default:
		break;
	}
	return couleur;
}



int LVL6PositionSouris(sf::Window &window, Referentiel CtrRay, int Xs, int Ys)
{

	int PartieCiblee = 0;
	double rayonD = sqrt((Xs - CtrRay.X0)*(Xs - CtrRay.X0) + (Ys - CtrRay.Y0)*(Ys - CtrRay.Y0));
	double RayonD = static_cast <double> (CtrRay.Rayon);

	if (RayonD <= rayonD)
	{
		PartieCiblee = 0;
	}
	else
	{
		double Angle = 3 / M_PI * AngleSouris(window, CtrRay);
		if (0 <= Angle && Angle < 1)
		{
			PartieCiblee = 1;
		}
		else if (1 <= Angle && Angle < 2)
		{
			PartieCiblee = 2;
		}
		else if (2 <= Angle && Angle < 3)
		{
			PartieCiblee = 3;
		}
		else if (3 <= Angle && Angle < 4)
		{
			PartieCiblee = 4;
		}
		else if (4 <= Angle && Angle < 5)
		{
			PartieCiblee = 5;
		}
		else if (5 <= Angle && Angle < 6)
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
