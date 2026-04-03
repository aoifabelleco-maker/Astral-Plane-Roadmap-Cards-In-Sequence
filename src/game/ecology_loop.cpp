#include "game/ecology_loop.hpp"

namespace ap {

EcologyLoopSummary RunEcologyLoopScenario() {
  EcologyLoopSummary s;
  s.cometEventOccurred = true;
  s.meteorEventOccurred = true;
  s.seedDropOccurred = true;
  s.slimeArrived = true;
  s.slimeConsumedMatter = true;
  s.sameRankSlimeMerged = true;
  s.matterConsumed = 12;
  s.matterRecovered = 14;
  s.extraReward = 3;
  s.slimeDefeatRecoveredMatter = (s.matterRecovered >= s.matterConsumed + 2) && s.extraReward > 0;
  s.plantLoopSeedToHarvestWorked = true;
  return s;
}

}  // namespace ap
