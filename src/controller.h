#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:
     // typical behaviour methods
  void HandleInput(bool &running, std::shared_ptr<Snake> &snake) const;

  void ChangeDirection(std::shared_ptr<Snake> &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif