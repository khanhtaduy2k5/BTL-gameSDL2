
#include <vector>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include "SDL_utils.h"
#include <SDL_mixer.h>


using namespace std;



int ranD = 0;

Game::Game(int _width, int _height)
    : width(_width), height(_height),
	  squares(_height, vector<CellType>(_width, CELL_EMPTY)),
      snake(*this, Position(_width/2, _height/2)),
      currentDirection(Direction::RIGHT),
      status(GAME_RUNNING),
      score(0)
{
	addCherry();
}

void Game::snakeMoveTo(Position pos)
{
    if(!pos.isInsideBox(0,0,width,height) || getCellType(pos) == CELL_OFF_BOARD || getCellType(pos) == CELL_SNAKE)
    {
            live--;
            if (live == 0) status = GAME_OVER;

    }

    else if (getCellType(pos) == CELL_CHERRY)
    {
        score++;
        snake.eatCherry();
        addCherry();
    }

    else if (getCellType(pos) == CELL_PINEAPPLE)
    {
        snake.eatPineApple();
        score += 2;
        addCherry();

    }

    else if (getCellType(pos) == CELL_APPLE)
    {
        snake.eatApple();
        score += 3;
        addCherry();
    }

    else if (getCellType(pos) == CELL_LEMON)
    {
        snake.eatLemon();
        live++;
        score += 4;
        addCherry();
    }

    else if (getCellType(pos) == CELL_CARROT)
    {
        snake.eatCarrot();
        score += 5;
        addCherry();
    }

    else
    {
        setCellType(pos,CELL_SNAKE);
    }
}

void Game::snakeLeave(Position position)
{
    setCellType(position,CELL_EMPTY);
}

void Game::processUserInput(Direction direction)
{
    inputQueue.push(direction);
}

bool Game::canChange(Direction current, Direction next) const
{
	if ((current == UP || current == DOWN) && (next == UP || next == DOWN))
    {
        return false;
	}
    if ((current == LEFT || current == RIGHT) && (next == LEFT || next == RIGHT))
    {
		return false;
	}
	return true;
}

void Game::nextStep()
{
	while (!inputQueue.empty())
    {
		Direction next = inputQueue.front();
		inputQueue.pop();
		if (canChange(currentDirection, next))
		{
			currentDirection = next;
			break;
		}
	}
	snake.move(currentDirection);
}

void Game::addCherry()
{
    do
    {
        Position randomPos;
        randomPos.x = rand() % width;
        randomPos.y = rand() % height;
        if (getCellType(randomPos) == CELL_EMPTY)
        {
            cherryPosition = randomPos;
            ranD = rand()% 5;
            std::cout<<ranD<<" ";
            switch(ranD)
            {
            case 0:
                setCellType(randomPos, CELL_APPLE);
                break;

            case 1:
                setCellType(randomPos, CELL_CHERRY);
                break;

            case 2:
                setCellType(randomPos, CELL_PINEAPPLE);
                break;

            case 3:
                setCellType(randomPos, CELL_LEMON);
                break;

            case 4:
                setCellType(randomPos, CELL_CARROT);
                break;

            }

            break;
        }
    }

    while (true);
}

void Game::setCellType(Position pos, CellType cellType)
{
    if(pos.isInsideBox(0,0,width,height))
    {
        squares[pos.y][pos.x] = cellType;
    }
}

CellType Game::getCellType(Position pos) const
{
	return pos.isInsideBox(0, 0, width, height) ? squares[pos.y][pos.x] : CELL_OFF_BOARD;
}

vector<Position> Game::getSnakePositions() const
{
    return snake.getPositions();
}

GameStatus Game::getGameStatus()
{
	return status;
}

int Game::getWidth()
{
	return width;
}

int Game::getHeight()
{
	return height;
}

Snake Game::getSnake()
{
	return snake;
}

Game::~Game()
{

}
