//Elements
#define _USE_MATH_DEFINES
#include <iostream>
#include<iostream>
#include<cmath>
#include<vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "AllFctB.h"

using namespace std;

//ATTENTION utiliser des pointeurs pour sf::Window



//retourne 0 <= X < 2*PI

double AngleSouris(sf::Window& window,Referentiel CtrRay)
{
	sf::Vector2i localPosition = sf::Mouse::getPosition(window); //Recuperation Position souris
	double LPX = localPosition.x - CtrRay.X0; //Recentrage
	double LPY = localPosition.y - CtrRay.Y0;
	double AnglePartie = 0;
	if (LPX == 0)
	{
		if (LPY < 0)
			{AnglePartie = -M_PI / 2;}
		if (LPY > 0)
			{AnglePartie = M_PI / 2;}
	}
	else
		{AnglePartie = atan(LPY / LPX);}

	if (LPX < 0)
		{AnglePartie = AnglePartie + M_PI;}

	while (AnglePartie < 0)
		{AnglePartie = AnglePartie + 2 * M_PI;}
	while (AnglePartie >= 2 * M_PI)
		{AnglePartie = AnglePartie - 2 * M_PI;}

	return AnglePartie;
}


void Requilibrage(Referentiel &CtrRay, sf::Window& window)
{
	CtrRay.X0 = window.getSize().x / 2;
	CtrRay.Y0 = window.getSize().y / 2;
	if (CtrRay.X0 < CtrRay.Y0)
	{
		CtrRay.Rayon = static_cast <int> (2./3 * CtrRay.X0);
	}
	else
	{
		CtrRay.Rayon = static_cast <int> (2. / 3 * CtrRay.Y0);
	}

}



//A changer pour conditions de temps et de figure
void NiveauAugmente(std::vector<int> & TableauOrdi, std::vector<int> & TableauJoueur, Difficulte &Niveau, int &PositionTableau)
{
	//On augmente le nombre de couleurs à faire deviner
	Niveau.NbreColorSeq += 1;
	TableauOrdi.push_back(0);
	TableauJoueur.push_back(0);

	//On réinitialise la variable de lecture des tableaux
	PositionTableau = 0;
}

