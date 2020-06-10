#ifndef SNAKE_H
#define SNAKE_H
#include <memory>
#include <vector>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };
  enum SnakeType { player, robot };
  Snake(int grid_width, int grid_height, float speedRate = 0.01f, int growthRate = 1)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2),
        speed(0.1f),
        size(1),
        growthRate(growthRate),
        speedRate(speedRate)
       {}

  void Update();

  void GrowBody();
   

  bool SnakeCell(int x, int y);

  
  void vSetAlive(const bool life) { alive = life;  }
  bool getAlive() const { return alive; }

  void vSetSpeed(const float speed){ this->speed = speed; }
  float getSpeed() const { return speed; }
  void vSetSize(const int size){ this->size = size; }
  float getSize() const { return size; }
  virtual SnakeType getType() const { return Snake::robot; }
  void vChangeDirection(const Direction d) { direction = d; }
  Direction getDirection() const { return direction; }
  
  
  
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};

  int grid_width;
  int grid_height;

  float speed;
  int size;
  int growthRate;
  float speedRate;
  bool alive{ true };

  Direction direction = Direction::kUp;

};

class PlayerSnake :public Snake {
public:
    PlayerSnake(int grid_width, int grid_height) : Snake(grid_width, grid_height, 0.02f, 2){}

    virtual SnakeType getType() const { return Snake::player; }
private:
};

#endif