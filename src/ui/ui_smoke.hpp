#pragma once

#include <string>

namespace ap {

struct UiShellScenarioResult {
  bool visibleShellShown = false;
  bool enterFromMenuWorked = false;
  bool wasdMovementWorked = false;
  bool cameraFourWayWorked = false;
  bool leftClickInspectWorked = false;
  bool rightClickInteractWorked = false;
  bool escReturnWorked = false;
  bool panelToggleWorked = false;
  int finalX = 0;
  int finalY = 0;
  int finalFacing = 0;
  bool alwaysVisibleTruthsDeclared = false;
  bool keySpineDeclared = false;
  bool modeBeltsDeclared = false;
  bool actionBeltVisible = false;
  bool currentVerbReadable = false;
  bool hoverTruthVisible = false;
  bool buildQuickRowVisible = false;
  bool buildAccessParity = false;
  bool topLeftBodyGrowthVisible = false;
  bool bottomLeftLifeAnchorVisible = false;
  bool bottomRightSpiritAnchorVisible = false;
  bool coreTruthFieldsVisible = false;
  bool radarVisible = false;
  bool markerTaxonomyPresent = false;
  bool markerDistancesReadable = false;
  bool expeditionOverlayReadable = false;
  bool markerCameraBehaviorFourWay = false;
};

bool LaunchVisibleShell();
UiShellScenarioResult RunUiInputCameraScenario();
bool WriteUiRebaseAnchor(const std::string& outputPath);
bool RunUiSmoke(const std::string& outputPath);

}  // namespace ap
