#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : engine(dev()),
    random_w(0, static_cast<int>(grid_width)),
    random_h(0, static_cast<int>(grid_height)) {
    std::shared_ptr<PlayerSnake> snake = std::make_shared<PlayerSnake>(grid_width, grid_height);
    std::shared_ptr<Snake> robot = std::make_shared<Snake>(grid_width, grid_height);

    _snakes.push_back(std::static_pointer_cast<Snake>(snake)); //_snakes[0]
    _snakes.push_back(robot); //_snakes[1]

    PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
    std::size_t target_frame_duration) {
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    bool running = true;

    while (running) {
        frame_start = SDL_GetTicks();

        // Input, Update, Render - the main game loop.
        controller.HandleInput(running, _snakes[0]);
        Update();

        //update direction of robot in the direction of food 
        float posXrelative = _snakes[1]->head_x - food.x;
        float posYrelative = _snakes[1]->head_y - food.y;
        if (posYrelative > posXrelative) {
            controller.ChangeDirection(_snakes[1], Snake::Direction::kUp,
                Snake::Direction::kDown);
        }
        else {
            controller.ChangeDirection(_snakes[1], Snake::Direction::kRight,
                Snake::Direction::kLeft);
        }        
        
        renderer.Render(_snakes, food);

        frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render cycle
        // takes.
        frame_count++;
        frame_duration = frame_end - frame_start;

        // After every second, update the window title.
        if (frame_end - title_timestamp >= 1000) {
            renderer.UpdateWindowTitle(score, frame_count);
            frame_count = 0;
            title_timestamp = frame_end;
        }

        // If the time for this frame is too small (i.e. frame_duration is
        // smaller than the target ms_per_frame), delay the loop to
        // achieve the correct frame rate.
        if (frame_duration < target_frame_duration) {
            SDL_Delay(target_frame_duration - frame_duration);
        }
    }
}

void Game::PlaceFood() {
    int x, y;
    //generate random food type when score is 3 and above
    if (GetScore() >= 3)
        food.type = rand() % 3;

    while (true) {
        x = random_w(engine);
        y = random_h(engine);
        // Check that the location is not occupied by a snake item before placing
        // food.
        if (!_snakes[0]->SnakeCell(x, y)) {
            food.x = x;
            food.y = y;
            std::cout << "Food placed " << std::endl;
            break;
        }

    }
}

void Game::Update() {

    if (!_snakes[0]->getAlive()) return;

    _snakes[0]->Update();
    _snakes[1]->Update();

    int new_x = static_cast<int>(_snakes[0]->head_x);
    int new_y = static_cast<int>(_snakes[0]->head_y);

    // Check if there's food over here
    if (food.x == new_x && food.y == new_y) {
        score++;
        std::cout << "Food consumed  " << std::endl;

        // Grow snake and adjust speed according to food type
        switch (food.type){
        case 1: _snakes[1]->vSetSize(_snakes[1]->getSize() / 2); _snakes[1]->ShrinkBody();  break; // green: reduce the size of robot
        case 2: _snakes[1]->vSetSpeed(_snakes[1]->getSpeed() / 2); break; //blue: reduce the speed of the robot
        case 3: _snakes[0]->ShrinkBody(1); break;
        default: break;
        }
        
        _snakes[0]->GrowBody();
        _snakes[1]->GrowBody();
        PlaceFood();
    }

    for (auto const &robot : _snakes[1]->body){
        // Check if any contact with robot
        if (robot.x == new_x && robot.y == new_y){
            _snakes[0]->vSetAlive(false);
            std::cout << "Game over  " << std::endl;
            return;
        }
    }

}


int Game::GetScore() const { return score; }
//int Game::GetSize() const { return snake->size; }