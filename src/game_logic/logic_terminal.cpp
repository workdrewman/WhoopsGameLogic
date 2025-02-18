/// logic_terminal.cpp
#include "game_logic/logic_terminal.hpp"
#include <iostream>

using namespace std;

namespace logic {
    LogicTerminal::LogicTerminal() {}
    
    int LogicTerminal::t_GetChip() {
        int chip;
        cout << "Enter chip number: ";
        cin >> chip;
        return chip;
    }

    int LogicTerminal::t_setStartAreas(LogicBoard* Board, LogicPlayer* Player) {
        Board->currentLocations[50] = 1;
        Board->currentLocations[51] = 1;
        Board->currentLocations[52] = 1;
        Board->currentLocations[59] = 2;
        Board->currentLocations[60] = 2;
        Board->currentLocations[61] = 2;
        if (Player->getPlayerCount() >= 3) {
            Board->currentLocations[68] = 3;
            Board->currentLocations[69] = 3;
            Board->currentLocations[70] = 3;
        }
        if (Player->getPlayerCount() == 4) {
            Board->currentLocations[77] = 4;
            Board->currentLocations[78] = 4;
            Board->currentLocations[79] = 4;
        }

        //Set colors too lol
        Player->player1Color = 1;
        Player->player2Color = 2;
        if (Player->getPlayerCount() >= 3) {
            Player->player3Color = 3;
        }
        if (Player->getPlayerCount() == 4) {
            Player->player4Color = 4;
        }

        Board->lastLocations = Board->currentLocations;
        return Player->getPlayerCount();
    }

    void LogicTerminal::t_displayChipInstructions(LogicChip* Chip) {
        switch (Chip->lastChip) {
            case 0:
                cout << "Whoops! Take any one pawn from Start and move it directly to a square occupied by any opponent's pawn, sending that pawn back to its own Start. A Whoops! chip cannot be used on an opponent's pawn in a Safety Zone or at the Home base. If there are no pawns on the player's Start, or no opponent's pawns on any space that can be moved to, the turn ends." << endl;
                break;
            case 1:
                cout << "Either move a pawn from Start or move a pawn 1 space forward." << endl;
                break;
            case 2:
                cout << "Either move a pawn from Start or move a pawn 2 spaces forward." << endl; //Maybe add draw again
                break;
            case 3:
                cout << "Move a pawn 3 spaces forward." << endl;
                break;
            case 4:
                cout << "Move a pawn 4 spaces backward." << endl;
                break;
            case 5:
                cout << "Move a pawn 5 spaces forward." << endl;
                break;
            case 7:
                cout << "Move one pawn 7 spaces forward, or split the 7 spaces between two pawns (such as 4 spaces for one pawn and 3 for another)." << endl;
                break;
            case 8:
                cout << "Move a pawn 8 spaces forward." << endl;
                break;
            case 10:
                cout << "Move a pawn 10 spaces forward or 1 space backward. If none of a player's pawns can move forward 10 spaces, then one pawn must move back 1 space." << endl;
                break;
            case 11:
                cout << "Move 11 spaces forward, or switch the places of one of the player's own pawns and an opponent's pawn. A player who cannot move 11 spaces is not forced to switch and instead can end their turn. An 11 cannot be used to switch a pawn that is in a Safety Zone." << endl;
                break;
            case 12:
                cout << "Move a pawn 12 spaces forward." << endl;
                break;
        }
        cout << endl;
    }

    void LogicTerminal::t_whereAreMyPieces(LogicBoard* Board, LogicPlayer* Player) {
        int color = Player->getPlayerColor(Player->currentPlayer);
        cout << "Player " << Player->currentPlayer + 1 << "'s pieces: ";
        for (int i = 0; i < Board->boardSize; i++) {
            if (Board->currentLocations[i] == color) {
                cout << i << " ";
            }
        }
        cout << endl;
    }

    void LogicTerminal::t_selectPiece(LogicBoard* Board, LogicPlayer* Player, LogicCalculations* Calc) {
        int location;
        int color = Player->getPlayerColor(Player->currentPlayer);
        cout << "Select a location to move " << Player->currentPlayer + 1 << "'s piece from: ";
        cin >> location;
        while (Board->currentLocations[location] != color) {
            cout << "Invalid piece" << endl;
            cout << "Select a piece to move: ";
            cin >> location;
        }
        Calc->movingFrom = location;
        //setPlayerColor();
    }
}