#pragma once

#include <string>

namespace ap {

struct PortalRiftSummary {
  bool runeActivated;
  bool crackGenerated;
  bool enteredCrackPlane;
  bool returnedSafely;
  bool timeoutHardFailure;
  bool timerVisible;
  bool extensionCostApplied;
  int timerStartTicks;
  int timerAfterExtension;
  int extensionCostMeasures;
  std::string originCoordinate;
  std::string crackCoordinate;
  std::string crackPlaneId;
};

PortalRiftSummary RunPortalRiftScenario();

}  // namespace ap
