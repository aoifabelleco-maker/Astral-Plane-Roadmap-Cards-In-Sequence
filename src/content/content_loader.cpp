#include "content/content_loader.hpp"

#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace {

struct Record {
  std::map<std::string, std::string> fields;
};

std::string Trim(const std::string& in) {
  size_t s = 0;
  while (s < in.size() && std::isspace(static_cast<unsigned char>(in[s]))) {
    ++s;
  }
  size_t e = in.size();
  while (e > s && std::isspace(static_cast<unsigned char>(in[e - 1]))) {
    --e;
  }
  return in.substr(s, e - s);
}

bool ParseModule(const std::string& path, std::vector<Record>& out, std::string& error) {
  std::ifstream in(path);
  if (!in.is_open()) {
    error = "Cannot open module: " + path;
    return false;
  }

  std::string line;
  bool inRecord = false;
  Record current;
  int lineNo = 0;

  while (std::getline(in, line)) {
    ++lineNo;
    std::string t = Trim(line);
    if (t.empty() || t[0] == '#') {
      continue;
    }
    if (t == "BEGIN") {
      if (inRecord) {
        error = "Nested BEGIN in " + path;
        return false;
      }
      inRecord = true;
      current = Record{};
      continue;
    }
    if (t == "END") {
      if (!inRecord) {
        error = "END without BEGIN in " + path;
        return false;
      }
      out.push_back(current);
      inRecord = false;
      continue;
    }

    if (!inRecord) {
      error = "Token outside record at " + path + ":" + std::to_string(lineNo);
      return false;
    }

    const auto pos = t.find('=');
    if (pos == std::string::npos) {
      error = "Invalid token (expected key=value) at " + path + ":" + std::to_string(lineNo);
      return false;
    }

    current.fields[Trim(t.substr(0, pos))] = Trim(t.substr(pos + 1));
  }

  if (inRecord) {
    error = "Unclosed record in " + path;
    return false;
  }
  return true;
}

std::string Checksum(const std::vector<std::string>& items) {
  // Simple deterministic bootstrap checksum (not cryptographic).
  uint64_t h = 1469598103934665603ULL;
  for (const auto& item : items) {
    for (const auto c : item) {
      h ^= static_cast<unsigned char>(c);
      h *= 1099511628211ULL;
    }
  }
  std::ostringstream oss;
  oss << std::hex << h;
  return oss.str();
}

bool Has(const Record& r, const std::string& k) {
  const auto it = r.fields.find(k);
  return it != r.fields.end() && !it->second.empty();
}

}  // namespace

namespace ap {

ContentLoadResult LoadAndAuditContent(const std::string& moduleOrderPath) {
  ContentLoadResult result{true, "", {}, {}, ""};

  std::ifstream order(moduleOrderPath);
  if (!order.is_open()) {
    result.ok = false;
    result.error = "Cannot open module load order: " + moduleOrderPath;
    return result;
  }

  std::vector<Record> allRecords;
  std::unordered_map<std::string, std::string> idToKind;
  std::string moduleLine;

  while (std::getline(order, moduleLine)) {
    moduleLine = Trim(moduleLine);
    if (moduleLine.empty() || moduleLine[0] == '#') {
      continue;
    }
    result.loadedModules.push_back(moduleLine);
    std::vector<Record> records;
    std::string parseError;
    if (!ParseModule(moduleLine, records, parseError)) {
      result.ok = false;
      result.error = parseError;
      return result;
    }

    for (const auto& record : records) {
      if (!Has(record, "kind") || !Has(record, "id")) {
        result.ok = false;
        result.error = "Record missing required kind/id in module: " + moduleLine;
        return result;
      }
      const std::string id = record.fields.at("id");
      const std::string kind = record.fields.at("kind");
      if (idToKind.count(id) > 0) {
        result.ok = false;
        result.error = "Duplicate content id: " + id;
        return result;
      }
      idToKind[id] = kind;
      result.loadedIds.push_back(id);
      allRecords.push_back(record);
    }
  }

  for (const auto& record : allRecords) {
    const std::string kind = record.fields.at("kind");

    if (kind == "terrain") {
      if (!Has(record, "material_id")) {
        result.ok = false;
        result.error = "Terrain missing material_id: " + record.fields.at("id");
        return result;
      }
      if (idToKind.count(record.fields.at("material_id")) == 0) {
        result.ok = false;
        result.error = "Terrain material ref missing: " + record.fields.at("material_id");
        return result;
      }
    }

    if (kind == "plane") {
      for (const auto& refKey : {"terrain_id", "core_id", "stat_id"}) {
        if (!Has(record, refKey)) {
          result.ok = false;
          result.error = "Plane missing " + std::string(refKey) + ": " + record.fields.at("id");
          return result;
        }
        if (idToKind.count(record.fields.at(refKey)) == 0) {
          result.ok = false;
          result.error = "Plane ref missing: " + record.fields.at(refKey);
          return result;
        }
      }
    }

    if (kind == "graphics_map") {
      if (!Has(record, "logical_id") || !Has(record, "asset")) {
        result.ok = false;
        result.error = "graphics_map missing logical_id/asset: " + record.fields.at("id");
        return result;
      }
      if (idToKind.count(record.fields.at("logical_id")) == 0) {
        result.ok = false;
        result.error = "graphics_map unresolved logical_id: " + record.fields.at("logical_id");
        return result;
      }
    }
  }

  std::sort(result.loadedModules.begin(), result.loadedModules.end());
  std::sort(result.loadedIds.begin(), result.loadedIds.end());
  result.checksum = Checksum(result.loadedIds);
  return result;
}

}  // namespace ap
