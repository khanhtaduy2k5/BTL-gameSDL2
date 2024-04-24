
#include "SDL_utils.h"
#include <iostream>
#include <SDL_mixer.h>

Mix_Chunk* eat_cherry=loadSound("eatcherry.wav");
Mix_Chunk* eat_apple=loadSound("eatapple.wav");
Mix_Chunk* eat_pineapple=loadSound("eatpineapple.wav");
Mix_Chunk* eat_lemon= loadSound("eatlemon.wav");
Mix_Chunk* eat_carrot=loadSound("eatcarrot.wav");




Snake::Snake(Game& _game, Position start)
    : head(new SnakeNode(start)), tail(head), game(_game), cherry(0)
{
    game.snakeMoveTo(start);
}

Snake::~Snake()
{
    for (SnakeNode *p = tail; p != nullptr;)
    {
        SnakeNode *nextNode = p->next;
        delete p;
        p = nextNode;
    }
    Mix_FreeChunk(eat_cherry);
    Mix_FreeChunk(eat_apple);
    Mix_FreeChunk(eat_pineapple);
    Mix_FreeChunk(eat_lemon);
    Mix_FreeChunk(eat_carrot);
}

vector<Position> Snake::getPositions() const
{
    vector<Position> res;
    for (SnakeNode* p = tail; p != nullptr; p = p->next)
        res.push_back(p->position);
    return res;
}

void Snake::growAtFront(Position newPosition)
{
    SnakeNode *newHead = new SnakeNode(newPosition, nullptr);
    head->next = newHead;
    head = newHead;
}

void Snake::slideTo(Position newPosition)
{
    if (tail->next == nullptr)
    {
        tail->position = newPosition;
    }
    else
    {
        SnakeNode *oldTailNode = tail;
        tail = tail->next;
        oldTailNode->next = nullptr;
        oldTailNode->position = newPosition;
        head->next = oldTailNode;
        head = oldTailNode;
    }
}

void Snake::eatCherry()
{
    cherry++;
    Mix_PlayChannel(-1,eat_cherry,0);

}

void Snake::eatApple()
{
    cherry-- ;
    Mix_PlayChannel(-1,eat_apple,0);
}

void Snake::eatPineApple()
{
    cherry+=2 ;
    Mix_PlayChannel(-1,eat_pineapple,0);
}

void Snake::eatLemon()
{
    cherry++;
    Mix_PlayChannel(-1,eat_lemon,0);
}

void Snake::eatCarrot()
{
    cherry+=3;
    Mix_PlayChannel(-1,eat_carrot,0);
}


void Snake::move(Direction direction)
{
    Position newPosition = head->position.move(direction);
    game.snakeMoveTo(newPosition);
    if (game.isGameOver())
        return;
    if (cherry > 0)
    {
        cherry--;
        growAtFront(newPosition);
    }
    else{
        game.snakeLeave(tail->position);
        slideTo(newPosition);
    }
}

int Snake::getNumCherry()
{
    return cherry;
}

SnakeNode* Snake::getHead()
{
    return head;
}

SnakeNode* Snake::getTail()
{
    return tail;
}


