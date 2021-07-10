#ifndef FIELD_H
#define FIELD_H

#include <SFML/Graphics.hpp>
#include <vector>


const unsigned GRID_SIZE = 32;

enum Tile
{
    OPEN = -1,
    EMPTY,
    ONE, 
    TWO, 
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    MINE,
    CLOSED,
    FLAG
};


class Field
{
public:

                                        Field(const int fieldSize = 9, const int numberOfMines = 10);
    void                                setPosition(const int x, const int y);
    void                                openTile(const int row, const int column);
    void                                changeFlagStateAtTile(const int row, const int column);
    void                                render(sf::RenderTarget& target);

private:

    const int                           FIELD_SIZE;
    const int                           NUMBER_OF_MINES;
    sf::Texture                         tilesTexture;
    sf::RenderTexture                   fieldTexture;
    sf::Sprite                          tilesSprite;
    sf::Sprite                          fieldSprite;

    std::vector<std::vector<Tile>>      field;
    std::vector<std::vector<bool>>      setFlags;

    void                                initTiles();
    void                                initField();
    void                                initFieldTexture();
    void                                updateFieldTexture(const int row, const int column, const Tile newTile);
    const bool                          positionIsValid(const int row, const int column) const;

};


#endif // FIELD_H
