#include "Personnages.h"
#include <iostream>
using namespace render;


bool Personnages::load (const std::string& tileset, sf::Vector2u tileSize, std::vector<int>* listePersonnageCoordX, std::vector<int>* listePersonnageId, std::vector<int>* listePersonnageCoordY)

{   
    std::size_t nbrPersonnages=(*listePersonnageId).size();
    static sf::Texture m_tileset;
    static sf::VertexArray m_vertices;
    // on charge la texture du tileset
    if (!m_tileset.loadFromFile(tileset))
        return false;

    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(nbrPersonnages * 4);
    // on remplit le tableau de vertex, avec un quad par tuile
    
    for (unsigned int i = 0; i < (int)nbrPersonnages; ++i){
        // on récupère le numéro de tuile courant
        int tileNumber = (*listePersonnageId)[i];

        // on récupère un pointeur vers le quad à définir dans le tableau de vertex
        sf::Vertex* quad = &m_vertices[i*4];
        int x=(*listePersonnageCoordX)[i];
        int y=(*listePersonnageCoordY)[i];
        // on définit ses quatre coins
        quad[0].position = sf::Vector2f(x * tileSize.x, y * tileSize.y);
        quad[1].position = sf::Vector2f((x + 1) * tileSize.x, y * tileSize.y);
        quad[2].position = sf::Vector2f((x + 1) * tileSize.x, (y + 1) * tileSize.y);
        quad[3].position = sf::Vector2f(x * tileSize.x, (y + 1) * tileSize.y);

        // on définit ses quatre coordonnées de texture
        quad[0].texCoords = sf::Vector2f(tileNumber * 128, 0);
        quad[1].texCoords = sf::Vector2f((tileNumber + 1) * 128, 0);
        quad[2].texCoords = sf::Vector2f((tileNumber + 1) * 128, 128);
        quad[3].texCoords = sf::Vector2f(tileNumber * 128,  128);
    }
    this->m_tileset=m_tileset;
    this->m_vertices=m_vertices;
    return true;
}



void Personnages::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    // on applique la transformation
    states.transform *= getTransform();

    // on applique la texture du tileset
    states.texture = &(this->m_tileset);

    // et on dessine enfin le tableau de vertex

    target.draw(this->m_vertices, states);
}

