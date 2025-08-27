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

#include "absl/log/log.h"
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

        LOG(ERROR) << err_msg;
        result.msg = err_msg;
        return result;
      }

      err_msg = absl::StrCat("🔍 The folder already exists.");
      LOG(INFO) << err_msg;
      result.result = true;
      result.msg = err_msg;
      return result;
    } else {
      err_msg = absl::StrCat("🔍 The folder does NOT exist.");
      result.result = true;
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
}

FileHandlerResult FileHandler::FileExists(std::string path) {
  FileHandlerResult result;
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
        result.msg = err_msg;
        return result;
      }

      err_msg = absl::StrCat("🔍 The file already exists.");
      LOG(INFO) << err_msg;
      result.result = true;
      result.msg = err_msg;
      return result;
    } else {
      err_msg = absl::StrCat("🔍 The file does NOT exist.");
      result.result = true;
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
}

FileHandlerResult FileHandler::CheckIsDirectoryExists(std::string path,
    bool create_mode) {
  FileHandlerResult result;

  if (path.empty()) {
    std::string err_msg =
      "❌ No path is specified, could NOT check if the folder exists";
    LOG(ERROR) << err_msg;
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

      LOG(ERROR) << err_msg;
      result.msg = err_msg;
      return result;
    }

    std::string result_msg = "✔ The folder exists. ";
    if (create_mode) {
      absl::StrAppend(&result_msg, "There is no need to create it.");
    }

    LOG(INFO) << result_msg;
    result.result = true;
    result.msg = result_msg;
    return result;
  }

  if (std::filesystem::exists(path, err_code)) {
    std::string err_msg =
      "❌ The path given is a file, and it is NOT directory.";
    LOG(ERROR) << err_msg;
    result.msg = err_msg;
    return result;
  }

  if (!create_mode) {
    std::string err_msg = "❌ The given directory does NOT exist.";
    LOG(ERROR) << err_msg;
    result.msg = err_msg;
    return result;
  }

  LOG(INFO) << "The given directory does NOT exist, now trying to create it...";

  if (std::filesystem::create_directories(path, err_code)) {
    std::string result_msg = absl::StrFormat(
      "📂 Successfully created the directory \"%s\".", path);
    LOG(INFO) << result_msg;
    result.result = true;
    result.msg = result_msg;
    return result;
  }

  if (err_code) {
    std::string err_msg = "❌ Failed to check directory. ";
    absl::StrAppend(&err_msg, "An error occurred.\n");
    absl::StrAppend(&err_msg, absl::StrFormat("Error code: %d.\n",
      err_code.value()));
    absl::StrAppend(&err_msg, absl::StrFormat("Error message: %s.\n",
      err_code.message()));

    LOG(ERROR) << err_msg;
    result.msg = err_msg;
    return result;
  } else {
    std::string err_msg =
      "❌ Failed to check directory due to an unknown error.";
    LOG(ERROR) << err_msg;
    result.msg = err_msg;
    return result;
  }
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
      kWorkspaceDataPath);
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

    auto workspace_data_file_existence_test_result = FileExists(
      kWorkspaceConfigFilePath);
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

    // nlohmann::json json_gen
  } catch(...) {

  }
}

}  // namespace core
}  // namespace pointer
