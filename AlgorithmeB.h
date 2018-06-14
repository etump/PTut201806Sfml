//Algorithmes des séquences de couleurs
//par ROLDAN Margot

#define _USE_MATH_DEFINES

#include <vector>
#include <iostream>
#include <cmath>

#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include "FctGlobalesB.h"
#include "AllStrcB.h"

using namespace std;


void sEquence(Difficulte w, vector<int>& CouleursOrdi);


void AffichageCouleurs(sf::RenderWindow &window, Referentiel CtrRay, std::vector<int> CouleursOrdi, Difficulte duNiveau, sf::Sound sound[]);

bool Comparaison(int CoulO, int CoulJ);





