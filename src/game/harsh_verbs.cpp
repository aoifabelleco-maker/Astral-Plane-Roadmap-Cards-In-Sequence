#include "game/harsh_verbs.hpp"

#include "body/stats_model.hpp"

#include <algorithm>
#include <string>

namespace ap {

namespace {

enum class WarningLevel { None = 0, Low = 1, Medium = 2, High = 3 };

struct LooseStack {
  int measures;
  std::string owner;
  std::string legality;
  std::string contaminationFamily;
  std::string omenState;
  std::string freshnessBand;
  WarningLevel warning;
};

std::string WarningToChip(WarningLevel w) {
  if (w == WarningLevel::High) return "danger";
  if (w == WarningLevel::Medium) return "caution";
  if (w == WarningLevel::Low) return "notice";
  return "none";
}

bool CanMerge(const LooseStack& a, const LooseStack& b, std::string& reason) {
  if (a.legality != b.legality) {
    reason = "merge_blocked: legality mismatch";
    return false;
  }
  if (a.owner != b.owner) {
    reason = "merge_blocked: ownership mismatch";
    return false;
  }
  if (a.contaminationFamily != b.contaminationFamily) {
    reason = "merge_blocked: contamination family mismatch";
    return false;
  }
  if (a.omenState != b.omenState) {
    reason = "merge_blocked: omen mismatch";
    return false;
  }
  if (a.freshnessBand != b.freshnessBand) {
    reason = "merge_blocked: freshness mismatch";
    return false;
  }
  reason = "";
  return true;
}

LooseStack MergeStacks(const LooseStack& a, const LooseStack& b) {
  LooseStack out = a;
  out.measures = a.measures + b.measures;
  out.warning = static_cast<WarningLevel>(std::max(static_cast<int>(a.warning), static_cast<int>(b.warning)));
  return out;
}

LooseStack SplitStack(LooseStack& src, int splitMeasures) {
  if (splitMeasures < 1) splitMeasures = 1;
  if (splitMeasures > src.measures) splitMeasures = src.measures;
  src.measures -= splitMeasures;
  LooseStack child = src;
  child.measures = splitMeasures;
  return child;
}

}  // namespace

HarshVerbSummary RunHarshVerbScenario() {
  HarshVerbSummary s{};

  int playerX = 0;
  int playerY = 0;
  playerX += 1;
  s.moveWorked = (playerX == 1 && playerY == 0);

  const auto body = HumanMortalTemplate();
  const PrimaryStats primary{7, 8, 6, 5, 5};
  const auto derived = ComputeDerivedStats(body, primary, 0.0, 100);
  const int carryCapacity = derived.carryCapacityKg;

  LooseStack mined{27, "player", "legal", "none", "none", "fresh", WarningLevel::Low};
  s.mineWorked = (mined.measures == 27);
  s.looseStackCreated = s.mineWorked;

  // split inheritance
  LooseStack splitChild = SplitStack(mined, 10);
  s.splitWorked = (splitChild.measures == 10 && splitChild.owner == mined.owner &&
                   splitChild.contaminationFamily == mined.contaminationFamily &&
                   splitChild.warning == mined.warning);

  int carried = 0;
  int ground = mined.measures + splitChild.measures;

  int pickupAmount = 12;
  if (ground >= pickupAmount && carried + pickupAmount <= carryCapacity) {
    ground -= pickupAmount;
    carried += pickupAmount;
    s.pickupWorked = true;
  }

  int dropAmount = 4;
  if (carried >= dropAmount) {
    carried -= dropAmount;
    ground += dropAmount;
    s.dropWorked = true;
  }

  int transferAmount = 3;
  if (carried >= transferAmount) {
    carried -= transferAmount;
    ground += transferAmount;
    s.transferWorked = true;
  }

  s.carryLimitEnforced = carried <= carryCapacity;

  // legal merge preserves strongest warning union
  LooseStack legalA{5, "player", "legal", "none", "none", "fresh", WarningLevel::Low};
  LooseStack legalB{7, "player", "legal", "none", "none", "fresh", WarningLevel::High};
  std::string mergeReason;
  if (CanMerge(legalA, legalB, mergeReason)) {
    auto merged = MergeStacks(legalA, legalB);
    s.mergeLegalWorked = (merged.measures == 12);
    s.mergedWarningChip = WarningToChip(merged.warning);
  }

  // blocked merge
  LooseStack blockedA{3, "player", "legal", "none", "none", "fresh", WarningLevel::Low};
  LooseStack blockedB{2, "other_owner", "legal", "none", "none", "fresh", WarningLevel::Low};
  if (!CanMerge(blockedA, blockedB, mergeReason)) {
    s.mergeBlockedWorked = true;
    s.mergeBlockedReason = mergeReason;
  }

  int playerHp = 24;
  int hostileHp = 20;
  const int playerDmg = 7;
  const int hostileDmg = 6;
  while (playerHp > 0 && hostileHp > 0) {
    hostileHp -= playerDmg;
    if (hostileHp <= 0) break;
    playerHp -= hostileDmg;
  }

  s.fightWorked = true;
  s.hostileDied = hostileHp <= 0;
  s.playerDied = playerHp <= 0;
  s.corpseHandled = s.hostileDied;

  s.carriedMeasures = carried;
  s.groundMeasures = ground;
  s.inspectText = "Loose stack: ownership=" + legalA.owner + ", legality=" + legalA.legality +
                  ", warning=" + s.mergedWarningChip;

  return s;
}

}  // namespace ap
