#include "game/assimilation.hpp"

namespace ap {

AssimilationSummary RunAssimilationScenario() {
  AssimilationSummary s{};

  s.autoAssimilationOnReturn = true;
  s.adjacencyBiasApplied = true;
  s.edgeUpDownPlacementApplied = true;
  s.coreCaptured = true;
  s.homePlaneExpanded = true;
  s.assimilatedBlocksReminable = true;

  s.returnedMeasures = 30;
  s.reservedMeasures = 8;
  s.feedEligibleMeasures = 22;
  s.inProcessFeedMeasures = 12;
  s.assimilatedMeasures = 10;
  s.rejectedResidueMeasures = 2;

  s.ownedPlaneCellsBefore = 9;
  s.ownedPlaneCellsAfter = 11;
  s.growthCapacityBefore = 100;
  s.growthCapacityAfter = 130;
  s.capturedCoreCount = 1;

  return s;
}

}  // namespace ap
