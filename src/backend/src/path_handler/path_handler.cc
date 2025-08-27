/*
 * Copyright 2025 MarcusPy827
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * NOTE: This software comes with ABSOLUTELY NO WARRANTY. Use at your own risk.
 */

#include <filesystem>

#include "absl/strings/str_cat.h"

#include "src/path_handler/path_handler.h"

namespace pointer {
namespace utils {

PathHandlerPathResult PathHandler::GetConfigPath() {
  PathHandlerPathResult result;
  pointer::utils::SystemType system_type = utils_helper_.GetSystemType();
  std::string err_msg;
  std::filesystem::path parent_folder;

  switch (system_type) {
    case pointer::utils::SystemType::kWindows:
      const char* app_data_path = std::getenv("APPDATA");
      if (!app_data_path) {
        err_msg = absl::StrCat("⛔ Could not find path of \"AppData\".");
        result.err_msg = err_msg;
        return result;
      } else {
        parent_folder = std::filesystem::path(app_data_path);
      }
      break;

    case pointer::utils::SystemType::kMacOS:
      const char* home_path = std::getenv("HOME");
      if (!home_path) {
        err_msg = absl::StrCat("⛔ Could not find path of \"Home\".");
        result.err_msg = err_msg;
        return result;
      } else {
        parent_folder = std::filesystem::path(app_data_path) / "Library" /
          "Application Support";
      }
      break;

    case pointer::utils::SystemType::kUnixLike:
      const char* xdg_home_path = std::getenv("XDG_CONFIG_HOME");
      if (!xdg_home_path) {
        err_msg = absl::StrCat("⛔ Could not find path of \"Home\".");
        result.err_msg = err_msg;
        return result;
      } else {
        parent_folder = std::filesystem::path(app_data_path) / ".config";
      }
      break;

    default:
      err_msg = absl::StrCat("⛔ Could not find application config path.");
      result.err_msg = err_msg;
      return result;
      break;
  }

  result.result = true;
  result.path = parent_folder / kApplicationName;
  return result;
}

}  // namespace utils
}  // namespace pointer
