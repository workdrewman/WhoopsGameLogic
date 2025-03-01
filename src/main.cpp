#include "game_logic/logic_controller.hpp"
#include <iostream> 

using namespace std;

int main() {
  //auto game_controller = std::make_shared<game_board::Controller>();

  logic::LogicController* controller = new logic::LogicController();
  controller->startGame();

  return 0;
}

