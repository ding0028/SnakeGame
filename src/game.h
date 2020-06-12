#ifndef GAME_H
#define GAME_H
#include <memory>
#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"


class Game {
 public:
  // constructor / desctructor
  Game(std::size_t grid_width, std::size_t grid_height);
  // typical behaviour methods
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  // miscellaneous
  int GetScore() const;


 private:

  std::vector<std::shared_ptr<Snake>> _snakes;
  std::vector<std::shared_ptr<Food<int>>>  _foods;
 
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood(const int fID = 0);
  void Update();
};

#endif