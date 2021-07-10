#include "Field.h"
#include <ctime>
#include <cassert>


Field::Field(const int fieldSize, const int numberOfMines)
    : FIELD_SIZE(fieldSize), NUMBER_OF_MINES(numberOfMines)
{
    assert(numberOfMines <= fieldSize * fieldSize);

    srand(time(nullptr));

    initTiles();
    initField();
    initFieldTexture();
}


void Field::setPosition(const int x, const int y)
{
    fieldSprite.setPosition(x, y);
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

    return openedTile;
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


void Field::render(sf::RenderTarget& target)
{
    target.draw(fieldSprite);
}



void Field::initTiles()
{
    tilesTexture.loadFromFile("Textures/tiles.jpg");
    tilesSprite.setTexture(tilesTexture);
}


void Field::initField()
{
    field.resize(FIELD_SIZE, std::vector<Tile>(FIELD_SIZE));
    setFlags.resize(FIELD_SIZE, std::vector<bool>(FIELD_SIZE, false));
    numberOfFlags = 0;


    // Placing mines at random positions
    std::vector<sf::Vector2i> minePositions(NUMBER_OF_MINES);
    sf::Vector2i minePos;
    for (int i = 0; i < NUMBER_OF_MINES; ++i)
    {
        // Making sure that 2 or more mines won't spawn at the same position
        do
        {
            minePos = sf::Vector2i(rand() % FIELD_SIZE, rand() % FIELD_SIZE);
        }while(std::find(minePositions.begin(), minePositions.end(), minePos) != minePositions.end());

        field[minePos.x][minePos.y] = MINE;
        minePositions[i] = minePos;
    }


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