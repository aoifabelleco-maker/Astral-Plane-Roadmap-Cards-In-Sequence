#pragma once

namespace ap {

struct BuildingStorageHeatSummary {
  bool buildPanelUsable;
  bool roomClosed;
  bool bedPlaced;
  bool stockpileActive;
  bool vaultPlaceholderActive;
  bool cultivationSpotPlaceholder;
  bool trainingSpotPlaceholder;
  bool enclosureCheckPassed;
  bool heatSourceActive;
  int localTempBeforeC;
  int localTempAfterC;
  bool iceMeltedToWater;

  bool storageLoosePileState;
  bool storageContainedState;
  bool storageStockpileState;
  bool storageReservedState;
  bool storageQueryUsable;
  bool transportTruthDistinct;
};

BuildingStorageHeatSummary RunBuildingStorageHeatScenario();

}  // namespace ap
