#include "Game.h"


Game::Game()
    : window(sf::VideoMode(400, 400), "Minesweeper", sf::Style::Close),
      field(9, 10)
{
    window.setFramerateLimit(60);
}


void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}


void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            {
                window.close();
                break;
            }
        case sf::Event::KeyPressed:
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                break;
            }
        }
    }
}


void Game::update()
{
    sf::Vector2i mousePosGrid(
        sf::Mouse::getPosition(window).x / GRID_SIZE, 
        sf::Mouse::getPosition(window).y / GRID_SIZE
    );

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        field.openTile(mousePosGrid.x, mousePosGrid.y);
    }
    else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        field.setFlagAtTile(mousePosGrid.x, mousePosGrid.y);
    }
}


void Game::render()
{
    window.clear();

    field.render(window);

    window.display();
}