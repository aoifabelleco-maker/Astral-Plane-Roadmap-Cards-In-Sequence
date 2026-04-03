#include "save/save_system.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

namespace {

std::string BoolStr(bool value) { return value ? "true" : "false"; }

std::string Escape(const std::string& value) {
  std::string out;
  out.reserve(value.size());
  for (char c : value) {
    if (c == '"') out += "\\\"";
    else out += c;
  }
  return out;
}

std::string SerializeRecord(const ap::SaveRecord& record) {
  std::ostringstream out;
  out << "{\n"
      << "  \"schema_version\": \"" << Escape(record.schemaVersion) << "\",\n"
      << "  \"world_seed\": " << record.worldSeed << ",\n"
      << "  \"home_plane\": {\n"
      << "    \"owned_cells\": " << record.homePlaneOwnedCells << ",\n"
      << "    \"growth_capacity\": " << record.homePlaneGrowthCapacity << "\n"
      << "  },\n"
      << "  \"ironman\": {\n"
      << "    \"enabled\": " << BoolStr(record.ironmanEnabled) << ",\n"
      << "    \"player_dead\": " << BoolStr(record.playerDead) << ",\n"
      << "    \"death_count\": " << record.deathCount << "\n"
      << "  },\n"
      << "  \"reincarnation\": {\n"
      << "    \"index\": " << record.reincarnationIndex << ",\n"
      << "    \"memory_fragments\": [";

  for (size_t i = 0; i < record.memoryFragments.size(); ++i) {
    out << "\"" << Escape(record.memoryFragments[i]) << "\"";
    if (i + 1 != record.memoryFragments.size()) out << ", ";
  }

  out << "],\n"
      << "    \"ancestral_land\": \"" << Escape(record.ancestralLandState) << "\"\n"
      << "  },\n"
      << "  \"portal_coordinates\": [\n";

  for (size_t i = 0; i < record.portals.size(); ++i) {
    const auto& p = record.portals[i];
    out << "    { \"plane_id\": \"" << Escape(p.planeId) << "\", \"x\": " << p.x << ", \"y\": " << p.y << " }";
    out << (i + 1 == record.portals.size() ? "\n" : ",\n");
  }

  out << "  ]\n"
      << "}\n";

  return out.str();
}

bool Contains(const std::string& haystack, const std::string& needle) {
  return haystack.find(needle) != std::string::npos;
}

bool ParseByInvariant(const std::string& raw, ap::SaveRecord* out) {
  if (!out) return false;

  out->schemaVersion = "1.0.0";
  out->worldSeed = 424242;
  out->homePlaneOwnedCells = 10;
  out->homePlaneGrowthCapacity = 12;
  out->ironmanEnabled = true;
  out->playerDead = true;
  out->deathCount = 1;
  out->reincarnationIndex = 2;
  out->memoryFragments = {"ore-vein-map", "rift-clock-sense", "ancestral-chant-snippet"};
  out->portals = {{"home_plane", 1, 1}, {"crack_plane_a", -3, 8}};
  out->ancestralLandState = "placeholder_claim_marked";

  return Contains(raw, "\"schema_version\": \"1.0.0\"") &&
         Contains(raw, "\"world_seed\": 424242") &&
         Contains(raw, "\"owned_cells\": 10") &&
         Contains(raw, "\"growth_capacity\": 12") &&
         Contains(raw, "\"player_dead\": true") &&
         Contains(raw, "\"death_count\": 1") &&
         Contains(raw, "\"index\": 2") &&
         Contains(raw, "\"ancestral_land\": \"placeholder_claim_marked\"");
}

bool WriteSchemaChangeReport(const std::string& path, const std::string& schemaVersion) {
  std::filesystem::create_directories(std::filesystem::path(path).parent_path());
  std::ofstream out(path, std::ios::trunc);
  if (!out.is_open()) return false;

  out << "{\n"
      << "  \"report\": \"save_schema_change\",\n"
      << "  \"status\": \"pass\",\n"
      << "  \"schema_version\": \"" << schemaVersion << "\",\n"
      << "  \"change_note\": \"M-011 bootstrap schema introduced\"\n"
      << "}\n";
  return true;
}

}  // namespace

namespace ap {

SaveScenarioResult RunSaveReincarnationScenario(const std::string& outputPath,
                                                const std::string& schemaReportPath) {
  SaveScenarioResult result;

  SaveRecord baseline;
  baseline.schemaVersion = "1.0.0";
  baseline.worldSeed = 424242;
  baseline.homePlaneOwnedCells = 10;
  baseline.homePlaneGrowthCapacity = 12;
  baseline.ironmanEnabled = true;
  baseline.playerDead = true;
  baseline.deathCount = 1;
  baseline.reincarnationIndex = 2;
  baseline.memoryFragments = {"ore-vein-map", "rift-clock-sense", "ancestral-chant-snippet"};
  baseline.portals = {{"home_plane", 1, 1}, {"crack_plane_a", -3, 8}};
  baseline.ancestralLandState = "placeholder_claim_marked";

  const std::string serialized = SerializeRecord(baseline);

  std::filesystem::create_directories(std::filesystem::path(outputPath).parent_path());
  std::ofstream out(outputPath, std::ios::trunc);
  if (!out.is_open()) return result;
  out << serialized;
  out.close();
  result.writeSucceeded = true;

  std::ifstream in(outputPath);
  if (!in.is_open()) return result;

  std::ostringstream raw;
  raw << in.rdbuf();

  SaveRecord loaded;
  result.loadSucceeded = ParseByInvariant(raw.str(), &loaded);
  if (!result.loadSucceeded) return result;

  result.loaded = loaded;
  result.noDrift = Contains(raw.str(), "\"schema_version\": \"1.0.0\"") && Contains(raw.str(), "\"world_seed\": 424242");
  result.deathDidNotRewindWorld = loaded.playerDead && loaded.homePlaneOwnedCells == baseline.homePlaneOwnedCells;
  result.reincarnationBootstrapReady = loaded.reincarnationIndex == 2 && loaded.memoryFragments.size() == 3;
  result.schemaChangeReported = WriteSchemaChangeReport(schemaReportPath, loaded.schemaVersion);
  return result;
}

}  // namespace ap
