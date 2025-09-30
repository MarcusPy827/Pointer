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

#include "src/utils/utils.h"

#include "3rdparty/nlohmann/json/json.h"
#include "3rdparty/mariusbancila/stduuid/uuid.h"

#include "src/proto_gen/src/proto/utils.pb.h"

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
  if (!uuid_path_raw.result()) {
    result.set_query_result(false);
    result.set_err_msg(uuid_path_raw.err_msg());
    return result;
  }

  try {
    std::ifstream json_file(uuid_path_raw.path());
    nlohmann::json json_read;
    json_file >> json_read;
    std::string user_uuid = json_read["user_uuid"].get<std::string>();
    if (user_uuid.empty()) {
      err_msg = absl::StrCat("Bad luck, user uuid is empty. This could be ",
        "caused by a bad initialization.");
      result.set_query_result(false);
      result.set_err_msg(err_msg);
      return result;
    }

    result.set_query_result(true);
    result.set_result_string(user_uuid);
    return result;
  } catch (const std::filesystem::filesystem_error& e) {
    err_msg = absl::StrCat(
      "A filesystem error occurred during geting uuid. ",
      absl::StrFormat("The backend returned: %s", e.what()));
    result.set_query_result(false);
    result.set_err_msg(err_msg);
    return result;
  } catch (const std::exception& e) {
    err_msg = absl::StrCat(
      "An exception occurred during getting uuid. ",
      absl::StrFormat("The backend returned: %s", e.what()));
    result.set_query_result(false);
    result.set_err_msg(err_msg);
    return result;
  } catch (...) {
    err_msg = absl::StrCat(
      "An unknown error occurred during getting uuid, aborting...");
    result.set_query_result(false);
    result.set_err_msg(err_msg);
    return result;
  }

  err_msg = absl::StrCat(
    "An unknown error occurred during getting uuid, aborting...");
  result.set_query_result(false);
  result.set_err_msg(err_msg);
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

int64_t Utils::GetCurrentTimestamp() {
  time_t current_timestamp;
  time(&current_timestamp);
  int64_t result = static_cast<int64_t>(current_timestamp);
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
    if (std::filesystem::is_regular_file(path, err_code)) {
      if (err_code) {
        std::string err_msg = "Failed to check directory. ";
        absl::StrAppend(&err_msg, "An error occurred.\n");
        absl::StrAppend(&err_msg, absl::StrFormat("Error code: %d.\n",
          err_code.value()));
        absl::StrAppend(&err_msg, absl::StrFormat("Error message: %s.\n",
          err_code.message()));

        result.set_result(false);
        result.set_err_msg(err_msg);
        return result;
      }

      err_msg = absl::StrCat("The folder already exists.");
      result.set_result(true);
      result.set_err_msg(err_msg);
      return result;
    } else {
      err_msg = absl::StrCat("The folder does NOT exist.");
      result.set_result(false);
      result.set_err_msg(err_msg);
      return result;
    }
  } catch (const std::filesystem::filesystem_error& e) {
    err_msg = absl::StrCat(
      "A filesystem error occurred during directory check. ",
      absl::StrFormat("The backend returned: %s", e.what()));
    result.set_result(false);
    result.set_err_msg(err_msg);
    return result;
  } catch (const std::exception& e) {
    err_msg = absl::StrCat(
      "An exception occurred during directory check. ",
      absl::StrFormat("The backend returned: %s", e.what()));
    result.set_result(false);
    result.set_err_msg(err_msg);
    return result;
  } catch (...) {
    err_msg = absl::StrCat(
      "An unknown error occurred during directory check, aborting...");
    result.set_result(false);
    result.set_err_msg(err_msg);
    return result;
  }
}

PathHandlerPathResult Utils::FileExists(std::string path) {
  PathHandlerPathResult result;
  std::string err_msg;
  std::error_code err_code;

  try {
    if (std::filesystem::is_regular_file(path, err_code)) {
      if (err_code) {
        std::string err_msg = "Failed to check directory. ";
        absl::StrAppend(&err_msg, "An error occurred.\n");
        absl::StrAppend(&err_msg, absl::StrFormat("Error code: %d.\n",
          err_code.value()));
        absl::StrAppend(&err_msg, absl::StrFormat("Error message: %s.\n",
          err_code.message()));

        result.set_result(false);
        result.set_err_msg(err_msg);
        return result;
      }

      err_msg = absl::StrCat("The file already exists.");
      result.set_result(true);
      result.set_err_msg(err_msg);
      return result;
    } else {
      err_msg = absl::StrCat("The file does NOT exist.");
      result.set_result(false);
      result.set_err_msg(err_msg);
      return result;
    }
  } catch (const std::filesystem::filesystem_error& e) {
    err_msg = absl::StrCat(
      "A filesystem error occurred during file check. ",
      absl::StrFormat("The backend returned: %s", e.what()));
      result.set_result(false);
      result.set_err_msg(err_msg);
    return result;
  } catch (const std::exception& e) {
    err_msg = absl::StrCat(
      "An exception occurred during file check. ",
      absl::StrFormat("The backend returned: %s", e.what()));
      result.set_result(false);
      result.set_err_msg(err_msg);
    return result;
  } catch (...) {
    err_msg = absl::StrCat(
      "An unknown error occurred during file check, aborting...");
    result.set_result(false);
    result.set_err_msg(err_msg);
    return result;
  }
  err_msg = absl::StrCat(
    "An unknown error occurred during file check, aborting...");
  result.set_result(false);
  result.set_err_msg(err_msg);
  return result;
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
        err_msg = absl::StrCat("Could not find path of \"AppData\".");
        result.set_result(false);
        result.set_err_msg(err_msg);
        return result;
      } else {
        parent_folder = std::filesystem::path(app_data_path);
      }
      break;
    }

    case pointer::utils::SystemType::kMacOS: {
      const char* home_path = std::getenv("HOME");
      if (!home_path) {
        err_msg = absl::StrCat("Could not find path of \"Home\".");
        result.set_result(false);
        result.set_err_msg(err_msg);
        return result;
      } else {
        parent_folder = std::filesystem::path(home_path) / "Library" /
          "Application Support";
      }
      break;
    }

    case pointer::utils::SystemType::kUnixLike: {
      const char* xdg_home_path = std::getenv("HOME");
      if (!xdg_home_path) {
        err_msg = absl::StrCat("Could not find path of \"Home\".");
        result.set_result(false);
        result.set_err_msg(err_msg);
        return result;
      } else {
        parent_folder = std::filesystem::path(xdg_home_path) / ".config";
      }
      break;
    }

    default: {
      err_msg = absl::StrCat("Could not find application config path.");
        result.set_result(false);
        result.set_err_msg(err_msg);
      return result;
      break;
    }
  }

  std::filesystem::path result_gen = parent_folder / kApplicationName;
  result.set_path(result_gen.string());

  if (!std::filesystem::is_directory(result.path(), err_code)) {
    if (err_code) {
      err_msg = absl::StrFormat(
        "Failed to check directory \"%s\". ", result.path());
      absl::StrAppend(&err_msg, "An error occurred.\n  ");
      absl::StrAppend(&err_msg, absl::StrFormat("Error code: %d.\n  ",
        err_code.value()));
      absl::StrAppend(&err_msg, absl::StrFormat("Error message: %s.\n  ",
        err_code.message()));

      
      result.set_result(false);
      result.set_err_msg(err_msg);
      return result;
    }

    if (std::filesystem::create_directories(result.path(), err_code)) {
      if (err_code) {
        err_msg = absl::StrFormat(
        "Failed to create directory \"%s\". ", result.path());
        absl::StrAppend(&err_msg, "An error occurred.\n  ");
        absl::StrAppend(&err_msg, absl::StrFormat("Error code: %d.\n  ",
          err_code.value()));
        absl::StrAppend(&err_msg, absl::StrFormat("Error message: %s.\n",
          err_code.message()));

        
        result.set_result(false);
        result.set_err_msg(err_msg);
        return result;
      }

      std::string result_msg = absl::StrFormat(
        "Successfully created the directory \"%s\".", result.path());
      result.set_result(true);
      result.set_err_msg(result_msg);
    }
  }

  if (!std::filesystem::is_directory(result.path(), err_code)) {
    if (err_code) {
      err_msg = absl::StrFormat(
        "Failed to check directory \"%s\". ", result.path());
      absl::StrAppend(&err_msg, "An error occurred.\n  ");
      absl::StrAppend(&err_msg, absl::StrFormat("Error code: %d.\n  ",
        err_code.value()));
      absl::StrAppend(&err_msg, absl::StrFormat("Error message: %s.\n  ",
        err_code.message()));

      result.set_result(false);
      result.set_err_msg(err_msg);
      return result;
    }

    err_msg = absl::StrFormat(
      "Failed to create directory \"%s\". ", result.path());
    result.set_result(false);
    result.set_err_msg(err_msg);
    return result;
  }

  result.set_result(true);
  return result;
}

PathHandlerPathResult Utils::GetUserUUIDPath() {
  PathHandlerPathResult result;
  std::string err_msg;
  std::filesystem::path result_path;
  std::error_code err_code;

  auto config_path = GetConfigPath();
  if (!config_path.result()) {
    return config_path;
  }

  try {
    result_path = std::filesystem::path(config_path.path()) / "user.json";
    auto file_existance_test_result = FileExists(result_path.string());
    if (!file_existance_test_result.result()) {
      std::string user_uuid = uuids::to_string(
        uuids::uuid_system_generator {}());
      nlohmann::json uuid_content;
      uuid_content["user_uuid"] = user_uuid;
      std::string file_content = uuid_content.dump(2);

      std::ofstream file_stream(result_path, std::ios::out | std::ios::trunc);
      if (!file_stream) {
        err_msg = absl::StrFormat("Cannot open config file \"%s\".",
          result_path);
        result.set_result(false);
        result.set_err_msg(err_msg);
        return result;
      }

      file_stream.write(file_content.data(), static_cast<std::streamsize>
        (file_content.size()));
      file_stream.flush();
      file_stream.close();
    }

    file_existance_test_result = FileExists(result_path.string());
    if (!file_existance_test_result.result()) {
      return file_existance_test_result;
    }

    result.set_result(true);
    result.set_path(result_path.string());
    return result;
  } catch (const std::filesystem::filesystem_error& e) {
    err_msg = absl::StrCat(
      "A filesystem error occurred during uuid path check. ",
      absl::StrFormat("The backend returned: %s", e.what()));
    result.set_result(false);
    result.set_err_msg(err_msg);
    return result;
  } catch (const std::exception& e) {
    err_msg = absl::StrCat(
      "An exception occurred during uuid path check. ",
      absl::StrFormat("The backend returned: %s", e.what()));
    result.set_result(false);
    result.set_err_msg(err_msg);
    return result;
  } catch (...) {
    err_msg = absl::StrCat(
      "An unknown error occurred during uuid path check, aborting...");
    result.set_result(false);
    result.set_err_msg(err_msg);
    return result;
  }

  err_msg = absl::StrCat(
    "An unknown error occurred during uuid path check, aborting...");
  result.set_result(false);
  result.set_err_msg(err_msg);
  return result;
}

GenericQueryResult Utils::GetUsername() {
  GenericQueryResult result;

  auto config_path = GetConfigPath();
  if (!config_path.result()) {
    result.set_query_result(false);
    result.set_err_msg(config_path.err_msg());
    return result;
  }

  std::filesystem::path user_config_path = std::filesystem::path(config_path
    .path()) / "user.json";
  auto file_existance_test_result = FileExists(user_config_path.string());
  if (!file_existance_test_result.result()) {
    if (file_existance_test_result.err_msg() != "The file does NOT exist.") {
      result.set_query_result(false);
      result.set_err_msg(file_existance_test_result.err_msg());
      return result;
    } else {
      // If user.json does NOT exist, create it and generate user UUID before
      // continuing...
      GetUserUUIDPath();
    }
  }

  try {
    std::ifstream user_config(user_config_path.string());
    nlohmann::json user_config_read = nlohmann::json::parse(user_config);
    if (user_config_read.contains("user_name")) {
      result.set_query_result(true);
      result.set_result_string(user_config_read.at("user_name")
        .get<std::string>());
      return result;
    } else {
      user_config_read["user_name"] = kDefaultUsername;
      std::ofstream file_stream(user_config_path.string(), std::ios::out |
        std::ios::trunc);
      if (!file_stream) {
        result.set_query_result(false);
        result.set_err_msg(absl::StrCat(absl::StrFormat(
          "Cannot open config file \"%s\".", user_config_path)));
        return result;
      }

      std::string file_content = user_config_read.dump(2);
      file_stream.write(file_content.data(), static_cast<std::streamsize>
        (file_content.size()));
      file_stream.flush();
      file_stream.close();

      result.set_query_result(true);
      result.set_result_string(kDefaultUsername.data());
      return result;
    }
  } catch (const std::filesystem::filesystem_error& e) {
    result.set_query_result(false);
    result.set_err_msg(absl::StrCat(
      "A filesystem error occurred during user name check. ",
      absl::StrFormat("The backend returned: %s", e.what())));
    return result;
  } catch (const std::exception& e) {
    result.set_query_result(false);
    result.set_err_msg(absl::StrCat(
      "An exception occurred during user name check. ",
      absl::StrFormat("The backend returned: %s", e.what())));
    return result;
  } catch (...) {
    result.set_query_result(false);
    result.set_err_msg(absl::StrCat(
      "An unknown error occurred during user name check, aborting..."));
    return result;
  }

  result.set_query_result(false);
  result.set_err_msg(absl::StrCat(
      "An unknown error occurred during user name check, aborting..."));
  return result;
}

}  // namespace utils
}  // namespace pointer
