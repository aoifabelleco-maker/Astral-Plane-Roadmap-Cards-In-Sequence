#pragma once

#include <string>
#include <vector>

namespace ap {

struct PortalCoordinate {
  std::string planeId;
  int x = 0;
  int y = 0;
};

struct SaveRecord {
  std::string schemaVersion;
  int worldSeed = 0;
  int homePlaneOwnedCells = 0;
  int homePlaneGrowthCapacity = 0;
  bool ironmanEnabled = true;
  bool playerDead = false;
  int deathCount = 0;
  int reincarnationIndex = 0;
  std::vector<std::string> memoryFragments;
  std::vector<PortalCoordinate> portals;
  std::string ancestralLandState;
};

struct SaveScenarioResult {
  bool writeSucceeded = false;
  bool loadSucceeded = false;
  bool noDrift = false;
  bool deathDidNotRewindWorld = false;
  bool reincarnationBootstrapReady = false;
  bool schemaChangeReported = false;
  SaveRecord loaded;
};

SaveScenarioResult RunSaveReincarnationScenario(const std::string& outputPath,
                                                const std::string& schemaReportPath);

}  // namespace ap
