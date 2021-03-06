#include "StateLayer.h"
#include <iostream>
using namespace render;
using namespace state;
using namespace std;

StateLayer::StateLayer(sf::Vector2u tileSize, unsigned int width, unsigned int height, state::State* state){
    (*this).tileSize=tileSize;
    (*this).width=width;
    (*this).height=height;
    (*this).state=state;
    std::vector<int>* listePersonnageCoordX=new std::vector<int>();
    std::vector<int>* listePersonnageId=new std::vector<int>();
    std::vector<int>* listePersonnageCoordY=new std::vector<int>();
    (*this).listePersonnageCoordX=listePersonnageCoordX;
    (*this).listePersonnageCoordY=listePersonnageCoordY;
    (*this).listePersonnageId=listePersonnageId;
}

std::vector<int> StateLayer::getPlateauIdFromState (){
    std::vector<int> plateauId;
    Plateau* pPlateau=(*(*this).state).getPlateau();
    int res;
    int size = pPlateau->getSize();
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            res=((*pPlateau).getCase(j,i))->getType();
            plateauId.push_back(res-10);
        }
    }
    return plateauId;
}
std::vector<int> StateLayer::getPlateauId (){
    return (*this).plateauId;
}

state::State* StateLayer::getState (){
    return (*this).state;
}

void StateLayer::setState (state::State* state){
    (*this).state=state;
}

void StateLayer::windowExemple(){
    // on crée la fenêtre
    (*this).plateauId=(*this).getPlateauIdFromState();
    (*this).actListePersonnageId();
    (*this).actXFromState(); 
    (*this).actYFromState();
    sf::RenderWindow* window=new sf::RenderWindow(sf::VideoMode((*this).width*tileSize.x, (*this).height*tileSize.y), "ENSEA Emblem: The Four Seasons");
    this->window=window;
    Surface* map= new Surface();
    this->map=map;
    Personnages* personnages = new Personnages();
    this->personnages=personnages;
    map->load("res/cases.png", (*this).tileSize, (*this).plateauId, (*this).width, (*this).height);
    personnages->load("res/personnages.png", (*this).tileSize, (*this).listePersonnageCoordX, (*this).listePersonnageId, (*this).listePersonnageCoordY);
    while (window->isOpen()){
        // on gère les évènements
        sf::Event event;
        while (window->pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window->close();
        }
        // on dessine le niveau
        
        window->clear();
        window->draw(*map);
        window->draw(*personnages);
        
        window->display();
    }
}
sf::RenderWindow* StateLayer::getWindow(){
    return this->window;
}

void StateLayer::windowInit(){
    // on crée la fenêtre
    (*this).plateauId=(*this).getPlateauIdFromState();
    (*this).actListePersonnageId();
    (*this).actXFromState();
    (*this).actYFromState();
    if (!font.loadFromFile("res/god-of-war.ttf")){
        perror("failed to load font");
        exit(1);
    }
    this->font=font;
    sf::Text text;
    text.setFont(font); // font is a sf::Font
    text.setString("Victoire de ");
    text.setCharacterSize(50); // in pixels, not points!
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
    text.setPosition(2*tileSize.x,(this->state->getPlateau()->getSize()/2-1)*tileSize.y);
    this->textGameOver=text;
    sf::RenderWindow* window=new sf::RenderWindow(sf::VideoMode((*this).width*tileSize.x, (*this).height*tileSize.y), "ENSEA Emblem: The Four Seasons");
    this->window=window;
    Surface* map= new Surface();
    this->map=map;
    Personnages* personnages = new Personnages();
    this->personnages=personnages; 
    map->load("res/cases.png", (*this).tileSize, (*this).plateauId, (*this).width, (*this).height);
    personnages->load("res/personnages.png", (*this).tileSize, (*this).listePersonnageCoordX, (*this).listePersonnageId, (*this).listePersonnageCoordY);
                 
    window->clear();
    window->draw(*map);
    window->draw(*personnages);
    window->display();
}

void StateLayer::windowReset(){
    window->clear();
    window->display();
}

void StateLayer::windowCell(){
    (*this).plateauId=(*this).getPlateauIdFromState();
    map->load("res/cases.png", (*this).tileSize, (*this).plateauId, (*this).width, (*this).height);
    window->clear();
    window->draw(*map);
    window->draw(*personnages);
    window->display();
}


void StateLayer::windowPersonnages(){
    // on crée la fenêtre
    (*this).actListePersonnageId();
    (*this).actXFromState(); 
    (*this).actYFromState();
    personnages->load("res/personnages.png", (*this).tileSize, (*this).listePersonnageCoordX, (*this).listePersonnageId, (*this).listePersonnageCoordY);
    window->clear();
    window->draw(*map);
    window->draw(*personnages);
    window->display();
}

void StateLayer::windowGameOver(){
    // on crée la fenêtre
    (*this).actListePersonnageId();
    (*this).actXFromState(); 
    (*this).actYFromState();
    std::string stringGameOver("Victoire de ");
    stringGameOver.append(this->state->getWinner()->getNom());
    this->textGameOver.setString(stringGameOver);
    personnages->load("res/personnages.png", (*this).tileSize, (*this).listePersonnageCoordX, (*this).listePersonnageId, (*this).listePersonnageCoordY);
    window->clear();
    window->draw(*map);
    window->draw(*personnages);
    window->draw(this->textGameOver);
    window->display();
}

std::vector<int>* StateLayer::getListePersonnageId (){
    return (*this).listePersonnageId;
}

std::vector<int>*  StateLayer::getListeX (){
    return (*this).listePersonnageCoordX;
}
std::vector<int>*  StateLayer::getListeY (){
    return (*this).listePersonnageCoordY;
}

void StateLayer::actListePersonnageId (){
    std::vector<int> *listePersonnageId = new std::vector<int>; 
    Joueur* pJoueur1=(*(*this).state).getJoueurs()[0];
    Joueur* pJoueur2=(*(*this).state).getJoueurs()[1];
    int size = pJoueur1->getPersonnages().size();
    for(int i=0;i<size;i++){
        if(pJoueur1->getPersonnages()[i]->getAlive()==true){
            (*listePersonnageId).push_back((*((*pJoueur1).getPersonnages()[i])).getClasseId());
        }
    }
    size = pJoueur2->getPersonnages().size();
    for(int i=0;i<size;i++){
        if(pJoueur2->getPersonnages()[i]->getAlive()==true){
            (*listePersonnageId).push_back((*((*pJoueur2).getPersonnages()[i])).getClasseId());
        }
    }
    (*this).listePersonnageId=listePersonnageId;
    
}

void  StateLayer::actXFromState (){
    (*this).listePersonnageCoordX->clear();
    std::vector<int> *listePersonnageCoordX= new std::vector<int>; 
    Joueur* pJoueur1;
    Joueur* pJoueur2;
    pJoueur1=(*(*this).state).getJoueurs()[0];
    pJoueur2=(*(*this).state).getJoueurs()[1];
    int size = pJoueur1->getPersonnages().size();
    int x;
    int y;
    Personnage *ptPersonnages;
    Cell *ptCell;
    int i;
    std::vector<int> coords;
    for(i=0;i<size;i++){
        ptPersonnages=(*pJoueur1).getPersonnages()[i];
        if(ptPersonnages->getAlive()==true){
            ptCell=(*ptPersonnages).getCell();
            //std::cout<<"ptCoord="<<((*ptCell).getCoordonees())<<"\n";
            x=((*ptCell).getCoordonees())[0]; 
            (*listePersonnageCoordX).push_back(x);
        }
    }
    size = pJoueur2->getPersonnages().size();
    int j;
    for(j=0;j<size;j++){
        ptPersonnages=(*pJoueur2).getPersonnages()[j];
            if(ptPersonnages->getAlive()==true){
            ptCell=(*ptPersonnages).getCell();
            x=((*ptCell).getCoordonees())[0];
            (*listePersonnageCoordX).push_back(x);
        }
    }
    (*this).listePersonnageCoordX=listePersonnageCoordX;
    
}

void  StateLayer::actYFromState(){
    
    std::vector<int>* listePersonnageCoordY=new std::vector<int>; 
    std::vector<Joueur*> listeJoueurs;
    listeJoueurs=(*(*this).state).getJoueurs();
    Joueur* pJoueur1=listeJoueurs[0];
    Joueur* pJoueur2=listeJoueurs[1];
    int size = pJoueur1->getPersonnages().size();
    int y;
    Personnage *ptPersonnages;
    Cell *ptCell;
    int i;
    std::vector<int> coords;
    for(i=0;i<size;i++){
        ptPersonnages=(*pJoueur1).getPersonnages()[i];
        if(ptPersonnages->getAlive()==true){
            ptCell=(*ptPersonnages).getCell();
            y=((*ptCell).getCoordonees())[1];
            (*listePersonnageCoordY).push_back(y);
        }
    }
    size = pJoueur2->getPersonnages().size();
    for(i=0;i<size;i++){
        ptPersonnages=(*pJoueur2).getPersonnages()[i];
        if(ptPersonnages->getAlive()==true){
            ptCell=(*ptPersonnages).getCell();
            y=((*ptCell).getCoordonees())[1];
            (*listePersonnageCoordY).push_back(y);
        }
    }
    (*this).listePersonnageCoordY=listePersonnageCoordY;
    
}
/*
int main()
{
    // on crée la fenêtre
    sf::RenderWindow window(sf::VideoMode(512, 256), "Tilemap");

    // on définit le niveau à l'aide de numéro de tuiles
    const int level[] =
    {
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
        0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
        0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
    };

    // on crée la tilemap avec le niveau précédemment défini
    TileMap map;
    if (!map.load("tileset.png", sf::Vector2u(32, 32), level, 16, 8))
        return -1;

    // on fait tourner la boucle principale
    while (window.isOpen())
    {
        // on gère les évènements
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        // on dessine le niveau
        window.clear();
        window.draw(map);
        window.display();
    }

    return 0;
}
*/