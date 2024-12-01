#include "../src/game_logic/logic_controller.cpp"
#include <iostream> 

using namespace std;

int main() {
  //auto game_controller = std::make_shared<game_board::Controller>();

  logic_controller::startGame();

  return 0;
}
