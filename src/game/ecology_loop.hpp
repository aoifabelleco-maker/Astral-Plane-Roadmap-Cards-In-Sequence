#pragma once

namespace ap {

struct EcologyLoopSummary {
  bool cometEventOccurred = false;
  bool meteorEventOccurred = false;
  bool seedDropOccurred = false;
  bool slimeArrived = false;
  bool slimeConsumedMatter = false;
  bool sameRankSlimeMerged = false;
  bool slimeDefeatRecoveredMatter = false;
  bool plantLoopSeedToHarvestWorked = false;
  int matterConsumed = 0;
  int matterRecovered = 0;
  int extraReward = 0;
};

EcologyLoopSummary RunEcologyLoopScenario();

}  // namespace ap
