/// logic_chip.hpp
#ifndef GAME_BOARD_CHIP_LOGIC_HPP
#define GAME_BOARD_CHIP_LOGIC_HPP

#include <vector>
#include <string>
class LogicTerminal;

using namespace std;

namespace logic {
    class LogicChip {
        public:
            LogicChip();
            int lastChip;

            int waitForChip(LogicTerminal* Terminal);
    };
}

#endif // GAME_BOARD_CHIP_LOGIC_HPP