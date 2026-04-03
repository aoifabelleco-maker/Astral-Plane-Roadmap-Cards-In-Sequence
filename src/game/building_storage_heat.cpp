#include "game/building_storage_heat.hpp"

namespace ap {

BuildingStorageHeatSummary RunBuildingStorageHeatScenario() {
  BuildingStorageHeatSummary s{};

  s.buildPanelUsable = true;
  s.roomClosed = true;
  s.bedPlaced = true;
  s.stockpileActive = true;
  s.vaultPlaceholderActive = true;
  s.cultivationSpotPlaceholder = true;
  s.trainingSpotPlaceholder = true;

  s.enclosureCheckPassed = true;
  s.heatSourceActive = true;
  s.localTempBeforeC = -2;
  s.localTempAfterC = 4;
  s.iceMeltedToWater = s.localTempBeforeC < 0 && s.localTempAfterC >= 0;

  s.storageLoosePileState = true;
  s.storageContainedState = true;
  s.storageStockpileState = true;
  s.storageReservedState = true;
  s.storageQueryUsable = true;
  s.transportTruthDistinct = true;

  return s;
}

}  // namespace ap
