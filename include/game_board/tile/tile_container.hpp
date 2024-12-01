// =======================================================
// Description: This header file contains the declaration
//              of the TileContainer class. This class is 
//              used to initialize the board with the 
//              correct tile types.
// =======================================================

#ifndef GAME_BOARD_TILE_CONTAINER_H
#define GAME_BOARD_TILE_CONTAINER_H

#include "../whoops_color.hpp" // for WhoopsColor
#include "../pawn/pawn.hpp" // for Pawn
#include "base_tile.hpp" // for BaseTile

#include <vector> // for std::vector
#include <memory> // for std::shared_ptr

namespace game_board
{
enum class TileType{
  kHome,
  kNormal,
  kSafety,
  kSlide,
  kStart,
  kEntrance
};

class TileContainer
{
 public:
  /// @brief Constructor to create the game tiles
  /// @param tile_types vector of tile types in order
  /// @param tile_colors vector of tile colors in order
  TileContainer(std::vector<TileType> tile_types, std::vector<WhoopsColor> tile_colors);

  /// @brief Returns a pointer to the tile based on sensor input
  /// @param sensor_idx 
  std::shared_ptr<Tile> GetTileFromSensor(int sensor_idx);

 private:
  std::vector<std::shared_ptr<Tile>> tiles_;
};
} // namespace game_board
#endif // GAME_BOARD_TILE_CONTAINER_H
