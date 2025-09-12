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

#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include <typeinfo>

#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"

#include "src/file_handler/file_handler.h"
#include "3rdparty/nlohmann/json/json.h"

namespace pointer {
namespace core {

FileHandlerResult FileHandler::FolderExists(std::string path) {
  FileHandlerResult result;
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

        result.msg = err_msg;
        return result;
      }

      err_msg = absl::StrCat("🔍 The folder already exists.");
      result.result = true;
      result.msg = err_msg;
      return result;
    } else {
      err_msg = absl::StrCat("🔍 The folder does NOT exist.");
      result.result = false;
      result.msg = err_msg;
      return result;
    }
  } catch (const std::filesystem::filesystem_error& e) {
    err_msg = absl::StrFormat(
      "⛔ A filesystem error occurred during directory check. "
      "The backend returned: %s",
      e.what());
    result.msg = err_msg;
    return result;
  } catch (const std::exception& e) {
    err_msg = absl::StrFormat(
      "⛔ An exception occurred during directory check. "
      "The backend returned: %s",
      e.what());
    result.msg = err_msg;
    return result;
  } catch (...) {
    err_msg = absl::StrCat(
      "⛔ An unknown error occurred during directory check, aborting...");
    result.msg = err_msg;
    return result;
  }

  err_msg = absl::StrCat(
      "⛔ An unknown error occurred during directory check, aborting...");
  result.msg = err_msg;
  return result;
}

FileHandlerResult FileHandler::FileExists(std::string path) {
  FileHandlerResult result;
  std::string err_msg;
  std::error_code err_code;

  try {
    if (std::filesystem::is_regular_file(path, err_code)) {
      if (err_code) {
        std::string err_msg = "❌ Failed to check directory. ";
        absl::StrAppend(&err_msg, "An error occurred.\n");
        absl::StrAppend(&err_msg, absl::StrFormat("Error code: %d.\n",
          err_code.value()));
        absl::StrAppend(&err_msg, absl::StrFormat("Error message: %s.\n",
          err_code.message()));

        result.msg = err_msg;
        return result;
      }

      err_msg = absl::StrCat("🔍 The file already exists.");
      result.result = true;
      result.msg = err_msg;
      return result;
    } else {
      err_msg = absl::StrCat("🔍 The file does NOT exist.");
      result.result = false;
      result.msg = err_msg;
      return result;
    }
  } catch (const std::filesystem::filesystem_error& e) {
    err_msg = absl::StrFormat(
      "⛔ A filesystem error occurred during directory check. "
      "The backend returned: %s",
      e.what());
    result.msg = err_msg;
    return result;
  } catch (const std::exception& e) {
    err_msg = absl::StrFormat(
      "⛔ An exception occurred during directory check. "
      "The backend returned: %s",
      e.what());
    result.msg = err_msg;
    return result;
  } catch (...) {
    err_msg = absl::StrCat(
      "⛔ An unknown error occurred during directory check, aborting...");
    result.msg = err_msg;
    return result;
  }

  err_msg = absl::StrCat(
      "⛔ An unknown error occurred during directory check, aborting...");
  result.msg = err_msg;
  return result;
}

FileHandlerResult FileHandler::CheckIsDirectoryExists(std::string path,
    bool create_mode) {
  FileHandlerResult result;

  if (path.empty()) {
    std::string err_msg =
      "❌ No path is specified, could NOT check if the folder exists";
    result.msg = err_msg;
    return result;
  }

  std::filesystem::path folder_path = path;
  std::error_code err_code;

  if (std::filesystem::is_directory(folder_path, err_code)) {
    if (err_code) {
      std::string err_msg = "❌ Failed to check directory. ";
      absl::StrAppend(&err_msg, "An error occurred.\n");
      absl::StrAppend(&err_msg, absl::StrFormat("Error code: %d.\n",
        err_code.value()));
      absl::StrAppend(&err_msg, absl::StrFormat("Error message: %s.\n",
        err_code.message()));

      result.msg = err_msg;
      return result;
    }

    std::string result_msg = "✔ The folder exists. ";
    if (create_mode) {
      absl::StrAppend(&result_msg, "There is no need to create it.");
    }

    result.result = true;
    result.msg = result_msg;
    return result;
  }

  if (std::filesystem::exists(path, err_code)) {
    std::string err_msg =
      "❌ The path given is a file, and it is NOT directory.";
    result.msg = err_msg;
    return result;
  }

  if (!create_mode) {
    std::string err_msg = "❌ The given directory does NOT exist.";
    result.msg = err_msg;
    return result;
  }

  if (!std::filesystem::create_directories(path, err_code)) {
    if (err_code) {
      std::string err_msg = "❌ Failed to check directory. ";
      absl::StrAppend(&err_msg, "An error occurred.\n");
      absl::StrAppend(&err_msg, absl::StrFormat("Error code: %d.\n",
        err_code.value()));
      absl::StrAppend(&err_msg, absl::StrFormat("Error message: %s.\n",
        err_code.message()));

      result.msg = err_msg;
      return result;
    }
  }

  std::string result_msg = absl::StrFormat(
      "📂 Successfully created the directory \"%s\".", path);
  result.result = true;
  result.msg = result_msg;
  return result;
}

FileHandlerResult FileHandler::CheckIsDirectoryEmpty(std::string path,
    bool ignore_hidden_files, bool create_mode) {
  FileHandlerResult result;
  bool is_hidden_file_accessed = false;
  std::string err_msg;

  try {
    auto is_folder_exist = CheckIsDirectoryExists(path, create_mode);
    if (!is_folder_exist.result) {
      return is_folder_exist;
    }

    for (const auto& entry : std::filesystem::directory_iterator(path)) {
      std::string current_filename = entry.path().filename().string();

      if (current_filename.empty()) {
        continue;
      } else if (ignore_hidden_files && !current_filename.empty() &&
          current_filename[0] == '.') {
        is_hidden_file_accessed = true;
        continue;
      }

      err_msg = absl::StrCat("❌ The directory is NOT empty!!");
      result.msg = err_msg;
      return result;
    }

    result.result = true;
    return result;
  } catch (const std::filesystem::filesystem_error& e) {
    err_msg = absl::StrFormat(
      "⛔ A filesystem error occurred during directory check. "
      "The backend returned: %s",
      e.what());
    result.msg = err_msg;
    return result;
  } catch (const std::exception& e) {
    err_msg = absl::StrFormat(
      "⛔ An exception occurred during directory check. "
      "The backend returned: %s",
      e.what());
    result.msg = err_msg;
    return result;
  } catch (...) {
    err_msg = absl::StrCat(
      "⛔ An unknown error occurred during directory check, aborting...");
    result.msg = err_msg;
    return result;
  }

  err_msg = absl::StrCat(
      "⛔ An unknown error occurred during directory check, aborting...");
  result.msg = err_msg;
  return result;
}

FileHandlerResult FileHandler::CreateWorkSpace(std::string path,
    std::string name) {
  FileHandlerResult result;
  std::string err_msg;
  std::error_code err_code;

  const std::filesystem::path kWorkspaceFolderPath = path;
  const std::filesystem::path kDataFolderPath = ".pointer";
  const std::filesystem::path kWorkspaceDataPath = kWorkspaceFolderPath /
    kDataFolderPath;
  const std::filesystem::path kWorkspaceConfigFileName = "config.json";
  const std::filesystem::path kWorkspaceConfigFilePath = kWorkspaceDataPath /
    kWorkspaceConfigFileName;

  try {
    auto directory_empty_test_result = CheckIsDirectoryEmpty(path, true, true);
    if (!directory_empty_test_result.result) {
      return directory_empty_test_result;
    }

    auto workspace_data_path_existence_test_result = FolderExists(
      kWorkspaceDataPath.string());
    if (workspace_data_path_existence_test_result.result) {
      if (workspace_data_path_existence_test_result.msg ==
          "🔍 The folder already exists.") {
        err_msg = "❌ Workspace data folder already exists, make sure that you "
          "are using an empty folder.";
      } else {
        err_msg = workspace_data_path_existence_test_result.msg;
      }

      result.msg = err_msg;
      return result;
    }

    auto workspace_folder_create = CheckIsDirectoryExists(
      kWorkspaceDataPath.string(), true);
    if (!workspace_folder_create.result) {
      return workspace_folder_create;
    }

    auto workspace_data_file_existence_test_result = FileExists(
      kWorkspaceConfigFilePath.string());
    if (workspace_data_file_existence_test_result.result) {
      if (workspace_data_file_existence_test_result.msg ==
          "🔍 The file already exists.") {
        err_msg = "❌ Workspace config file already exists, make sure that you "
          "are using an empty folder.";
      } else {
        err_msg = workspace_data_file_existence_test_result.msg;
      }

      result.msg = err_msg;
      return result;
    }

    auto owner_id = utils_helper_.GetUserUuid();
    if (!owner_id.query_result) {
      result.msg = owner_id.err_msg;
      return result;
    }

    nlohmann::json json_gen;
    json_gen["name"] = name;
    json_gen["owners"] = owner_id.result_string;

    json_gen["time"] = {
      { "created_at", utils_helper_.GetCurrentTimestamp() },
      { "config_updated_at", utils_helper_.GetCurrentTimestamp() }
    };

    json_gen["versions"] = {
      { "created_version", utils_helper_.GetBackendVersion() },
      { "min_compatible_version", utils_helper_
          .GetCompactableWithMinBackendVersion() }
    };

    std::ofstream config_stream(kWorkspaceConfigFilePath);
    config_stream << std::setw(2) << json_gen << std::endl;
    config_stream.close();

    result.result = true;
    return result;
  } catch (const std::filesystem::filesystem_error& e) {
    err_msg = absl::StrCat(
      "⛔ A filesystem error occurred during directory check. ",
      absl::StrFormat("The backend returned: %s", e.what()));
    result.msg = err_msg;
    return result;
  } catch (const std::exception& e) {
    err_msg = absl::StrCat(
      "⛔ An exception occurred during directory check. ",
      absl::StrFormat("The backend returned: %s", e.what()));
    result.msg = err_msg;
    return result;
  } catch (...) {
    err_msg = absl::StrCat(
      "⛔ An unknown error occurred during directory check, aborting...");
    result.msg = err_msg;
    return result;
  }
  err_msg = absl::StrCat(
    "⛔ An unknown error occurred during directory check, aborting...");
  result.msg = err_msg;
  return result;
}

WorkspaceInfoQueryPayload FileHandler::OpenWorkSpace(std::string path) {
  WorkspaceInfoQueryPayload result;
  if (path.empty()) {
    result.err_code = 1;
    result.err_msg = absl::StrCat("⛔ The workspace path is empty, aborting...");
    return result;
  }

  auto workspace_existance_test = FolderExists(path);
  if (!workspace_existance_test.result) {
    if (workspace_existance_test.msg == "🔍 The folder does NOT exist.") {
      result.err_code = 2;
      result.err_msg = absl::StrCat("⛔ The workspace folder does NOT exist, ",
        "aborting...");
      return result;
    } else {
      result.err_code = -1;
      result.err_msg = workspace_existance_test.msg;
    }
  }

  std::filesystem::path workspace_path = path;
  std::filesystem::path workspace_config_path = workspace_path /
    kWorkspaceConfigFolderName;

  auto workspace_config_existance_test = FolderExists(workspace_config_path
    .string());
  if (!workspace_config_existance_test.result) {
    if (workspace_config_existance_test.msg ==
        "🔍 The folder does NOT exist.") {
      result.err_code = 3;
      result.err_msg = absl::StrCat("⛔ The workspace config folder does NOT ",
        "exist, aborting...");
      return result;
    } else {
      result.err_code = -1;
      result.err_msg = workspace_config_existance_test.msg;
    }
  }

  std::filesystem::path workspace_metadata_path = workspace_config_path /
    kWorkspaceConfigFileName;

  auto workspace_metadata_existance_test = FileExists(workspace_metadata_path
    .string());
  if (!workspace_metadata_existance_test.result) {
    if (workspace_metadata_existance_test.msg ==
        "🔍 The file does NOT exist.") {
      result.err_code = 4;
      result.err_msg = absl::StrCat("⛔ The workspace metadata file does NOT ",
        "exist, aborting...");
      return result;
    } else {
      result.err_code = -1;
      result.err_msg = workspace_metadata_existance_test.msg;
    }
  }

  try {
    std::ifstream metadata_stream(workspace_metadata_path);
    nlohmann::json metadata_read = nlohmann::json::parse(metadata_stream);

    auto min_compatible_version = metadata_read.at("versions")
      .at("min_compatible_version").get<double>();
    auto created_version = metadata_read.at("versions")
      .at("created_version").get<double>();

    if (min_compatible_version <= 0) {
      result.err_code = 5;
      result.err_msg = absl::StrCat("⛔ The workspace is created by unknown ",
        "version of Pointer, aborting...");
      return result;
    }
      
    if (min_compatible_version > utils_helper_.GetBackendVersion()) {
      result.err_code = 6;
      result.err_msg = absl::StrCat(
        "💾 The workspace requires a newer version of pointer, aborting");
      return result;
    }

    result.min_compatible_version = min_compatible_version;
    result.version = created_version;
    result.name = metadata_read.at("name").get<std::string>();
    result.owner = metadata_read.at("owners").get<std::string>();
    result.created_at = metadata_read.at("time").at("created_at")
      .get<int64_t>();
    result.config_updated = metadata_read.at("time").at("config_updated_at")
      .get<int64_t>();
    result.query_state = true;
    return result;
  } catch (const std::filesystem::filesystem_error& e) {
    result.err_msg = absl::StrCat(
      "⛔ A filesystem error occurred during workspace check.",
      absl::StrFormat("The backend returned: %s", e.what()));
    result.err_code = -1;
    return result;
  } catch (const std::exception& e) {
    result.err_msg = absl::StrCat(
      "⛔ An exception occurred during workspace check.",
      absl::StrFormat("The backend returned: %s", e.what()));
    result.err_code = -1;
    return result;
  } catch (...) {
    result.err_msg = absl::StrCat(
      "⛔ An unknown error occurred during workspace check, aborting...");
    result.err_code = -1;
    return result;
  }
  result.err_msg = absl::StrCat(
      "⛔ An unknown error occurred during workspace check, aborting...");
    result.err_code = -1;
    return result;
}

}  // namespace core
}  // namespace pointer
