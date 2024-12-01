// =======================================================
// Description: This header file contains the declaration
//              of the SlideTile class.
// =======================================================

#ifndef GAME_BOARD_TILE_SLIDE_H
#define GAME_BOARD_TILE_SLIDE_H

#include "base_tile.hpp" // For Tile
#include "../pawn/pawn.hpp" // for Pawn

namespace game_board
{
class SlideTile : public Tile
{
 public:
  SlideTile(int index, WhoopsColor tile_color, bool slide_start = false, bool entrance_tile = false) : 
            led_index_{index}, tile_color_{tile_color}, is_slide_start_{slide_start} {}

  bool CanBeWhoopsed() override { return !IsVacant(); };
  
  /// @brief Updates the color of the pawn occupying the space
  /// @param pawn Pointer to the pawn that is moving to the space
  void PawnArrivingTo(Pawn* pawn) override { color_occupied_ = pawn->GetColor(); pawn_ = pawn; }

  /// @brief Updates the color of the pawn occupying to none
  void PawnLeavingFrom() override { color_occupied_ = WhoopsColor::kNone; pawn_ = nullptr; }

  /// @brief Returns bool to tell if a piece is on the tile or not
  /// @return True if a piece is occupying
  bool IsVacant() override { return (color_occupied_ != WhoopsColor::kNone); }

  /// @brief Method that determines if a piece will slide
  /// @return True if the tile is the start of a slide
  bool IsSlideStart() { return is_slide_start_; };

  /// @brief Returns bool to tell if the piece should 
  /// @return True if the piece should move to the safety tiles
  bool AdvanceToSafetyTile(Pawn* pawn) { return (pawn->GetColor() == tile_color_) && is_entrance_; }

  Pawn* GetPawn() { return pawn_; }

 private:
  int led_index_{-1};
  WhoopsColor tile_color_{WhoopsColor::kNone};
  WhoopsColor color_occupied_{WhoopsColor::kNone};
  bool is_slide_start_{false};
  bool is_entrance_{true};
  Pawn* pawn_{nullptr};
};
} // namespace game_board
#endif // GAME_BOARD_TILE_SLIDE_H
