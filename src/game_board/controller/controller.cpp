// =======================================================
// Description: This header file contains the implementation
//              of the Controller class. This class is 
//              used to control the pawn and tile movements
// =======================================================

#include "../../../include/game_board/controller/controller.hpp" // for Controller

#include "../../../include/game_board/whoops_color.hpp" // for WhoopsColor
#include "../../../include/game_board/pawn/pawn.hpp" // for Pawn
#include "../../../include/game_board/tile/base_tile.hpp" // for Tile
#include "../../../include/game_board/tile/tile_container.hpp" // for TileContainer

#include <vector> // for std::vector
#include <memory> // for std::shared_ptr

namespace game_board
{

auto constexpr kNumPawns{3};

Controller::Controller()
{
 auto tile_types = {game_board::TileType::kNormal, 
                     game_board::TileType::kSlide, game_board::TileType::kSlide,
                     game_board::TileType::kSlide, game_board::TileType::kSlide, game_board::TileType::kNormal,
                     game_board::TileType::kNormal, game_board::TileType::kSlide, game_board::TileType::kSlide,
                     game_board::TileType::kSlide, game_board::TileType::kSlide, game_board::TileType::kNormal,
                     
                     game_board::TileType::kSlide, game_board::TileType::kSlide,
                     game_board::TileType::kSlide, game_board::TileType::kSlide, game_board::TileType::kNormal,
                     game_board::TileType::kNormal, game_board::TileType::kSlide, game_board::TileType::kSlide,
                     game_board::TileType::kSlide, game_board::TileType::kSlide, game_board::TileType::kNormal,
                     
                     game_board::TileType::kSlide, game_board::TileType::kSlide,
                     game_board::TileType::kSlide, game_board::TileType::kSlide, game_board::TileType::kNormal,
                     game_board::TileType::kNormal, game_board::TileType::kSlide, game_board::TileType::kSlide,
                     game_board::TileType::kSlide, game_board::TileType::kSlide, game_board::TileType::kNormal,

                     game_board::TileType::kSlide, game_board::TileType::kSlide,
                     game_board::TileType::kSlide, game_board::TileType::kSlide, game_board::TileType::kNormal,
                     game_board::TileType::kNormal, game_board::TileType::kSlide, game_board::TileType::kSlide,
                     game_board::TileType::kSlide, game_board::TileType::kSlide};

  auto colors = {game_board::WhoopsColor::kNone,
                  game_board::WhoopsColor::kYellow, game_board::WhoopsColor::kYellow,
                  game_board::WhoopsColor::kYellow, game_board::WhoopsColor::kYellow, game_board::WhoopsColor::kYellow,
                  game_board::WhoopsColor::kYellow, game_board::WhoopsColor::kYellow, game_board::WhoopsColor::kYellow,
                  game_board::WhoopsColor::kYellow, game_board::WhoopsColor::kYellow, game_board::WhoopsColor::kNone,

                  game_board::WhoopsColor::kGreen, game_board::WhoopsColor::kGreen,
                  game_board::WhoopsColor::kGreen, game_board::WhoopsColor::kGreen, game_board::WhoopsColor::kGreen,
                  game_board::WhoopsColor::kGreen, game_board::WhoopsColor::kGreen, game_board::WhoopsColor::kGreen,
                  game_board::WhoopsColor::kGreen, game_board::WhoopsColor::kGreen, game_board::WhoopsColor::kNone,

                  game_board::WhoopsColor::kRed, game_board::WhoopsColor::kRed,
                  game_board::WhoopsColor::kRed, game_board::WhoopsColor::kRed, game_board::WhoopsColor::kRed,
                  game_board::WhoopsColor::kRed, game_board::WhoopsColor::kRed, game_board::WhoopsColor::kRed,
                  game_board::WhoopsColor::kRed, game_board::WhoopsColor::kRed, game_board::WhoopsColor::kNone,
                  
                  game_board::WhoopsColor::kBlue, game_board::WhoopsColor::kBlue,
                  game_board::WhoopsColor::kBlue, game_board::WhoopsColor::kBlue, game_board::WhoopsColor::kBlue,
                  game_board::WhoopsColor::kBlue, game_board::WhoopsColor::kBlue, game_board::WhoopsColor::kBlue,
                  game_board::WhoopsColor::kBlue, game_board::WhoopsColor::kBlue};

  tiles_ = std::make_shared<TileContainer>(tile_types, colors);

  for (int i = 0; i < kNumPawns; i++) {
    pawns_.push_back(new Pawn(game_board::WhoopsColor::kYellow, static_cast<int>(game_board::WhoopsColor::kYellow) + i));
    pawns_.push_back(new Pawn(game_board::WhoopsColor::kGreen, static_cast<int>(game_board::WhoopsColor::kGreen) + i));
    pawns_.push_back(new Pawn(game_board::WhoopsColor::kRed, static_cast<int>(game_board::WhoopsColor::kRed) + i));
    pawns_.push_back(new Pawn(game_board::WhoopsColor::kBlue, static_cast<int>(game_board::WhoopsColor::kBlue) + i));
  } 
}

Pawn* Controller::GetPawnFromTile(std::shared_ptr<Tile> tile)
{
  return tile->GetPawn();
}

Pawn* Controller::GetPawnFromSensor(int sensor_idx)
{
  auto tile = tiles_->GetTileFromSensor(sensor_idx);
  return tile->GetPawn();
}

std::vector<Pawn*> Controller::GetCurrentColorPawns()
{
  std::vector<Pawn*> current_pawns;
  for (size_t i = 0; i < pawns_.size(); i++) {
    if (pawns_.at(i)->GetColor() == current_color_) {
      current_pawns.push_back(pawns_.at(i));
    }
  }
  return current_pawns;
}

} // namespace game_board
