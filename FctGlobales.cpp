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




double AngleSouris(sf::Window& window, Referentiel CtrRay)
{
	sf::Vector2i localPosition = sf::Mouse::getPosition(window); //Recuperation Position souris
	double LPX = localPosition.x - CtrRay.X0; //Recentrage
	double LPY = localPosition.y - CtrRay.Y0;
	double AnglePartie = 0;
	if (LPX == 0)
	{
		if (LPY < 0)
		{
			AnglePartie = - M_PI / 2;
		}
		if (LPY > 0)
		{
			AnglePartie = M_PI / 2;
		}
	}
	else
	{
		AnglePartie = atan(LPY / LPX);
	}

	if (LPX < 0)
	{
		AnglePartie = AnglePartie + M_PI;
	}

	while (AnglePartie < 0)
	{
		AnglePartie = AnglePartie + 2 * M_PI;
	}
	while (AnglePartie >= 2 * M_PI)
	{
		AnglePartie = AnglePartie - 2 * M_PI;
	}

	return AnglePartie;
}


void Requilibrage(Referentiel &CtrRay, sf::Window& window)
{
	CtrRay.X0 = window.getSize().x / 2;
	CtrRay.Y0 = window.getSize().y / 2;
	if (CtrRay.X0 < CtrRay.Y0)
	{
		CtrRay.Rayon = static_cast <int> (2. / 3 * CtrRay.X0);
	}
	else
	{
		CtrRay.Rayon = static_cast <int> (2. / 3 * CtrRay.Y0);
	}

}


void InitTabV(std::vector<int> &TabDynam)
{
	for (int i = 0; i < TabDynam.size(); i++)
	{
		TabDynam[i] = 0;
	}
}


void NiveauAugmente(std::vector<int> & TableauOrdi, std::vector<int> & TableauJoueur, Difficulte &Niveau, int &PositionTableau)
{
	//On augmente le nombre de couleurs à faire deviner
	Niveau.NbreColorSeq += 1;


	TableauOrdi.push_back(0);
	TableauJoueur.push_back(0);

	//On réinitialise la variable de lecture des tableaux et le tableau du joueur
	PositionTableau = 0;
	InitTabV(TableauJoueur);
}


void dessinFond(sf::RenderWindow &window, double& k1)
{
	double k2;
	double k3;
	k1 = (k1 + 10000);
	k2 = k1 + 17000000;
	k3 = k1 + 8500000;
	if (k1 > 23000000)
	{
		k1 = k1 - 23000000;
	}
	if (k2 > 23000000)
	{
		k2 = k2 - 23000000;
	}
	if (k3 > 23000000)
	{
		k3 = k3 - 23000000;
	}


	int l1 = static_cast<int> (k1 / 100000);
	int l2 = static_cast<int> (k2 / 100000);
	int l3 = static_cast<int> (k3 / 100000);



	float Xm = static_cast<float> (window.getSize().x);
	float Ym = static_cast<float> (window.getSize().y);


	// création d'un nouveau vertex
	sf::Vertex V0;
	// on change sa position
	V0.position = sf::Vector2f(1, 1);
	// on change sa couleur
	V0.color = sf::Color(l1, l2, l3, 255);

	// création d'un nouveau vertex
	sf::Vertex V1;
	// on change sa position
	V1.position = sf::Vector2f(Xm, 1),
		// on change sa couleur
		V1.color = sf::Color(l2, l3, l1, 255);

	// création d'un nouveau vertex
	sf::Vertex V2;
	// on change sa position
	V2.position = sf::Vector2f(1, Ym);
	// on change sa couleur
	V2.color = sf::Color(l3, l1, l2, 255);


	sf::VertexArray triangleH(sf::Triangles, 3);
	triangleH[0] = V0;
	triangleH[1] = V1;
	triangleH[2] = V2;

	// on change sa position
	V0.position = sf::Vector2f(Xm, Ym);
	// on change sa couleur
	V0.color = sf::Color(l1, l2, l3, 255);

	sf::VertexArray triangleB(sf::Triangles, 3);
	triangleB[0] = V0;
	triangleB[1] = V1;
	triangleB[2] = V2;


	window.draw(triangleB);
	window.draw(triangleH);
}