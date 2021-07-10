//#include <SFML/Graphics.hpp>
//#include <time.h>
//#include <iostream>
//
///**
// *  FIXME:
// *  - make fixed number of mines, not random
// *  - use sf::RenderTexture for pre-loading tiles
// */
//
//using namespace sf;
//
//int main()
//{
//	// Генератор случайных чисел
//	srand(time(0));
//
//	RenderWindow app(VideoMode(400, 400), "Minesweeper");
//    app.setFramerateLimit(60);
//	
//	// Ширина клетки
//	int gridSize = 32;
//	int gridLogic[12][12];
//	int gridView[12][12]; 
//	
//	// Загрузка текстуры и создание спрайта
//	Texture t;
//	t.loadFromFile("Textures/tiles.jpg");
//	Sprite s(t);
//
//    int minesCount = 0;
//	for (int i = 1; i <= 10; i++)
//    {
//		for (int j = 1; j <= 10; j++)
//		{
//			gridView[i][j] = 10; // closed tile
//			if (rand() % 5 == 0)
//            {
//                gridLogic[i][j] = 9; // mine
//                ++minesCount;
//            }
//			else 
//            {
//                gridLogic[i][j] = 0; // empty
//            }
//		}
//    }
//    std::cout << minesCount << '\n';
//		
//	// Подсчет мин вокруг каждой клетки
//	for (int i = 1; i <= 10; i++)
//    {
//		for (int j = 1; j <= 10; j++)
//		{
//			int n = 0;
//			if (gridLogic[i][j] == 9) continue;
//			if (gridLogic[i + 1][j] == 9) n++;
//			if (gridLogic[i][j + 1] == 9) n++;
//			if (gridLogic[i - 1][j] == 9) n++;
//			if (gridLogic[i][j - 1] == 9) n++;
//			if (gridLogic[i + 1][j + 1] == 9) n++;
//			if (gridLogic[i - 1][j - 1] == 9) n++;
//			if (gridLogic[i - 1][j + 1] == 9) n++;
//			if (gridLogic[i + 1][j - 1] == 9) n++;
//			gridLogic[i][j] = n;
//		}
//    }
//
//	while (app.isOpen())
//	{
//		// Получаем координаты мышки относительно окна нашего приложения
//		Vector2i pos = Mouse::getPosition(app);
//		int x = pos.x / gridSize;
//		int y = pos.y / gridSize;
//
//		Event e;
//		while (app.pollEvent(e))
//		{
//			if (e.type == Event::Closed)
//				app.close();
//			
//			// Была нажата кнопка мыши…?
//			if (e.type == Event::MouseButtonPressed)
//            {
//				// Если это - левая кнопка мыши, то открываем клетку
//				if (e.key.code == Mouse::Left)
//                {
//                    gridView[x][y] = gridLogic[x][y];
//                }
//				// Если это – правая кнопка мыши, то отображаем флажок
//				else if (e.key.code == Mouse::Right) 
//                {
//                    gridView[x][y] = 11; // flag
//                }
//            }
//		}
//
//		// Устанавливаем белый фон
//		app.clear(Color::White);
//
//		for (int i = 1; i <= 10; i++)
//        {
//			for (int j = 1; j <= 10; j++)
//			{
//				if (gridView[x][y] == 9) 
//                {
//                    gridView[i][j] = gridLogic[i][j];
//                }
//				
//				// Вырезаем из спрайта нужный нам квадратик текстуры
//				s.setTextureRect(IntRect(gridView[i][j] * gridSize, 0, gridSize, gridSize));
//				
//				// Устанавливаем его заданную позицию…
//				s.setPosition(i * gridSize, j * gridSize);
//				
//				// … и отрисовываем
//				app.draw(s);
//			}
//        }
//		// Отображаем всю композицию на экране
//		app.display();
//	}
//
//	return 0;
//}

#include "Game.h"


int main()
{
    Game game;
    game.run();

    return 0;
}