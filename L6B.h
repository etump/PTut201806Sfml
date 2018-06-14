//PROJET TUTORE: Le "SUPER-MARIN".
//Application Multimédia, construite avec la bibliothèque SFML.
//
//Header Fonctions du Niveau 6 Couleurs
//par DAVENEL Titouan, 06-2018














sf::Color LVL6ConversionCouleur(int PartieFigure);
sf::VertexArray LVL6Triangle(int PartieFigure, Referentiel CtrRay);
int LVL6PositionSouris(sf::Window &window, Referentiel CtrRay, int Xs, int Ys);




void EventsLVL6(sf::Event &event, bool &Recommencer, PartImage& Partie, sf::Window &window, Referentiel CtrRay1, int PositionTableau, std::vector<int> & CouleursJ);

void DrawLVL6(sf::RenderWindow &window, Referentiel CtrRay1, int PartieClic);





