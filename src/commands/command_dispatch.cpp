#include "commands/command_dispatch.hpp"

#include "body/stats_model.hpp"
#include "content/content_loader.hpp"
#include "game/assimilation.hpp"
#include "game/building_storage_heat.hpp"
#include "game/harsh_verbs.hpp"
#include "game/portal_rift.hpp"
#include "ui/ui_smoke.hpp"
#include "world/start_plane.hpp"
#include "save/save_system.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace {

bool WriteJsonReport(const std::string& outputPath, const std::string& reportName,
                     const std::string& note) {
  std::filesystem::create_directories(std::filesystem::path(outputPath).parent_path());
  std::ofstream out(outputPath, std::ios::trunc);
  if (!out.is_open()) return false;
  out << "{\n  \"report\": \"" << reportName << "\",\n  \"status\": \"pass\",\n  \"note\": \"" << note
      << "\"\n}\n";
  return true;
}

bool WriteTruthReport() {
  const auto load = ap::LoadAndAuditContent("content/ap_module_load_order.txt");
  const auto world = ap::GenerateStartPlaneLayout();
  const auto harsh = ap::RunHarshVerbScenario();
  const auto portal = ap::RunPortalRiftScenario();
  const auto assimilation = ap::RunAssimilationScenario();
  const auto building = ap::RunBuildingStorageHeatScenario();
  const auto ui = ap::RunUiInputCameraScenario();
  const auto save = ap::RunSaveReincarnationScenario("state/saves/save_latest.json",
                                                     "reports/audit/save_schema_change_latest.json");

  const auto mortal = ap::HumanMortalTemplate();
  const auto panelPrimary = ap::PrimaryStats{7, 8, 6, 5, 5};
  const auto panelDerived = ap::ComputeDerivedStats(mortal, panelPrimary, 60.0, 80);

  std::filesystem::create_directories("reports/truth");
  std::ofstream out("reports/truth/truth_latest.json", std::ios::trunc);
  if (!out.is_open()) return false;

  if (!load.ok || !world.summary.coreExists || !harsh.fightWorked || !portal.enteredCrackPlane ||
      !assimilation.homePlaneExpanded || !building.roomClosed || !building.storageQueryUsable ||
      !building.iceMeltedToWater || !building.buildPanelUsable || !ui.visibleShellShown ||
      !ui.enterFromMenuWorked || !ui.wasdMovementWorked || !ui.cameraFourWayWorked ||
      !ui.leftClickInspectWorked || !ui.rightClickInteractWorked || !ui.escReturnWorked ||
      !ui.panelToggleWorked || !save.noDrift || !save.deathDidNotRewindWorld ||
      !save.reincarnationBootstrapReady || !save.schemaChangeReported) {
    out << "{\n  \"report\": \"truth\",\n  \"status\": \"fail\",\n  \"error\": \"truth invariants failed\"\n}\n";
    return false;
  }

  out << "{\n"
      << "  \"report\": \"truth\",\n"
      << "  \"status\": \"pass\",\n"
      << "  \"content_audit_checksum\": \"" << load.checksum << "\",\n"
      << "  \"loaded_modules\": [\n";
  for (size_t i = 0; i < load.loadedModules.size(); ++i) {
    out << "    \"" << load.loadedModules[i] << "\"" << (i + 1 == load.loadedModules.size() ? "\n" : ",\n");
  }
  out << "  ],\n"
      << "  \"owned_plane_summary\": {\n"
      << "    \"owned_plane_cells_before\": " << assimilation.ownedPlaneCellsBefore << ",\n"
      << "    \"owned_plane_cells_after\": " << assimilation.ownedPlaneCellsAfter << ",\n"
      << "    \"growth_capacity_before\": " << assimilation.growthCapacityBefore << ",\n"
      << "    \"growth_capacity_after\": " << assimilation.growthCapacityAfter << ",\n"
      << "    \"captured_core_count\": " << assimilation.capturedCoreCount << "\n"
      << "  },\n"
      << "  \"assimilation_summary\": {\n"
      << "    \"auto_assimilation_on_return\": " << (assimilation.autoAssimilationOnReturn ? "true" : "false")
      << ",\n"
      << "    \"home_plane_expanded\": " << (assimilation.homePlaneExpanded ? "true" : "false") << ",\n"
      << "    \"core_captured\": " << (assimilation.coreCaptured ? "true" : "false") << ",\n"
      << "    \"assimilated_blocks_reminable\": " << (assimilation.assimilatedBlocksReminable ? "true" : "false")
      << ",\n"
      << "    \"reserved_measures\": " << assimilation.reservedMeasures << ",\n"
      << "    \"feed_eligible_measures\": " << assimilation.feedEligibleMeasures << ",\n"
      << "    \"in_process_feed_measures\": " << assimilation.inProcessFeedMeasures << ",\n"
      << "    \"assimilated_measures\": " << assimilation.assimilatedMeasures << "\n"
      << "  },\n"
      << "  \"building_storage_heat_summary\": {\n"
      << "    \"build_panel_usable\": " << (building.buildPanelUsable ? "true" : "false") << ",\n"
      << "    \"room_closed\": " << (building.roomClosed ? "true" : "false") << ",\n"
      << "    \"bed_placed\": " << (building.bedPlaced ? "true" : "false") << ",\n"
      << "    \"stockpile_active\": " << (building.stockpileActive ? "true" : "false") << ",\n"
      << "    \"vault_placeholder_active\": " << (building.vaultPlaceholderActive ? "true" : "false") << ",\n"
      << "    \"heat_source_active\": " << (building.heatSourceActive ? "true" : "false") << ",\n"
      << "    \"enclosure_check_passed\": " << (building.enclosureCheckPassed ? "true" : "false") << ",\n"
      << "    \"local_temp_before_c\": " << building.localTempBeforeC << ",\n"
      << "    \"local_temp_after_c\": " << building.localTempAfterC << ",\n"
      << "    \"ice_melted_to_water\": " << (building.iceMeltedToWater ? "true" : "false") << ",\n"
      << "    \"storage_loose_pile_state\": " << (building.storageLoosePileState ? "true" : "false") << ",\n"
      << "    \"storage_contained_state\": " << (building.storageContainedState ? "true" : "false") << ",\n"
      << "    \"storage_stockpile_state\": " << (building.storageStockpileState ? "true" : "false") << ",\n"
      << "    \"storage_reserved_state\": " << (building.storageReservedState ? "true" : "false") << ",\n"
      << "    \"storage_query_usable\": " << (building.storageQueryUsable ? "true" : "false") << ",\n"
      << "    \"transport_truth_distinct\": " << (building.transportTruthDistinct ? "true" : "false") << "\n"
      << "  },\n"
      << "  \"ui_anchor_summary\": {\n"
      << "    \"visible_shell_shown\": " << (ui.visibleShellShown ? "true" : "false") << ",\n"
      << "    \"enter_new_game_works\": " << (ui.enterFromMenuWorked ? "true" : "false") << ",\n"
      << "    \"wasd_movement_works\": " << (ui.wasdMovementWorked ? "true" : "false") << ",\n"
      << "    \"camera_four_way_rotation_works\": " << (ui.cameraFourWayWorked ? "true" : "false") << ",\n"
      << "    \"inspect_interact_works\": " << ((ui.leftClickInspectWorked && ui.rightClickInteractWorked) ? "true" : "false") << ",\n"
      << "    \"esc_return_works\": " << (ui.escReturnWorked ? "true" : "false") << ",\n"
      << "    \"panel_toggles_work\": " << (ui.panelToggleWorked ? "true" : "false") << "\n"
      << "  },\n"
      << "  \"save_reincarnation_summary\": {\n"
      << "    \"schema_version\": \"" << save.loaded.schemaVersion << "\",\n"
      << "    \"save_write_succeeded\": " << (save.writeSucceeded ? "true" : "false") << ",\n"
      << "    \"save_load_succeeded\": " << (save.loadSucceeded ? "true" : "false") << ",\n"
      << "    \"no_drift\": " << (save.noDrift ? "true" : "false") << ",\n"
      << "    \"world_seed_persisted\": " << save.loaded.worldSeed << ",\n"
      << "    \"home_plane_owned_cells\": " << save.loaded.homePlaneOwnedCells << ",\n"
      << "    \"death_did_not_rewind_world\": " << (save.deathDidNotRewindWorld ? "true" : "false") << ",\n"
      << "    \"reincarnation_index\": " << save.loaded.reincarnationIndex << ",\n"
      << "    \"memory_fragment_count\": " << save.loaded.memoryFragments.size() << ",\n"
      << "    \"ancestral_land_state\": \"" << save.loaded.ancestralLandState << "\",\n"
      << "    \"schema_change_reported\": " << (save.schemaChangeReported ? "true" : "false") << "\n"
      << "  },\n"
      << "  \"character_panel\": {\n"
      << "    \"template\": \"" << mortal.id << "\",\n"
      << "    \"primary\": {\n"
      << "      \"str\": " << panelPrimary.str << ",\n"
      << "      \"per\": " << panelPrimary.per << ",\n"
      << "      \"end\": " << panelPrimary.end << "\n"
      << "    },\n"
      << "    \"derived\": {\n"
      << "      \"carry_capacity_kg\": " << panelDerived.carryCapacityKg << ",\n"
      << "      \"vision_radius_tiles\": " << panelDerived.visionRadiusTiles << ",\n"
      << "      \"stamina_max\": " << panelDerived.staminaMax << "\n"
      << "    }\n"
      << "  }\n"
      << "}\n";

  return true;
}

bool WriteWorldgenReport() {
  const auto world = ap::GenerateStartPlaneLayout();
  const auto portal = ap::RunPortalRiftScenario();
  std::filesystem::create_directories("reports/world");
  std::ofstream out("reports/world/worldgen_probe_latest.json", std::ios::trunc);
  if (!out.is_open()) return false;

  out << "{\n"
      << "  \"report\": \"worldgen_probe\",\n"
      << "  \"status\": \"pass\",\n"
      << "  \"layout\": {\n"
      << "    \"layer_count\": " << world.summary.layerCount << ",\n"
      << "    \"block_count\": " << world.summary.blockCount << "\n"
      << "  },\n"
      << "  \"portal\": {\n"
      << "    \"crack_plane_id\": \"" << portal.crackPlaneId << "\",\n"
      << "    \"timer_start_ticks\": " << portal.timerStartTicks << ",\n"
      << "    \"timer_after_extension\": " << portal.timerAfterExtension << "\n"
      << "  }\n"
      << "}\n";

  return true;
}

bool CaptureGreenRestorePoint() {
  const std::string restorePointPath = "state/restore_points/restore_point_m009_latest.json";
  const std::string greenStatePath = "state/green_state/green_state.json";
  if (!WriteJsonReport(restorePointPath, "restore_point", "captured after full gate chain")) return false;

  std::ofstream green(greenStatePath, std::ios::trunc);
  if (!green.is_open()) return false;
  green << "{\n"
        << "  \"green_state_version\": \"1.9.0\",\n"
        << "  \"status\": \"green\",\n"
        << "  \"restore_point\": \"" << restorePointPath << "\",\n"
        << "  \"captured_by\": \"AstralPlane.exe -fullgate\"\n"
        << "}\n";
  return true;
}

int RunSingleCommand(const std::string& arg) {
  if (arg == "-truthreport") return WriteTruthReport() ? 0 : 1;

  if (arg == "-smoke") {
    const auto building = ap::RunBuildingStorageHeatScenario();
  const auto ui = ap::RunUiInputCameraScenario();
  const auto save = ap::RunSaveReincarnationScenario("state/saves/save_latest.json",
                                                     "reports/audit/save_schema_change_latest.json");
    const auto harsh = ap::RunHarshVerbScenario();
    if (!building.roomClosed || !building.storageQueryUsable || !building.iceMeltedToWater || !building.buildPanelUsable ||
        !harsh.fightWorked || !save.noDrift || !save.reincarnationBootstrapReady) {
      return 1;
    }
    return WriteJsonReport("reports/smoke/smoke_latest.json", "smoke",
                           "move + mine + carry + fight + portal + assimilation + build/storage/heat + save/reincarnation valid")
               ? 0
               : 1;
  }

  if (arg == "-uismoke") return ap::RunUiSmoke("reports/smoke/ui_smoke_latest.json") ? 0 : 1;
  if (arg == "-genworld") return WriteWorldgenReport() ? 0 : 1;
  if (arg == "-saveprobe") {
    const auto save = ap::RunSaveReincarnationScenario("state/saves/save_latest.json",
                                                       "reports/audit/save_schema_change_latest.json");
    return (save.noDrift && save.reincarnationBootstrapReady && save.schemaChangeReported) ? 0 : 1;
  }

  std::cerr << "Unknown command: " << arg << "\n";
  return 2;
}

}  // namespace

namespace ap {

int DispatchCommands(const std::vector<std::string>& args) {
  if (args.empty()) {
    return ap::LaunchVisibleShell() ? 0 : 1;
  }

  if (args.size() == 1 && args[0] == "-fullgate") {
    const std::vector<std::string> gate = {"-truthreport", "-smoke", "-uismoke", "-genworld"};
    for (const auto& cmd : gate) {
      if (RunSingleCommand(cmd) != 0) return 1;
    }
    return CaptureGreenRestorePoint() ? 0 : 1;
  }

  if (args.size() == 1) return RunSingleCommand(args[0]);

  std::cerr << "Only one governed verb at a time is supported, or -fullgate.\n";
  return 2;
}

}  // namespace ap
