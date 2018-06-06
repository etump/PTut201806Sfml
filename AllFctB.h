/////////////////Nouvelles structures de Variables
struct Referentiel
{
	int X0;
	int Y0;
	int Rayon;
};

struct Difficulte
{
	int Level;
	int NbreColorSeq;
	sf::Time TempsLimite;
};

struct PartImage
{
	int P0;
	int P1;
	int Choix;
};


/////////////////////// Generales //////////////////////



double AngleSouris(sf::Window& window,Referentiel CtrRay);
void Requilibrage(Referentiel &CtrRay, sf::Window& window);		//Recentre la figure au milieu de la fenetre + redimensionnement 2/3 du plus court côté
void NiveauAugmente(std::vector<int> & TableauOrdi, std::vector<int> & TableauJoueur, Difficulte &Niveau, int &PositionTableau);


//////////////////// Level 1 ////////////////////////
sf::Color Lvl1ConversionCouleur(int PartieFigure);
sf::VertexArray Lvl1Triangle(int PartieFigure, Referentiel CtrRay);
int Lvl1PositionSouris(sf::Window &window, Referentiel CtrRay, int Xs, int Ys);

void DrawLVL1(sf::RenderWindow &window, Referentiel CtrRay1, int PartieClic);
void EventsLVL1(sf::Event& event, bool &Recommencer, PartImage &Partie, sf::Window &window, Referentiel CtrRay1, bool &FinClic);


////////////////// Level 2 ///////////////////////////
sf::Color Lvl2ConversionCouleur(int PartieFigure);
sf::VertexArray Lvl2Triangle(int PartieFigure, Referentiel CtrRay);
int Lvl2PositionSouris(sf::Window &window, Referentiel CtrRay, int Xs, int Ys);

