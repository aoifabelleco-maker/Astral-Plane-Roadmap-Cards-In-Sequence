#pragma once

#include <string>
#include <vector>

namespace ap {

struct WorldSummary {
  int layerCount;
  int blockCount;
  int homePlaneBlockCount;
  int visibleStartLayer;
  bool coreExists;
  int occupiedCells;
  int fullBlockCells;
  int looseMatterCells;
  int assimilatedCells;
  int containedMatterCells;
  int reservedMatterCells;
  int taintedMatterCells;
  int refinedMatterCells;
  int totalMeasures;
};

struct WorldBlock {
  int x;
  int y;
  int layer;
  std::string role;
};

struct WorldLayout {
  WorldSummary summary;
  std::vector<WorldBlock> blocks;
};

WorldLayout GenerateStartPlaneLayout();

}  // namespace ap
