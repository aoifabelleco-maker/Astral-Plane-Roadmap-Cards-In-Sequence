#pragma once

#include <string>
#include <vector>

namespace ap {

enum class CellMatterState {
  FullBlock,
  LooseMatter,
  AssimilatedMatter,
  ContainedMatter,
};

struct TerrainCell {
  int x;
  int y;
  int z;
  bool occupied;
  CellMatterState state;
  int measures;
  double temperatureC;
  bool reservedMatter;
  bool taintedMatter;
  bool refinedMatter;
};

struct TerrainModelSummary {
  int totalCells;
  int occupiedCells;
  int freeCells;
  int fullBlockCells;
  int looseMatterCells;
  int assimilatedCells;
  int containedMatterCells;
  int reservedMatterCells;
  int taintedMatterCells;
  int refinedMatterCells;
  int totalMeasures;
  int totalLayers;
  int minZ;
  int maxZ;
};

struct TerrainModel {
  std::vector<TerrainCell> cells;
  TerrainModelSummary summary;
};

TerrainModel BuildStartTerrainModel();
std::string CellMatterStateToString(CellMatterState state);

}  // namespace ap
