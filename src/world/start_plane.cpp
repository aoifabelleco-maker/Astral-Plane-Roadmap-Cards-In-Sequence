#include "world/start_plane.hpp"

#include "world/terrain_model.hpp"

namespace ap {

WorldLayout GenerateStartPlaneLayout() {
  WorldLayout layout;
  layout.summary.layerCount = 3;
  layout.summary.blockCount = 0;
  layout.summary.homePlaneBlockCount = 0;
  layout.summary.visibleStartLayer = 0;
  layout.summary.coreExists = false;

  const auto terrain = BuildStartTerrainModel();
  layout.summary.occupiedCells = terrain.summary.occupiedCells;
  layout.summary.fullBlockCells = terrain.summary.fullBlockCells;
  layout.summary.looseMatterCells = terrain.summary.looseMatterCells;
  layout.summary.assimilatedCells = terrain.summary.assimilatedCells;
  layout.summary.containedMatterCells = terrain.summary.containedMatterCells;
  layout.summary.reservedMatterCells = terrain.summary.reservedMatterCells;
  layout.summary.taintedMatterCells = terrain.summary.taintedMatterCells;
  layout.summary.refinedMatterCells = terrain.summary.refinedMatterCells;
  layout.summary.totalMeasures = terrain.summary.totalMeasures;

  for (int layer = -1; layer <= 1; ++layer) {
    for (int y = -1; y <= 1; ++y) {
      for (int x = -1; x <= 1; ++x) {
        WorldBlock block{x, y, layer, "support"};
        if (layer == 0) {
          block.role = "home_plane";
          layout.summary.homePlaneBlockCount++;
        }
        if (layer == 0 && x == 0 && y == 0) {
          block.role = "core";
          layout.summary.coreExists = true;
        }
        layout.blocks.push_back(block);
      }
    }
  }

  layout.summary.blockCount = static_cast<int>(layout.blocks.size());
  return layout;
}

}  // namespace ap
