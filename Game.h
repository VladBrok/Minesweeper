#ifndef GAME_H
#define GAME_H

#include "Field.h"


enum GameState
{
    GAME,
    VICTORY,
    DEFEAT
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
    int                 fieldSizeInTiles;
    int                 numberOfMines;
    sf::RenderWindow    window;

    sf::Font            font;
    sf::Text            minesCountText;
    sf::Text            victoryText;
    sf::Text            gameOverText;

    void                initField();
    void                initWindow();
    void                initText();
    void                processEvents();
    void                update();
    void                render();

};


#endif // GAME_H
