#include "world/terrain_model.hpp"

namespace ap {

std::string CellMatterStateToString(CellMatterState state) {
  switch (state) {
    case CellMatterState::FullBlock:
      return "full_block";
    case CellMatterState::LooseMatter:
      return "loose_matter";
    case CellMatterState::AssimilatedMatter:
      return "assimilated_matter";
    case CellMatterState::ContainedMatter:
      return "contained_matter";
  }
  return "unknown";
}

TerrainModel BuildStartTerrainModel() {
  TerrainModel model;
  model.summary = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, -1, 1};

  for (int z = -1; z <= 1; ++z) {
    for (int y = -1; y <= 1; ++y) {
      for (int x = -1; x <= 1; ++x) {
        TerrainCell cell{};
        cell.x = x;
        cell.y = y;
        cell.z = z;
        cell.temperatureC = 12.0;
        cell.reservedMatter = false;
        cell.taintedMatter = false;
        cell.refinedMatter = false;

        if (z == 0) {
          cell.state = CellMatterState::FullBlock;
          cell.measures = 27;
        } else if (z < 0) {
          cell.state = CellMatterState::LooseMatter;
          cell.measures = 9;
        } else {
          cell.state = CellMatterState::AssimilatedMatter;
          cell.measures = 18;
        }

        cell.occupied = cell.measures > 0;
        model.cells.push_back(cell);

        model.summary.totalCells++;
        model.summary.totalMeasures += cell.measures;
        if (cell.occupied) {
          model.summary.occupiedCells++;
        } else {
          model.summary.freeCells++;
        }
        if (cell.state == CellMatterState::FullBlock) {
          model.summary.fullBlockCells++;
        }
        if (cell.state == CellMatterState::LooseMatter) {
          model.summary.looseMatterCells++;
        }
        if (cell.state == CellMatterState::AssimilatedMatter) {
          model.summary.assimilatedCells++;
        }
        if (cell.state == CellMatterState::ContainedMatter) {
          model.summary.containedMatterCells++;
        }
        if (cell.reservedMatter) {
          model.summary.reservedMatterCells++;
        }
        if (cell.taintedMatter) {
          model.summary.taintedMatterCells++;
        }
        if (cell.refinedMatter) {
          model.summary.refinedMatterCells++;
        }
      }
    }
  }

  return model;
}

}  // namespace ap
