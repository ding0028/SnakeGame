# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

Additional features:
- A robot snake (obstacle) that grows in length and speed at reduced rate of player's snake 
- It will compete with the player for food but not consuming the food, i.e. stay nearby the food
- Additional food (blue) to reduce the speed of robot snake, green food to reduce the length of robot snake by half 
- Special food (violet) appears randomly that give additional score and reduce the length of player snake

# Rubic:
- The project uses Object Oriented Programming techniques. 
- Classes use appropriate access specifiers for class members. `snake.h, game.h organized into public, private accordingly `
- Class constructors utilize member initialization lists. `snake.h:22`
- Classes encapsulate behavior. `snake.h: usage of setter/getter `
- Classes follow an appropriate inheritance hierarchy. `snake.h: child PlayerSnake class `
- Overloaded functions allow the same function to operate on different parameters. `snake.h:60 `
- Derived class functions override virtual base class functions. `snake.h:92 `
- Templates generalize functions in the project. `snake.h:7 `
- The project makes use of references in function declarations. `renderer.cpp:41 `
- The project uses smart pointers instead of raw pointers `game.cpp:9-12 `




## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.
