#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing && !shrinking) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  }
  else if (shrinking){      
      shrinking = false; 
      int delta = body.size() - size;
      std::cout << "Body reduced by " << delta << std::endl;
      //erase the tail by the amount of delta
      if (delta > 1){
          while (delta != 0){
              body.erase(body.begin());
              delta--;
          }
      }
  }
  else {
    growing = false;
    size += growthRate;
    std::cout << "Body grow " << size << std::endl;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
      std::cout << "Game Over " << std::endl;
    }
  }
}

//Set the body to grow and according to the define rate of speed
void Snake::GrowBody() { growing = true; speed += speedRate; }

//Set the body to shrink 
void Snake::ShrinkBody() { shrinking = true; }

//Set the body to shrink by amount
void Snake::ShrinkBody(const int amount) { 
    shrinking = true; 
    size -= amount; 
    if (size < 1) size = 1;
}

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}