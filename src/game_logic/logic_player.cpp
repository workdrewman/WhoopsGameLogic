/// logic_player.cpp
#include "game_logic/logic_player.hpp"
#include "game_logic/logic_board.hpp"
#include "game_logic/logic_chip.hpp"
#include "game_logic/logic_terminal.hpp"

using namespace std;

namespace logic {
    LogicPlayer::LogicPlayer() {}

    int LogicPlayer::getPlayerColor(int playerIndex) const {
        return playerColors[playerIndex];
    }

    //POSSIBLE BUG: if player picks up a piece that already has a color
    void LogicPlayer::setPlayerColor(int movingFrom, int color, int player) {
        if (movingFrom >= 50 && movingFrom <= 52) {
            color = 1;    //Yellow
        } else if (movingFrom >= 59 && movingFrom <= 61) {
            color = 2;    //Green
        } else if (movingFrom >= 68 && movingFrom <= 70) {
            color = 3;    //Red
        } else if (movingFrom >= 77 && movingFrom <= 79) {
            color = 4;    //Blue
        }

        playerColors[player] = color;
    }

    int LogicPlayer::getPlayerCount() {
        return playerCount;
    }

    void LogicPlayer::setPlayerCount(LogicChip* Chip, LogicTerminal* Terminal) {
        //Scan chip to get player count
        cout << "Get number of players: " << endl;
        //Audio
        int lastChip = Chip->waitForChip(Terminal);
        while (lastChip < 2 || lastChip > 4) {
            //ERROR
            cout << "Invalid number of players" << endl;
            //Audio
            //Scan chip to get player count
            lastChip = Chip->waitForChip(Terminal);
        }
        playerCount = lastChip;
        lastChip = -1;
    }

    void LogicPlayer::handleSelfCollision(LogicBoard* Board, int possibleMove, vector<int> &possibleMoves, int index) {    
        int color = getPlayerColor(currentPlayer);
        if (Board->currentLocations[possibleMove] == color) {
            possibleMoves.erase(possibleMoves.begin() + index);
        }
    }
} 