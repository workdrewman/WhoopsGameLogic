// =======================================================
// Description: This header file contains the declaration
//              of the Tile base class. This will define
//              the base members for each of the game
//              of the game tiles.
// =======================================================

#ifndef GAME_BOARD_TILE_BASE_H
#define GAME_BOARD_TILE_BASE_H

#include "../whoops_color.hpp" // for WhoopsColor
#include "../pawn/pawn.hpp" // for Pawn

#include <memory>

namespace game_board
{
class Tile
{
 public:
  /// @brief Call to determine if a tile can be whoopsed
  /// @return True the tile has a game piece and can be whoopsed
  virtual bool CanBeWhoopsed() = 0;

  /// @brief Pawn arrives at the tile. 
  ///        Updates the color of the pawn occupying the space
  /// @param pawn Pointer to the pawn that is moving to the space
  virtual void PawnArrivingTo(Pawn* pawn) = 0;

  /// @brief Pawn leaves the tile. 
  ///        Updates the color of the pawn occupying to none
  virtual void PawnLeavingFrom() = 0;

  /// @brief Returns bool to tell if a piece is on the tile or not
  /// @return True if a piece is occupying
  virtual bool IsVacant(){ return true; }
  
  /// @brief Returns a pointer to the pawn that occupies the tile
  /// @return A pointer to the pawn.
  virtual Pawn* GetPawn() = 0;
};
} // namespace game_board
#endif // GAME_BOARD_TILE_BASE_H
