#include "body/stats_model.hpp"

#include <algorithm>
#include <cmath>

namespace ap {

BodyTemplate HumanMortalTemplate() {
  return BodyTemplate{"human_mortal", 100, 5};
}

BodyTemplate HumanCultivatorTemplate() {
  return BodyTemplate{"human_cultivator_placeholder", 120, 8};
}

DerivedStats ComputeDerivedStats(const BodyTemplate& body, const PrimaryStats& primary,
                                 double carriedMassKg, int currentStamina) {
  DerivedStats d{};
  d.carryCapacityKg = 20 + primary.str * 5;
  d.encumbranceRatio = carriedMassKg / static_cast<double>(d.carryCapacityKg);

  if (d.encumbranceRatio <= 1.0) {
    d.encumbrancePenalty = 0;
  } else if (d.encumbranceRatio <= 1.25) {
    d.encumbrancePenalty = 1;
  } else if (d.encumbranceRatio <= 1.5) {
    d.encumbrancePenalty = 2;
  } else {
    d.encumbrancePenalty = 3;
  }

  d.staminaMax = body.baselineStamina + primary.end * 4;
  const int baseDrain = std::max(1, 6 - static_cast<int>(std::floor(primary.end / 3.0)));
  d.staminaDrainPerTick = baseDrain + d.encumbrancePenalty;
  d.visionRadiusTiles = 3 + static_cast<int>(std::floor(primary.per / 2.0));
  d.awarenessRadiusTiles = 2 + static_cast<int>(std::floor(primary.per / 3.0));
  d.collapseRisk = currentStamina <= body.collapseThresholdStamina || d.encumbranceRatio > 1.5;

  return d;
}

BodyLawSummary BuildBodyLawSummary() {
  const auto body = HumanMortalTemplate();
  const PrimaryStats lowStr{5, 6, 6, 5, 5};
  const PrimaryStats highStr{10, 6, 6, 5, 5};
  const PrimaryStats lowPer{7, 4, 6, 5, 5};
  const PrimaryStats highPer{7, 10, 6, 5, 5};

  const auto dLowStr = ComputeDerivedStats(body, lowStr, 80.0, 60);
  const auto dHighStr = ComputeDerivedStats(body, highStr, 80.0, 60);
  const auto dLowPer = ComputeDerivedStats(body, lowPer, 30.0, 60);
  const auto dHighPer = ComputeDerivedStats(body, highPer, 30.0, 60);
  const auto dOverload = ComputeDerivedStats(body, lowStr, 110.0, 4);

  BodyLawSummary s{};
  s.strAffectsCarryInPractice = dLowStr.carryCapacityKg != dHighStr.carryCapacityKg;
  s.carryCapacityAtStr5 = dLowStr.carryCapacityKg;
  s.carryCapacityAtStr10 = dHighStr.carryCapacityKg;
  s.perAffectsSightInPractice = dLowPer.visionRadiusTiles != dHighPer.visionRadiusTiles;
  s.visionAtPer4 = dLowPer.visionRadiusTiles;
  s.visionAtPer10 = dHighPer.visionRadiusTiles;
  s.staminaDrainVisible = dLowStr.staminaDrainPerTick > 0;
  s.staminaDrainTick = dLowStr.staminaDrainPerTick;
  s.overloadVisible = dOverload.collapseRisk;
  s.characterPanelReady = true;
  return s;
}

}  // namespace ap
