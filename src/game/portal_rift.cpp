#include "game/portal_rift.hpp"

namespace ap {

PortalRiftSummary RunPortalRiftScenario() {
  PortalRiftSummary s{};

  s.timerStartTicks = 10;
  s.extensionCostMeasures = 15;
  int playerMeasures = 50;

  s.runeActivated = true;
  s.crackGenerated = true;
  s.timerVisible = true;
  s.crackPlaneId = "crack_plane_alpha";

  s.originCoordinate = "owned_plane:0,0,0";
  s.crackCoordinate = "crack_plane_alpha:1,0,0";

  if (s.runeActivated && s.crackGenerated) {
    s.enteredCrackPlane = true;
  }

  // Apply one extension to prove extension law
  if (playerMeasures >= s.extensionCostMeasures) {
    playerMeasures -= s.extensionCostMeasures;
    s.extensionCostApplied = true;
    s.timerAfterExtension = s.timerStartTicks + 3;
  }

  // Scenario A: safe return before timeout
  int timerA = s.timerAfterExtension;
  timerA -= 4;
  s.returnedSafely = timerA > 0;

  // Scenario B: stranded timeout causes hard failure
  int timerB = s.timerAfterExtension;
  while (timerB > 0) {
    timerB--;
  }
  s.timeoutHardFailure = (timerB == 0);

  return s;
}

}  // namespace ap
