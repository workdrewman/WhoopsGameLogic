/// logic_player.hpp
#ifndef GAME_BOARD_LOGIC_PLAYER_HPP
#define GAME_BOARD_LOGIC_PLAYER_HPP

#include <vector>
#include <iostream>

using namespace std;

namespace logic {
    class LogicChip;
    class LogicBoard;
    class LogicTerminal;
    class LogicPlayer {
        private:
            int playerCount;
            vector<int> playerColors = {0, 0, 0, 0};

        public:
            LogicPlayer();
            int getPlayerColor(int playerIndex) const;
            void setPlayerColor(int movingFrom, int color, int player);
            int getPlayerCount();
            void setPlayerCount(LogicChip* Chip, LogicTerminal* Terminal);
            void handleSelfCollision(LogicBoard* Board, int possibleMove, vector<int> &possibleMoves, int index);

            int currentPlayer;
            int player1Color = 0;
            int player2Color = 0;
            int player3Color = 0;
            int player4Color = 0;
    };
} 

#endif // GAME_BOARD_LOGIC_PLAYER_HPP