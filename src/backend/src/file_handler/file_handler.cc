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

namespace pointer {
namespace core {

FileHandlerResult FileHandler::CheckDirectoryExists(std::string path,
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

}  // namespace core
}  // namespace pointer
