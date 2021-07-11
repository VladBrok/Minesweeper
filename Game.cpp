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
    fieldRenderOffset  = 2;
    field = new Field(FILED_SIZE_IN_TILES, NUMBER_OF_MINES);
    field->setPosition(GRID_SIZE * fieldRenderOffset, GRID_SIZE * fieldRenderOffset);
}


void Game::initWindow()
{
    window.create(
        sf::VideoMode(
            GRID_SIZE * (FILED_SIZE_IN_TILES + fieldRenderOffset * 2), 
            GRID_SIZE * (FILED_SIZE_IN_TILES + fieldRenderOffset * 2)
        ), 
        "Minesweeper", 
        sf::Style::Close
    );
    window.setFramerateLimit(30);
}


void Game::initText()
{
    font.loadFromFile("Fonts/PixellettersFull.ttf");

    // FIXME: Refactor
    minesCountText.setFont(font);
    minesCountText.setCharacterSize(25);
    minesCountText.setPosition(
        GRID_SIZE * fieldRenderOffset,
        GRID_SIZE / 2
    );

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setColor(sf::Color::Red);
    gameOverText.setString("GAME OVER");
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setPosition(
        window.getSize().x / 2 - gameOverText.getGlobalBounds().width / 2,
        window.getSize().y - gameOverText.getGlobalBounds().height - GRID_SIZE * 1.2f
    );

    victoryText.setFont(font);
    victoryText.setCharacterSize(50);
    victoryText.setColor(sf::Color::Green);
    victoryText.setString("YOU WON!");
    victoryText.setStyle(sf::Text::Bold);
    victoryText.setPosition(
        window.getSize().x / 2 - victoryText.getGlobalBounds().width / 2,
        window.getSize().y - victoryText.getGlobalBounds().height - GRID_SIZE * 1.2f
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

            // FIXME: Refactor
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
                            field->openAllTiles();
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
           field->getNumberOfFlags() << "/" << NUMBER_OF_MINES
           << '\n';
    minesCountText.setString(msg.str());

    if (field->getNumberOfOpenedTiles() + NUMBER_OF_MINES == 
        FILED_SIZE_IN_TILES * FILED_SIZE_IN_TILES &&
        gameState != DEFEAT)
    {
        gameState = VICTORY;
        field->openAllTiles();
    }
}


void Game::render()
{
    window.clear();

    field->render(window);
    window.draw(minesCountText);

    switch (gameState)
    {
    case DEFEAT:
        window.draw(gameOverText);
        break;
    case VICTORY:
        window.draw(victoryText);
        break;
    }

    window.display();
}
