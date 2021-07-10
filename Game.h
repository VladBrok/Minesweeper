#ifndef GAME_H
#define GAME_H

#include "Field.h"


class Game
{
public:

                        Game();
                        ~Game();
    void                run();

private:

    Field*              field;
    int                 fieldRenderOffset;
    int                 fieldSizeInTiles;
    int                 numberOfMines;
    sf::RenderWindow    window;

    void                initWindow();
    void                initField();
    void                processEvents();
    void                update();
    void                render();

};


#endif // GAME_H
