#pragma once

#include <string>

namespace ap {

struct HarshVerbSummary {
  bool moveWorked;
  bool mineWorked;
  bool carryLimitEnforced;
  bool pickupWorked;
  bool dropWorked;
  bool transferWorked;
  bool fightWorked;
  bool hostileDied;
  bool playerDied;
  bool corpseHandled;
  int carriedMeasures;
  int groundMeasures;
  bool looseStackCreated;
  bool splitWorked;
  bool mergeLegalWorked;
  bool mergeBlockedWorked;
  std::string mergeBlockedReason;
  std::string mergedWarningChip;
  std::string inspectText;
};

HarshVerbSummary RunHarshVerbScenario();

}  // namespace ap
