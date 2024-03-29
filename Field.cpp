#include "Field.h"
#include <ctime>
#include <cassert>
#include <queue>


Field::Field(const int fieldSize, const int numberOfMines)
    : FIELD_SIZE(fieldSize), NUMBER_OF_MINES(numberOfMines)
{
    assert(numberOfMines < fieldSize * fieldSize);

    srand(time(nullptr));
    
    initTilesTexture();
    generateNewField();
}


void Field::render(sf::RenderTarget& target)
{
    target.draw(fieldSprite);
}


void Field::setPosition(const int x, const int y)
{
    fieldSprite.setPosition(x, y);
}


void Field::generateNewField()
{
    initField();
    initFieldTexture();
}


const Tile Field::openTile(const int row, const int column)
{
    if (!positionIsValid(row, column) || 
        field[row][column] == OPEN ||
        setFlags[row][column]
        )
    {
        return CLOSED;
    }

    updateFieldTexture(row, column, field[row][column]);
    Tile openedTile = field[row][column];
    field[row][column] = OPEN;
    ++numberOfOpenedTiles;

    if (openedTile == EMPTY)
    {
        openEmptyTiles(row, column);
    }

    return openedTile;
}


void Field::openAllTiles()
{
    for (int i = 0; i < FIELD_SIZE; ++i)
    {
        for (int j = 0; j < FIELD_SIZE; ++j)
        {
            if (field[i][j] != OPEN)
            {
                updateFieldTexture(i, j, field[i][j]);
            }
        }
    }
}


void Field::changeFlagStateAtTile(const int row, const int column)
{
    if (!positionIsValid(row, column) || 
        field[row][column] == OPEN
        )
    {
        return;
    }

    if (!setFlags[row][column])
    {
        updateFieldTexture(row, column, FLAG);
        setFlags[row][column] = true;
        ++numberOfFlags;
    }
    else
    {
        updateFieldTexture(row, column, CLOSED);
        setFlags[row][column] = false;
        --numberOfFlags;
    }
}


const int Field::getNumberOfFlags() const
{
    return numberOfFlags;
}


const int Field::getNumberOfOpenedTiles() const
{
    return numberOfOpenedTiles;
}


void Field::initTilesTexture()
{
    tilesTexture.loadFromFile("Textures/tiles.jpg");
    tilesSprite.setTexture(tilesTexture);
}


void Field::initField()
{
    field.clear();
    setFlags.clear();
    field.resize(FIELD_SIZE, std::vector<Tile>(FIELD_SIZE, EMPTY));
    setFlags.resize(FIELD_SIZE, std::vector<bool>(FIELD_SIZE, false));
    numberOfFlags = 0;
    numberOfOpenedTiles = 0;

    placeMines();

    // Offsets to check all eight neighbouring tiles of specific tile
    int offsetsI[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int offsetsJ[8] = {0, 1, 1, 1, 0, -1, -1, -1};

    // Placing number of neighbouring mines for each tile
    for (int i = 0; i < FIELD_SIZE; ++i)
    {
        for (int j = 0; j < FIELD_SIZE; ++j)
        {
            if (field[i][j] != MINE)
            {
                int numberOfNeighbouringMines = 0;
                for (int k = 0; k < 8; ++k)
                {
                    int checkingRow = i + offsetsI[k];
                    int checkingCol = j + offsetsJ[k];

                    if (positionIsValid(checkingRow, checkingCol) &&
                        field[checkingRow][checkingCol] == MINE)
                    {
                        ++numberOfNeighbouringMines;
                    }
                }
                field[i][j] = static_cast<Tile>(numberOfNeighbouringMines);
            }
        }
    }
}


void Field::initFieldTexture()
{
    fieldTexture.create(FIELD_SIZE * GRID_SIZE, FIELD_SIZE * GRID_SIZE);
    fieldTexture.clear();

    tilesSprite.setTextureRect(sf::IntRect(CLOSED * GRID_SIZE, 0, GRID_SIZE, GRID_SIZE));

    // Making all tiles closed
    for (int i = 0; i < FIELD_SIZE; ++i)
    {
        for (int j = 0; j < FIELD_SIZE; ++j)
        {
            tilesSprite.setPosition(i * GRID_SIZE, j * GRID_SIZE);
            fieldTexture.draw(tilesSprite);
        }
    }

    fieldTexture.display();

    fieldSprite.setTexture(fieldTexture.getTexture());
}


void Field::placeMines()
{
    std::vector<int> fieldTileNumbers;
    for (int n = 0; n < FIELD_SIZE * FIELD_SIZE; ++n)
    {
        fieldTileNumbers.push_back(n);
    }

    std::random_shuffle(fieldTileNumbers.begin(), fieldTileNumbers.end());

    for (int i = 0; i < NUMBER_OF_MINES; ++i)
    {
        field[fieldTileNumbers[i] / FIELD_SIZE][fieldTileNumbers[i] % FIELD_SIZE] = MINE;
    }
}


void Field::updateFieldTexture(const int row, const int column, const Tile newTile)
{
    tilesSprite.setTextureRect(sf::IntRect(newTile * GRID_SIZE, 0, GRID_SIZE, GRID_SIZE));
    tilesSprite.setPosition(row * GRID_SIZE, column * GRID_SIZE);
    fieldTexture.draw(tilesSprite);
    fieldTexture.display();
}


const bool Field::positionIsValid(const int row, const int column) const
{
    return row >= 0 && row < FIELD_SIZE &&
           column >= 0 && column < FIELD_SIZE;
}


void Field::openEmptyTiles(const int start_row, const int start_col)
{
    std::queue<sf::Vector2i> positionsQueue;
    positionsQueue.push(sf::Vector2i(start_row, start_col));

    // Offsets to check all eight neighbouring tiles of specific tile
    int offsetsI[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int offsetsJ[8] = {0, 1, 1, 1, 0, -1, -1, -1};

    while (!positionsQueue.empty())
    {
        sf::Vector2i curPos = positionsQueue.front();
        for (int k = 0; k < 8; ++k)
        {
            sf::Vector2i checkPos(curPos.x + offsetsI[k], curPos.y + offsetsJ[k]);
            if (positionIsValid(checkPos.x, checkPos.y) &&
                field[checkPos.x][checkPos.y] != MINE && 
                field[checkPos.x][checkPos.y] != OPEN)
            {
                if (field[checkPos.x][checkPos.y] == EMPTY)
                {
                    positionsQueue.push(checkPos);
                }
                updateFieldTexture(checkPos.x, checkPos.y, field[checkPos.x][checkPos.y]);
                field[checkPos.x][checkPos.y] = OPEN;
                if (setFlags[checkPos.x][checkPos.y])
                {
                    setFlags[checkPos.x][checkPos.y] = false;
                    --numberOfFlags;
                }
                ++numberOfOpenedTiles;
            }
        }
        positionsQueue.pop();
    }
}