// =======================================================
// Description: This header file contains the declaration
//              of the SafetyTile class.
// =======================================================

#ifndef GAME_BOARD_TILE_SAFETY_H
#define GAME_BOARD_TILE_SAFETY_H

#include "base_tile.hpp" // For Tile
#include "../pawn/pawn.hpp" // for Pawn

namespace game_board
{
class SafetyTile : public Tile
{
 public:
  SafetyTile(int index, WhoopsColor tile_color) : led_index_{index}, tile_color_{tile_color} {}
  bool CanBeWhoopsed() override { return false; };
  
  /// @brief Updates the color of the pawn occupying the space
  /// @param pawn Pointer to the pawn that is moving to the space
  void PawnArrivingTo(Pawn* pawn) override { color_occupied_ = pawn->GetColor(); pawn_ = pawn; }

  /// @brief Updates the color of the pawn occupying to none
  void PawnLeavingFrom() override { color_occupied_ = WhoopsColor::kNone;  pawn_ = nullptr;}

  /// @brief Returns bool to tell if a piece is on the tile or not
  /// @return True if a piece is occupying
  bool IsVacant() override { return (color_occupied_ != WhoopsColor::kNone); }

  Pawn* GetPawn() { return pawn_; }
 private:
  int led_index_{-1};
  WhoopsColor tile_color_{WhoopsColor::kNone};
  WhoopsColor color_occupied_{WhoopsColor::kNone};
  Pawn* pawn_{nullptr};
};
} // namespace game_board
#endif // GAME_BOARD_TILE_SAFETY_H
