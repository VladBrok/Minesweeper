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
            GRID_SIZE * (FILED_SIZE_IN_TILES + fieldRenderOffset * 3)
        ), 
        "Minesweeper", 
        sf::Style::Close
    );
    window.setFramerateLimit(30);
}


void Game::initText()
{
    font.loadFromFile("Fonts/PixellettersFull.ttf");


    createText(minesCountText, 25, sf::Color::White, "", 
               sf::Text::Regular, 
               sf::Vector2f(
                   GRID_SIZE * fieldRenderOffset,
                   GRID_SIZE / 2
                   )
               );
    updateMinesCountText();
   
    createText(gameOverText, 50, sf::Color::Red, "GAME OVER", sf::Text::Bold);

    createText(victoryText, 50, sf::Color::Green, "YOU WON!", sf::Text::Bold);
 
    gameOverText.setPosition(
        window.getSize().x / 2 - gameOverText.getGlobalBounds().width / 2,
        window.getSize().y - gameOverText.getGlobalBounds().height - GRID_SIZE * 3.f
    );

    victoryText.setPosition(
        window.getSize().x / 2 - victoryText.getGlobalBounds().width / 2,
        window.getSize().y - victoryText.getGlobalBounds().height - GRID_SIZE * 3.f
    );   

    createText(restartGameText, 30, sf::Color::White, "Press space to start new game", 
               sf::Text::Regular, sf::Vector2f(GRID_SIZE / 2.f, 
                                               gameOverText.getGlobalBounds().top + 
                                               gameOverText.getGlobalBounds().height +
                                               GRID_SIZE
                                               )
               );
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
                else if (gameState != GAME && 
                         event.key.code == sf::Keyboard::Space)
                {
                    field->generateNewField();
                    gameState = GAME;
                }
                break;
            }
        case sf::Event::MouseButtonPressed:
            {
                if (gameState == GAME)
                {
                    updateMouseInput(event.mouseButton.button);
                }
            }
        }
        updateMinesCountText();
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
        window.draw(restartGameText);
        break;
    case VICTORY:
        window.draw(victoryText);
        window.draw(restartGameText);
        break;
    }

    window.display();
}


void Game::updateMouseInput(const sf::Mouse::Button pressedButton)
{
    sf::Vector2i mousePosGrid(
        sf::Mouse::getPosition(window).x / GRID_SIZE - fieldRenderOffset, 
        sf::Mouse::getPosition(window).y / GRID_SIZE - fieldRenderOffset
    );

    // Open tile and update game state
    if (pressedButton == sf::Mouse::Left)
    {
        updateGameState(field->openTile(mousePosGrid.x, mousePosGrid.y));
    }

    // Set or remove flag in tile
    else if (pressedButton == sf::Mouse::Right)
    {
        field->changeFlagStateAtTile(mousePosGrid.x, mousePosGrid.y);
        updateMinesCountText();
    }
}


void Game::updateGameState(const Tile lastOpenedTile)
{
    if (lastOpenedTile == MINE)
    {
        gameState = DEFEAT;
        field->openAllTiles();
    }

    else if (field->getNumberOfOpenedTiles() + NUMBER_OF_MINES == 
             FILED_SIZE_IN_TILES * FILED_SIZE_IN_TILES)
    {
        gameState = VICTORY;
        field->openAllTiles();
    }
}


void Game::updateMinesCountText()
{
    std::stringstream msg;
    msg << "Mines marked: " << 
           field->getNumberOfFlags() << "/" << NUMBER_OF_MINES
           << '\n';
    minesCountText.setString(msg.str());
}


void Game::createText(sf::Text& text,
                      const unsigned& charSize,
                      const sf::Color& color,
                      const std::string& string,
                      const sf::Text::Style& style,
                      const sf::Vector2f& position
                      )
{
    text.setFont(font);
    text.setCharacterSize(charSize);
    text.setColor(color);
    text.setString(string);
    text.setStyle(style);
    text.setPosition(position);
}
