#pragma once

#include <string>
#include <vector>

namespace ap {

struct ContentLoadResult {
  bool ok;
  std::string error;
  std::vector<std::string> loadedModules;
  std::vector<std::string> loadedIds;
  std::string checksum;
};

ContentLoadResult LoadAndAuditContent(const std::string& moduleOrderPath);

}  // namespace ap
