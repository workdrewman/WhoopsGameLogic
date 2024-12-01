// =======================================================
// Description: This header file contains the declaration
//              of the Logic Controller class. This class is 
//              used to control the pawn and tile movements
// =======================================================

#ifndef GAME_BOARD_LOGIC_CONTROLLER_H
#define GAME_BOARD_LOGIC_CONTROLLER_H

// #include "../game_board/whoops_color.hpp" // for WhoopsColor
// #include "../game_board/pawn/pawn.hpp" // for Pawn
// #include "../game_board/tile/base_tile.hpp" // for Tile
// #include "../game_board/tile/tile_container.hpp" // for TileContainer

#include <vector> // for std::vector
#include <memory> // for std::shared_ptr

namespace logic_controller
{
    void startGame();
    void getPlayerCount();
    void nextPlayer();
    void saveCard(int card);
    int waitForCard();
    void saveCurrentLocations(std::vector<int> locations);
    void saveLastLocations(std::vector<int> locations);
    bool allPiecesPlaced();
    int moveSpaces(int color, int location, int spaces);

    //terminal functions
    int t_GetCard();
}

#endif // GAME_BOARD_CONTROLLER_H