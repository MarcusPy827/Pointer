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

#define UUID_SYSTEM_GENERATOR

#include <fstream>
#include <iostream>
#include <filesystem>
#include <ctime>
#include <chrono>

#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/log/log.h"

#include "src/utils/utils.h"

#include "3rdparty/nlohmann/json/json.h"
#include "3rdparty/mariusbancila/stduuid/uuid.h"

namespace pointer {
namespace utils {

SystemType Utils::GetSystemType() {
#if defined(_WIN32)
  return SystemType::kWindows;

#elif defined(__APPLE__)
  return SystemType::kMacOS;

#else
  return SystemType::kUnixLike;

#endif
}

GenericQueryResult Utils::GetUserUuid() {
  GenericQueryResult result;
  std::string err_msg;

  auto uuid_path_raw = GetUserUUIDPath();
  if (!uuid_path_raw.result) {
    result.err_msg = uuid_path_raw.err_msg;
    return result;
  }

  try {
    std::ifstream json_file(uuid_path_raw.path);
    nlohmann::json json_read;
    json_file >> json_read;
    std::string user_uuid = json_read["user_uuid"];
    if (user_uuid.empty()) {
      err_msg = absl::StrCat("⛔ Bad luck, user uuid is empty. This could be ",
        "caused by a bad initialization.");
      LOG(ERROR) << err_msg;
      result.err_msg = err_msg;
      return result;
    }

    result.query_result = true;
    result.result = user_uuid;
    return result;
  } catch (const std::filesystem::filesystem_error& e) {
    err_msg = absl::StrCat(
      "⛔ A filesystem error occurred during directory check. ",
      absl::StrFormat("The backend returned: %s", e.what()));
    result.err_msg = err_msg;
    return result;
  } catch (const std::exception& e) {
    err_msg = absl::StrCat(
      "⛔ An exception occurred during directory check. ",
      absl::StrFormat("The backend returned: %s", e.what()));
    result.err_msg = err_msg;
    return result;
  } catch (...) {
    err_msg = absl::StrCat(
      "⛔ An unknown error occurred during directory check, aborting...");
    result.err_msg = err_msg;
    return result;
  }

  err_msg = absl::StrCat(
      "⛔ An unknown error occurred during directory check, aborting...");
  result.err_msg = err_msg;
  return result;
}

// Modified from: https://stackoverflow.com/questions/20619236/
std::string Utils::GetCurrentUtcTime() {
  std::time_t now = std::time(0);
  std::tm* now_tm = std::gmtime(&now);
  char buf[44];
  std::strftime(buf, 44, "%Y-%m-%d %X", now_tm);
  std::string result = buf;
  return result;
}

std::string Utils::GetBackendVersionString() {
  return backend_version_string_;
}

double Utils::GetBackendVersion() {
  return backend_version_;
}

std::string Utils::GetCompactableWithMinBackendVersionString() {
  return compactable_with_min_backend_version_string_;
}

double Utils::GetCompactableWithMinBackendVersion() {
  return compactable_with_min_backend_version_;
}

PathHandlerPathResult Utils::FolderExists(std::string path) {
  PathHandlerPathResult result;
  std::string err_msg;
  std::error_code err_code;

  try {
    if (std::filesystem::is_directory(path, err_code)) {
      if (err_code) {
        std::string err_msg = "❌ Failed to check directory. ";
        absl::StrAppend(&err_msg, "An error occurred.\n");
        absl::StrAppend(&err_msg, absl::StrFormat("Error code: %d.\n",
          err_code.value()));
        absl::StrAppend(&err_msg, absl::StrFormat("Error message: %s.\n",
          err_code.message()));

        LOG(ERROR) << err_msg;
        result.err_msg = err_msg;
        return result;
      }

      err_msg = absl::StrCat("🔍 The folder already exists.");
      LOG(INFO) << err_msg;
      result.result = true;
      result.err_msg = err_msg;
      return result;
    } else {
      err_msg = absl::StrCat("🔍 The folder does NOT exist.");
      result.result = true;
      result.err_msg = err_msg;
      return result;
    }
  } catch (const std::filesystem::filesystem_error& e) {
    err_msg = absl::StrCat(
      "⛔ A filesystem error occurred during directory check. ",
      absl::StrFormat("The backend returned: %s", e.what()));
    result.err_msg = err_msg;
    return result;
  } catch (const std::exception& e) {
    err_msg = absl::StrCat(
      "⛔ An exception occurred during directory check. ",
      absl::StrFormat("The backend returned: %s", e.what()));
    result.err_msg = err_msg;
    return result;
  } catch (...) {
    err_msg = absl::StrCat(
      "⛔ An unknown error occurred during directory check, aborting...");
    result.err_msg = err_msg;
    return result;
  }
}

PathHandlerPathResult Utils::FileExists(std::string path) {
  PathHandlerPathResult result;
  std::string err_msg;
  std::error_code err_code;

  try {
    if (std::filesystem::exists(path, err_code)) {
      if (err_code) {
        std::string err_msg = "❌ Failed to check directory. ";
        absl::StrAppend(&err_msg, "An error occurred.\n");
        absl::StrAppend(&err_msg, absl::StrFormat("Error code: %d.\n",
          err_code.value()));
        absl::StrAppend(&err_msg, absl::StrFormat("Error message: %s.\n",
          err_code.message()));

        LOG(ERROR) << err_msg;
        result.err_msg = err_msg;
        return result;
      }

      err_msg = absl::StrCat("🔍 The file already exists.");
      LOG(INFO) << err_msg;
      result.result = true;
      result.err_msg = err_msg;
      return result;
    } else {
      err_msg = absl::StrCat("🔍 The file does NOT exist.");
      result.result = true;
      result.err_msg = err_msg;
      return result;
    }
  } catch (const std::filesystem::filesystem_error& e) {
    err_msg = absl::StrCat(
      "⛔ A filesystem error occurred during directory check. ",
      absl::StrFormat("The backend returned: %s", e.what()));
    result.err_msg = err_msg;
    return result;
  } catch (const std::exception& e) {
    err_msg = absl::StrCat(
      "⛔ An exception occurred during directory check. ",
      absl::StrFormat("The backend returned: %s", e.what()));
    result.err_msg = err_msg;
    return result;
  } catch (...) {
    err_msg = absl::StrCat(
      "⛔ An unknown error occurred during directory check, aborting...");
    result.err_msg = err_msg;
    return result;
  }
}

PathHandlerPathResult Utils::GetConfigPath() {
  PathHandlerPathResult result;
  pointer::utils::SystemType system_type = GetSystemType();
  std::string err_msg;
  std::filesystem::path parent_folder;
  std::error_code err_code;

  switch (system_type) {
    case pointer::utils::SystemType::kWindows: {
      const char* app_data_path = std::getenv("APPDATA");
      if (!app_data_path) {
        err_msg = absl::StrCat("⛔ Could not find path of \"AppData\".");
        result.err_msg = err_msg;
        return result;
      } else {
        parent_folder = std::filesystem::path(app_data_path);
      }
      break;
    }

    case pointer::utils::SystemType::kMacOS: {
      const char* home_path = std::getenv("HOME");
      if (!home_path) {
        err_msg = absl::StrCat("⛔ Could not find path of \"Home\".");
        result.err_msg = err_msg;
        return result;
      } else {
        parent_folder = std::filesystem::path(home_path) / "Library" /
          "Application Support";
      }
      break;
    }

    case pointer::utils::SystemType::kUnixLike: {
      const char* xdg_home_path = std::getenv("XDG_CONFIG_HOME");
      if (!xdg_home_path) {
        err_msg = absl::StrCat("⛔ Could not find path of \"Home\".");
        result.err_msg = err_msg;
        return result;
      } else {
        parent_folder = std::filesystem::path(xdg_home_path) / ".config";
      }
      break;
    }

    default: {
      err_msg = absl::StrCat("⛔ Could not find application config path.");
      result.err_msg = err_msg;
      return result;
      break;
    }
  }

  result.path = parent_folder / kApplicationName;

  if (!std::filesystem::is_directory(result.path, err_code)) {
    if (err_code) {
      err_msg = absl::StrFormat(
        "❌ Failed to check directory \"%s\". ", result.path);
      absl::StrAppend(&err_msg, "An error occurred.\n  ");
      absl::StrAppend(&err_msg, absl::StrFormat("Error code: %d.\n  ",
        err_code.value()));
      absl::StrAppend(&err_msg, absl::StrFormat("Error message: %s.\n  ",
        err_code.message()));

      LOG(ERROR) << err_msg;
      result.err_msg = err_msg;
      return result;
    }

    LOG(INFO) << "❗ The application config path does NOT exist, "
      "now creating it...";

    if (std::filesystem::create_directories(result.path, err_code)) {
      if (err_code) {
        err_msg = absl::StrFormat(
        "❌ Failed to create directory \"%s\". ", result.path);
        absl::StrAppend(&err_msg, "An error occurred.\n  ");
        absl::StrAppend(&err_msg, absl::StrFormat("Error code: %d.\n  ",
          err_code.value()));
        absl::StrAppend(&err_msg, absl::StrFormat("Error message: %s.\n",
          err_code.message()));

        LOG(ERROR) << err_msg;
        result.err_msg = err_msg;
        return result;
      }

      std::string result_msg = absl::StrFormat(
        "📂 Successfully created the directory \"%s\".", result.path);
      LOG(INFO) << result_msg;
    }
  }

  if (!std::filesystem::is_directory(result.path, err_code)) {
    if (err_code) {
      err_msg = absl::StrFormat(
        "❌ Failed to check directory \"%s\". ", result.path);
      absl::StrAppend(&err_msg, "An error occurred.\n  ");
      absl::StrAppend(&err_msg, absl::StrFormat("Error code: %d.\n  ",
        err_code.value()));
      absl::StrAppend(&err_msg, absl::StrFormat("Error message: %s.\n  ",
        err_code.message()));

      LOG(ERROR) << err_msg;
      result.err_msg = err_msg;
      return result;
    }

    err_msg = absl::StrFormat(
      "❌ Failed to create directory \"%s\". ", result.path);
    LOG(ERROR) << err_msg;
    result.err_msg = err_msg;
    return result;
  }

  result.result = true;
  return result;
}

PathHandlerPathResult Utils::GetUserUUIDPath() {
  PathHandlerPathResult result;
  std::string err_msg;
  std::filesystem::path result_path;
  std::error_code err_code;

  auto config_path = GetConfigPath();
  if (!config_path.result) {
    return config_path;
  }

  try {
    result.path = std::filesystem::path(result.path) / "user.json";
    auto file_existance_test_result = FileExists(result.path);
    if (!file_existance_test_result.result) {
      std::string user_uuid = uuids::to_string(
        uuids::uuid_system_generator {}());
      nlohmann::json uuid_content;
      uuid_content["user_uuid"] = user_uuid;
      std::string file_content = uuid_content.dump(2);

      LOG(INFO) << "❗ User uuid is NOT ready, now initializing it...";

      std::ofstream file_stream(result.path, std::ios::out | std::ios::trunc);
      if (!file_stream) {
        err_msg = absl::StrFormat("⛔ Cannot open config file \"%s\".",
          result.path);
        LOG(ERROR) << err_msg;
        result.err_msg = err_msg;
        return result;
      }

      file_stream << file_content;
      file_stream.close();
      LOG(INFO) << "📄 Successfully created user UUID.";
    }

    file_existance_test_result = FileExists(result.path);
    if (!file_existance_test_result.result) {
      return file_existance_test_result;
    }

    result.result = true;
    return result;
  } catch (const std::filesystem::filesystem_error& e) {
    err_msg = absl::StrCat(
      "⛔ A filesystem error occurred during directory check. ",
      absl::StrFormat("The backend returned: %s", e.what()));
    result.err_msg = err_msg;
    return result;
  } catch (const std::exception& e) {
    err_msg = absl::StrCat(
      "⛔ An exception occurred during directory check. ",
      absl::StrFormat("The backend returned: %s", e.what()));
    result.err_msg = err_msg;
    return result;
  } catch (...) {
    err_msg = absl::StrCat(
      "⛔ An unknown error occurred during directory check, aborting...");
    result.err_msg = err_msg;
    return result;
  }

  err_msg = absl::StrCat(
      "⛔ An unknown error occurred during directory check, aborting...");
  result.err_msg = err_msg;
  return result;
}

}  // namespace utils
}  // namespace pointer
