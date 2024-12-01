// =======================================================
// Description: This header file contains the implementation
//              of the Pawn class. This will define
//              the functions needed to use the game
//              pieces.
// =======================================================

#include "../../../include/game_board/pawn/pawn.hpp" // for Pawn

#include "../../../include/game_board/whoops_color.hpp" // for WhoopsColor
#include "../../../include/game_board/tile/base_tile.hpp" // for Tile

#include "memory" // for std::shared_ptr

namespace game_board
{

Pawn::Pawn(WhoopsColor color, int id) : color_{color}, id_{id} {}

void Pawn::MoveTo(std::shared_ptr<Tile> new_tile)
{
  tile_occupied_->PawnLeavingFrom();
  tile_occupied_ = new_tile;
  tile_occupied_->PawnArrivingTo(this);
}

bool Pawn::CanBeWhoopsed()
{
  return tile_occupied_->CanBeWhoopsed();
}

bool Pawn::CanWhoops(Pawn* other_pawn)
{
  return ((other_pawn->CanBeWhoopsed()) && (other_pawn->color_ != color_));
}

WhoopsColor Pawn::GetColor()
{
  return color_;
}

} // namespace game_board
