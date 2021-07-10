#ifndef GAME_H
#define GAME_H

#include "Field.h"


class Game
{
public:

                        Game();
    void                run();

private:

    sf::RenderWindow    window;
    Field               field;

    void                processEvents();
    void                update();
    void                render();

};


#endif // GAME_H
