/// logic_special.cpp
#include "game_logic/logic_special.hpp"
#include "game_logic/logic_board.hpp"
#include "game_logic/logic_player.hpp"
#include "game_logic/logic_calculations.hpp"
#include "game_logic/logic_chip.hpp"
#include <algorithm>


namespace logic {
    LogicSpecial::LogicSpecial() {}

    void LogicSpecial::handleWhoops(LogicChip* Chip, LogicBoard* Board, LogicPlayer* Player, LogicCalculations* Calc, vector<int> possibleMoves) {
        if (Chip->lastChip == 0) {
            int opponentPawn;
            cout << "Select an opponent's pawn to send back to start: ";
            cin >> opponentPawn;
            while (find(possibleMoves.begin(), possibleMoves.end(), opponentPawn) == possibleMoves.end()) {
                cout << "Invalid pawn" << endl;
                cout << "Select an opponent's pawn to send back to start: ";
                cin >> opponentPawn;
            }
            int opponentColor = Board->currentLocations[opponentPawn];
            Board->currentLocations[Board->findNextOpenStart(opponentColor)] = opponentColor;
            Board->currentLocations[opponentPawn] = Player->getPlayerColor(Player->currentPlayer);
            Board->currentLocations[Calc->movingFrom] = 0;
            //Slide if on slide square
            int newLocation = Board->checkSlide(Player, opponentPawn);
            cout << "Press any key to confirm opponent's pawn has been sent back to start and your pawn has been set in their previous location." << endl;
            cin.ignore();
            cin.get();

        }
    }

    void LogicSpecial::handleSeven(LogicChip* Chip, LogicBoard* Board, LogicPlayer* Player, LogicCalculations* Calc, vector<int> possibleMoves, int movingFrom) {
        if (Chip->lastChip == 7) {
            int color = Player->getPlayerColor(Player->currentPlayer);
            cout << "Place your pawn in a valid location: " << endl;
            int location;
            cin >> location;
            while (find(possibleMoves.begin(), possibleMoves.end(), location) == possibleMoves.end()) {
                cout << "Invalid location" << endl;
                cout << "Place your pawn in a valid location: " << endl;
                cin >> location;
            }
            Board->currentLocations[location] = color;
            Board->currentLocations[movingFrom] = 0;
            //Slide if on slide square
            int newLocation = Board->checkSlide(Player, location);
            int firstDistance = Calc->getDistance(Player, movingFrom, location);
            int secondDistance = 7 - firstDistance;
            if (secondDistance == 0) {
                return;
            }
            cout << "You have " << secondDistance << " spaces left to move with your second pawn." << endl;
            cout << "Possible second pawn current locations(s): ";
            for (int i = 0; i < 44; i++) {
                if (Board->currentLocations[i] == color && i != location && i != newLocation) {
                    cout << i << " ";
                }
            }
            for (int i = 0; i < kSafetyLocations.size(); i++) {
                if (Board->currentLocations[kSafetyLocations[i]] == color && kSafetyLocations[i] != location) {
                    cout << kSafetyLocations[i] << " ";
                }
            }
            cout << endl;
            cout << "Select a pawn location to move from: ";
            int secondPawnStart;
            cin >> secondPawnStart;
            while (Board->currentLocations[secondPawnStart] != color) {
                cout << "Invalid pawn" << endl;
                cout << "Select a pawn to move: ";
                cin >> secondPawnStart;
            }
            cout << "Move your second pawn " << secondDistance << " spaces forward. Press any key to confirm:" << endl;
            cin.ignore();
            cin.get();
            Board->currentLocations[secondPawnStart] = 0;
            moveSecondPawn(Board, Player, secondDistance, secondPawnStart);
        }
    }

    void LogicSpecial::moveSecondPawn(LogicBoard* Board, LogicPlayer* Player, int distance, int start) { // Need to finish
        int color = Player->getPlayerColor(Player->currentPlayer);
        int location = start;
        for (int i = 0; i < distance; i++) {
            if (location == 43) {
                location = 0;
            }
            else if (location == 1 + 11*(color-1)) {
                location = 49 + 9*(color-1);
            }
            else if (location == 49 + 9*(color-1)) {
                location = 48 + 9*(color-1);
            }
            else if (location == 48 + 9*(color-1)) {
                location = 47 + 9*(color-1);
            }
            else if (location == 47 + 9*(color-1)) {
                location = Board->findNextOpenHome(color);
            }
            else if (location >= 0 && location < 43) {
                location++;
            }
        }

        //If piece hits other piece, send other piece back to start
        if (Board->currentLocations[location] != 0) {
            cout << "COLLISION: Send opponent's piece back to start. Press any key to confirm: " << endl;
            cin.ignore();
            cin.get();
            Board->currentLocations[Board->findNextOpenStart(Board->currentLocations[location])] = Board->currentLocations[location];
        }
        Board->currentLocations[location] = color;
        Board->currentLocations[start] = 0;
        //Slide if on slide square
        location = Board->checkSlide(Player, location);
    }

    void LogicSpecial::handleEleven(LogicChip* Chip, LogicBoard* Board, LogicPlayer* Player, vector<int> possibleMoves, int movingFrom) {
        if (Chip->lastChip == 11) {
            int color = Player->getPlayerColor(Player->currentPlayer);
            int endLocation;
            cout << "Select an opponent's pawn to send back to swap with or move forward 11 spaces" << endl;
            cout << "Enter the oppoents's pawn location or the location you are moving to: ";
            cin >> endLocation;
            while (find(possibleMoves.begin(), possibleMoves.end(), endLocation) == possibleMoves.end()) {
                cout << "Invalid pawn/location" << endl;
                cout << "Enter the oppoents's pawn location or the location you are moving to: ";
                cin >> endLocation;
            }
            if (Board->currentLocations[endLocation] == 0) {
                Board->currentLocations[endLocation] = color;
                //Slide if on slide square
                endLocation = Board->checkSlide(Player, endLocation);
                Board->currentLocations[movingFrom] = 0;
            } else {
                int opponentColor = Board->currentLocations[endLocation];
                Board->currentLocations[movingFrom] = opponentColor;
                //Slide if on slide square
                int opponentPosition = Board->checkSlide(Player, movingFrom);
                Board->currentLocations[endLocation] = color;
                //Slide if on slide square
                endLocation = Board->checkSlide(Player, endLocation);
                cout << "Press any key to confirm opponent's pawn swapped with your pawn." << endl;
                cin.ignore();
                cin.get();
            }
        }
    }
}