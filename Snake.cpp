#include "SDL_utils.h"
//#include "Snake.h"
//#include "Game.h"
#include <iostream>
//#include "Audio.h"

Snake::Snake(Game& _game, Position start)
    : head(new SnakeNode(start)), tail(head), game(_game), cherry(0)
{
    game.snakeMoveTo(start);
}

Snake::~Snake(){
    for (SnakeNode *p = tail; p != nullptr;){
        SnakeNode *nextNode = p->next;
        delete p;
        p = nextNode;
    }
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

void Snake::slideTo(Position newPosition){
    if (tail->next == nullptr){
        tail->position = newPosition;
    }
    else{
        SnakeNode *oldTailNode = tail;
        tail = tail->next;
        oldTailNode->next = nullptr;
        oldTailNode->position = newPosition;
        head->next = oldTailNode;
        head = oldTailNode;
    }
}

void Snake::eatCherry(){
    cherry++;
     Audio eating_sound;
     eating_sound.loadSound("audio/eating.wav");
	//lose_sound.loadSound("res/audio/sound/lose.wav");
}

void Snake::move(Direction direction){
    Position newPosition = head->position.move(direction);
    game.snakeMoveTo(newPosition);
    if (game.isGameOver())
        return;
    if (cherry > 0){
        cherry--;
        growAtFront(newPosition);
    }
    else{
        game.snakeLeave(tail->position);
        slideTo(newPosition);
    }
}

int Snake::getNumCherry(){
    return cherry;
}

SnakeNode* Snake::getHead(){
    return head;
}

SnakeNode* Snake::getTail(){
    return tail;
}
