#ifndef GAME_H
#define GAME_H

#include "Field.h"


const int FILED_SIZE_IN_TILES  = 9;//16;
const int NUMBER_OF_MINES      = 10;//40;


enum GameState
{
    GAME,
    DEFEAT,
    VICTORY
};


class Game
{
public:

                        Game();
                        ~Game();
    void                run();

private:

    GameState           gameState;
    Field*              field;
    int                 fieldRenderOffset;
    sf::RenderWindow    window;

    sf::Font            font;
    sf::Text            minesCountText;
    sf::Text            gameOverText;
    sf::Text            victoryText;

    void                initField();
    void                initWindow();
    void                initText();
    void                processEvents();
    void                update();
    void                render();
    void                createText(sf::Text& text,
                                   const unsigned& charSize,
                                   const sf::Color& color,
                                   const std::string& string,
                                   const sf::Text::Style& style,
                                   const sf::Vector2f& position = sf::Vector2f(0.f, 0.f)
                                   );





};


#endif // GAME_H
