#include "Game.h"
#include <sstream>
#include <iostream>


Game::Game()
{
    gameState = GAME;
    initField();
    initWindow();
    initText();
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
    window.setFramerateLimit(30);
}


void Game::initText()
{
    font.loadFromFile("Fonts/PixellettersFull.ttf");

    minesCountText.setFont(font);
    minesCountText.setCharacterSize(25);
    minesCountText.setColor(sf::Color::White);
    minesCountText.setPosition(
        GRID_SIZE * fieldRenderOffset,
        GRID_SIZE / 2
    );
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
            // Reacting on pressed mouse button
        case sf::Event::MouseButtonPressed:
            {
                if (gameState == GAME)
                {
                    // Open tile
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        // Checking if we opened a tile with mine
                        if (field->openTile(mousePosGrid.x, mousePosGrid.y) == MINE)
                        {
                            gameState = DEFEAT;
                        };
                    }
                    // Set or remove flag in tile
                    else if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        field->changeFlagStateAtTile(mousePosGrid.x, mousePosGrid.y);
                    }
                }
            }
        }
    }
}


void Game::update()
{
    std::stringstream msg;
    msg << "Mines marked: " << 
           field->getNumberOfFlags() << "/" << numberOfMines
           << '\n';
    minesCountText.setString(msg.str());
}


void Game::render()
{
    window.clear();

    field->render(window);
    window.draw(minesCountText);

    window.display();
}
