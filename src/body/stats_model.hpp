#pragma once

#include <string>

namespace ap {

struct PrimaryStats {
  int str;
  int per;
  int end;
  int agi;
  int wil;
};

struct BodyTemplate {
  std::string id;
  int baselineStamina;
  int collapseThresholdStamina;
};

struct DerivedStats {
  int carryCapacityKg;
  double encumbranceRatio;
  int encumbrancePenalty;
  int staminaMax;
  int staminaDrainPerTick;
  bool collapseRisk;
  int visionRadiusTiles;
  int awarenessRadiusTiles;
};

struct BodyLawSummary {
  bool strAffectsCarryInPractice;
  int carryCapacityAtStr5;
  int carryCapacityAtStr10;
  bool perAffectsSightInPractice;
  int visionAtPer4;
  int visionAtPer10;
  bool staminaDrainVisible;
  int staminaDrainTick;
  bool overloadVisible;
  bool characterPanelReady;
};

BodyTemplate HumanMortalTemplate();
BodyTemplate HumanCultivatorTemplate();
DerivedStats ComputeDerivedStats(const BodyTemplate& body, const PrimaryStats& primary,
                                 double carriedMassKg, int currentStamina);
BodyLawSummary BuildBodyLawSummary();

}  // namespace ap
