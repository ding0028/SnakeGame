#ifndef RENDERER_H
#define RENDERER_H
#include <memory>
#include <vector>
#include "SDL.h"
#include "snake.h"

class Renderer {
 public:
     // constructor / desctructor
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();
  // typical behaviour methods
  void Render(const std::vector<std::shared_ptr<Snake>> &snakes, Food const &food);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif