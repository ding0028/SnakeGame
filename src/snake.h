#ifndef SNAKE_H
#define SNAKE_H
#include <memory>
#include <vector>
#include "SDL.h"

typedef struct Food
{
    int x{ 0 };
    int y{ 0 };
    int type{ 0 };
} Food;


class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };
  enum SnakeType { player, robot };

  // constructor / desctructor
  Snake(int grid_width, int grid_height, float speedRate = 0.01f, int growthRate = 1)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2),
        speed(0.1f),
        size(1),
        growthRate(growthRate),
        speedRate(speedRate),
        growing(false),
        alive(true),
        shrinking(false),
        direction(Direction::kUp)  
       {        
           body.clear();  
  }
  

  // getters / setters
  void vSetAlive(const bool life) { alive = life;  }
  bool getAlive() const { return alive; }
  void vSetSpeed(const float speed){ if (speed <= 0) this->speed = 0.1f; else this->speed = speed; }
  float getSpeed() const { return speed; }
  void vSetSize(const int size){ if (size <= 0) this->size = 1; else this ->size = size; }
  float getSize() const { return size; }  
  void vChangeDirection(const Direction d) { direction = d; }
  Direction getDirection() const { return direction; }
  bool boShrinking() const { return shrinking; }

  //virtual function
  virtual SnakeType getType() const { return Snake::robot; }

  // typical behaviour methods
  void Update();
  void GrowBody();     
  bool SnakeCell(int x, int y);
  //overloaded function
  void ShrinkBody();
  void ShrinkBody(const int amount); 

  // miscellaneous
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  //private variables
  bool growing;
  bool alive;
  bool shrinking;
  int grid_width;
  int grid_height;  
  int size;
  int growthRate;
  float speedRate;
  float speed;  
  Direction direction = Direction::kUp;

};

//Derived class of Snake for Player to have special growth and speed 
class PlayerSnake :public Snake {
public:
    // constructor / desctructor
    PlayerSnake(int grid_width, int grid_height) : Snake(grid_width, grid_height, 0.015f, 1){}
    // getters / setters
    // virtual function
    virtual SnakeType getType() const { return Snake::player; }
private:
};

#endif