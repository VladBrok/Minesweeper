#ifndef GAME_H
#define GAME_H

#include "Field.h"


const int FILED_SIZE_IN_TILES  = 16;
const int NUMBER_OF_MINES      = 40;


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
    sf::Text            restartGameText;

    void                initField();
    void                initWindow();
    void                initText();
    void                processEvents();
    void                render();
    void                updateMouseInput(const sf::Mouse::Button pressedButton);
    void                updateGameState(const Tile lastOpenedTile);
    void                updateMinesCountText();
    void                createText(sf::Text& text,
                                   const unsigned& charSize,
                                   const sf::Color& color,
                                   const std::string& string,
                                   const sf::Text::Style& style,
                                   const sf::Vector2f& position = sf::Vector2f(0.f, 0.f)
                                   );
};


#endif // GAME_H
