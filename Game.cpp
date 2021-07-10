#include "Game.h"
#include <iostream>

Game::Game()
{
    initField();
    initWindow();
}


Game::~Game()
{
    delete field;
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


void Game::initField()
{
    fieldRenderOffset = 2;
    fieldSizeInTiles  = 9;
    numberOfMines     = 10;
    field = new Field(fieldSizeInTiles, numberOfMines);
    field->setPosition(GRID_SIZE * fieldRenderOffset, GRID_SIZE * fieldRenderOffset);
}


void Game::initWindow()
{
    window.create(
        sf::VideoMode(
            GRID_SIZE * (fieldSizeInTiles + fieldRenderOffset * 2), 
            GRID_SIZE * (fieldSizeInTiles + fieldRenderOffset * 2)
        ), 
        "Minesweeper", 
        sf::Style::Close
    );
    window.setFramerateLimit(60);
}


void Game::processEvents()
{
    sf::Vector2i mousePosGrid(
        sf::Mouse::getPosition(window).x / GRID_SIZE - fieldRenderOffset, 
        sf::Mouse::getPosition(window).y / GRID_SIZE - fieldRenderOffset
    );

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
        case sf::Event::MouseButtonPressed:
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                     field->openTile(mousePosGrid.x, mousePosGrid.y);
                }
                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    field->changeFlagStateAtTile(mousePosGrid.x, mousePosGrid.y);
                }
            }
        }
    }
}


void Game::update()
{
}


void Game::render()
{
    window.clear();

    field->render(window);

    window.display();
}
