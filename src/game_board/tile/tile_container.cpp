// =======================================================
// Description: This header file contains the declaration
//              of the TileContainer class. This class is 
//              used to initialize the board with the 
//              correct tile types.
// =======================================================

#include "../../../include/game_board/tile/tile_container.hpp" // for TileContainer, TileType

#include "../../../include/game_board/whoops_color.hpp" // for WhoopsColor
#include "../../../include/game_board/pawn/pawn.hpp" // for Pawn
#include "../../../include/game_board/tile/home_tile.hpp"
#include "../../../include/game_board/tile/normal_tile.hpp"
#include "../../../include/game_board/tile/safety_tile.hpp"
#include "../../../include/game_board/tile/slide_tile.hpp"
#include "../../../include/game_board/tile/start_tile.hpp"

#include <vector> // for std::vector
#include <memory> // for std::shared_ptr, std::make_shared

namespace game_board
{

TileContainer::TileContainer(std::vector<TileType> tile_types, std::vector<WhoopsColor> tile_colors)
{
  for (auto idx = 0; idx < tile_types.size(); ++idx) {
    switch (tile_types.at(idx)){
      case TileType::kHome:
        tiles_.emplace_back(std::make_shared<HomeTile>(idx, tile_colors.at(idx)));
        break;
      case TileType::kNormal:
        tiles_.emplace_back(std::make_shared<NormalTile>(idx, tile_colors.at(idx)));
        break;
      case TileType::kSafety:
        tiles_.emplace_back(std::make_shared<SafetyTile>(idx, tile_colors.at(idx)));
        break;
      case TileType::kSlide:
        if (tile_types.at(idx - 1) == TileType::kSlide) {
          if (tile_types.at(idx - 2) != TileType::kSlide) { // if it's the first
            tiles_.emplace_back(std::make_shared<SlideTile>(idx, tile_colors.at(idx), false, true));
            continue;
          }
          tiles_.emplace_back(std::make_shared<SlideTile>(idx, tile_colors.at(idx)));
        }
        tiles_.emplace_back(std::make_shared<SlideTile>(idx, tile_colors.at(idx), true));
        break;
      case TileType::kStart:
        tiles_.emplace_back(std::make_shared<StartTile>(idx, tile_colors.at(idx)));
        break;
    }
  }
}


std::shared_ptr<Tile> TileContainer::GetTileFromSensor(int sensor_idx)
{
  if (sensor_idx < tiles_.size()){
    return tiles_.at(sensor_idx);
  } 
  return nullptr;
}

} // namespace game_board
