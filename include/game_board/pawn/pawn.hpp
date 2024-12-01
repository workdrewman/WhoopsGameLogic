// =======================================================
// Description: This header file contains the declaration
//              of the Pawn class. This will define
//              the functions needed to use the game
//              pieces.
// =======================================================

#ifndef GAME_BOARD_PAWN_H
#define GAME_BOARD_PAWN_H

#include "../whoops_color.hpp" // for WhoopsColor

#include <memory>

namespace game_board
{
// Forward declaration of Tile to avoid circular dependency
class Tile;

class Pawn
{
 public:
  /// @brief Pawn Constructor
  /// @param color Color of the game piece to create
  Pawn(WhoopsColor color, int id);
  
  /// @brief Function that updates the tile to occupy
  ///        a new tile that is passed in.
  /// @param new_tile Pointer of the new tile
  void MoveTo(std::shared_ptr<Tile> new_tile);

  /// @brief Function that returns the tile rule
  ///        of whether it can be whoopsed
  /// @return True if the tile can be whoopsed
  bool CanBeWhoopsed();

  /// @brief Function that returns boolean whether
  ///        one pawn can whoops the other.
  /// @param other_pawn Any other pawn
  /// @return True if you can whoops the other pawn
  bool CanWhoops(Pawn* other_pawn);

  WhoopsColor GetColor();

 private:
  std::shared_ptr<Tile> tile_occupied_{};
  WhoopsColor color_{WhoopsColor::kNone};
  int id_{0};
};
} // namespace game_board
#endif // GAME_BOARD_PAWN_H
