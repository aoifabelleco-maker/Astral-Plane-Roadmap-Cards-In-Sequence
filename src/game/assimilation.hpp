#pragma once

namespace ap {

struct AssimilationSummary {
  bool autoAssimilationOnReturn;
  bool adjacencyBiasApplied;
  bool edgeUpDownPlacementApplied;
  bool coreCaptured;
  bool homePlaneExpanded;
  bool assimilatedBlocksReminable;

  int returnedMeasures;
  int reservedMeasures;
  int feedEligibleMeasures;
  int inProcessFeedMeasures;
  int assimilatedMeasures;
  int rejectedResidueMeasures;

  int ownedPlaneCellsBefore;
  int ownedPlaneCellsAfter;
  int growthCapacityBefore;
  int growthCapacityAfter;
  int capturedCoreCount;
};

AssimilationSummary RunAssimilationScenario();

}  // namespace ap
