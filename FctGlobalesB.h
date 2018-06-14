//PROJET TUTORE: Le "SUPER-MARIN".
//Application Multimédia, construite avec la bibliothèque SFML.
//
//
//par DAVENEL Titouan, 06-2018

#define USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <vector>

#include <SFML\System.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

#include "AllStrcB.h"



void InitTabV(std::vector<int> &TabDynam);

double AngleSouris(sf::Window& window, Referentiel CtrRay);

void Requilibrage(Referentiel &CtrRay, sf::Window& window);		//Recentre la figure au milieu de la fenetre + redimensionnement 2/3 du plus court côté

void NiveauAugmente(std::vector<int> & TableauOrdi, std::vector<int> & TableauJoueur, Difficulte &Niveau, int &PositionTableau);

void dessinFond(sf::RenderWindow &window, double& k1);
