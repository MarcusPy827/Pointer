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

#include "gtest/gtest.h"
#include "absl/log/log.h"
#include "absl/log/check.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_cat.h"

#include "src/file_handler.h"

namespace pointer {
namespace eval {
namespace {
void CreateDirectory(std::string path) {
  std::filesystem::path folder_path = path;
  std::error_code err_code;
  std::string err_msg;

  if (std::filesystem::is_directory(folder_path, err_code)) {
    if (err_code) {
      err_msg = "❌ Failed to check directory. ";
      absl::StrAppend(&err_msg, "An error occurred.\n");
      absl::StrAppend(&err_msg, absl::StrFormat("Error code: %d.\n",
        err_code.value()));
      absl::StrAppend(&err_msg, absl::StrFormat("Error message: %s.\n",
        err_code.message()));
      CHECK(false) << err_msg;
    }

    err_msg =
      absl::StrFormat(
        "❌ Failed to create %s. The path already exists on system. ", path);
    absl::StrAppend(&err_msg,
      "You need to ensure that the working directory is clean.");

    // Crash the test, the folder may be manually created, stop the process so
    // user may have a chance to backup everything in that folder.
    CHECK(false) << err_msg;
  }

  if (std::filesystem::exists(path, err_code)) {
    if (err_code) {
      err_msg = "❌ Failed to check directory. ";
      absl::StrAppend(&err_msg, "An error occurred.\n");
      absl::StrAppend(&err_msg, absl::StrFormat("Error code: %d.\n",
        err_code.value()));
      absl::StrAppend(&err_msg, absl::StrFormat("Error message: %s.\n",
        err_code.message()));
      CHECK(false) << err_msg;
    }

    err_msg = "❌ The path given is an existing file.";
    absl::StrAppend(&err_msg,
      "You need to ensure that the working directory is clean.");
    CHECK(false) << err_msg;
  }

  if (std::filesystem::create_directories(path, err_code)) {
    std::string result_msg = absl::StrFormat(
      "📂 Successfully created the directory \"%s\".", path);
    LOG(INFO) << result_msg;
    return;
  }

  if (err_code) {
    err_msg = "❌ Failed to check directory. ";
    absl::StrAppend(&err_msg, "An error occurred.\n");
    absl::StrAppend(&err_msg, absl::StrFormat("Error code: %d.\n",
      err_code.value()));
    absl::StrAppend(&err_msg, absl::StrFormat("Error message: %s.\n",
      err_code.message()));
  } else {
    err_msg = "❌ Failed to check directory due to an unknown error.";
  }

  // Crash the test due to failure to setup test environment
  CHECK(false) << err_msg;
}

void CreateFile(std::string path) {
  std::filesystem::path folder_path = path;
  std::error_code err_code;
  std::string err_msg;

  if (std::filesystem::exists(path, err_code)) {
    err_msg = "❌ The give file EXISTS, did you forget to cleanup?";
    CHECK(false) << err_msg;
  }

  std::ofstream file(path);
  if (!file.is_open()) {
    err_msg = absl::StrFormat("❌ Could NOT create file \"%s\".", path);
    CHECK(false) << err_msg;
  }

  file << "";
  file.close();
  if (!file.good()) {
    err_msg = absl::StrFormat("❌ Could NOT write to \"%s\".", path);
    CHECK(false) << err_msg;
  }

  std::string result_msg = absl::StrFormat(
    "📄 Successfully created file \"%s\".", path);
  LOG(INFO) << result_msg;
}

bool GetTestResult(FileHandlerResult result) {
  if (!result.msg.empty()) {
    LOG(INFO) << result.msg;
  }

  if (result.result) {
    LOG(INFO) << "🎉 Congrats, current test PASSED.";
    return true;
  } else {
    LOG(ERROR) << "❌ Bad luck, current test FAILED.";
    return false;
  }
}

void ExecAfterScript(std::string path) {
  LOG(INFO) << "🛠 Running afterscript...";

  std::error_code err_code;
  std::string err_msg;

  if (!std::filesystem::exists(path, err_code)) {
    if (err_code) {
      err_msg = "❌ Failed to check directory. ";
      absl::StrAppend(&err_msg, "An error occurred.\n");
      absl::StrAppend(&err_msg, absl::StrFormat("Error code: %d.\n",
        err_code.value()));
      absl::StrAppend(&err_msg, absl::StrFormat("Error message: %s.\n",
        err_code.message()));

      // Crash the test due to failure to setup test environment
      CHECK(false) << err_msg;
    }

    err_msg = absl::StrFormat(
      "❗ The path %s idoes NOT exist BEFORE cleaning. ", path);
    absl::StrAppend(&err_msg, "This is weird, please check MANUALLY.");
    LOG(WARNING) << err_msg;
    return;
  }

  auto execRemove = std::filesystem::remove_all(path, err_code);
  if (err_code) {
    err_msg = "❌ Failed to check directory. ";
    absl::StrAppend(&err_msg, "An error occurred.\n");
    absl::StrAppend(&err_msg, absl::StrFormat("Error code: %d.\n",
      err_code.value()));
    absl::StrAppend(&err_msg, absl::StrFormat("Error message: %s.\n",
      err_code.message()));

    // Crash the test due to failure to setup test environment
    CHECK(false) << err_msg;
  } else {
    std::string result_msg = "🎉 Job succeed.";
    LOG(INFO) << result_msg;
  }
}

const char kFolderPath[] = "./example_path";
}  // namespace

TEST(UtilTest, GetPassedTestResult) {
  FileHandlerResult result_gen;
  result_gen.result = true;
  result_gen.msg = "This is a message from a passed test.";

  EXPECT_TRUE(GetTestResult(result_gen));
}

TEST(UtilTest, GetFailedTestResult) {
  FileHandlerResult result_gen;
  result_gen.result = false;
  result_gen.msg = "This is a message from a failed test.";

  EXPECT_FALSE(GetTestResult(result_gen));
}

TEST(FileHandler, PathExists) {
  CreateDirectory(kFolderPath);
  FileHandler file_handler;
  auto result = file_handler.CheckDirectoryExists(kFolderPath, false);
  ExecAfterScript(kFolderPath);
  EXPECT_TRUE(GetTestResult(result));
}

TEST(FileHandler, PathNOTExists) {
  FileHandler file_handler;
  auto result = file_handler.CheckDirectoryExists(kFolderPath, false);
  EXPECT_FALSE(GetTestResult(result));
}

TEST(FileHandler, PathNOTExistsAndCreate) {
  FileHandler file_handler;
  file_handler.CheckDirectoryExists(kFolderPath, true);
  auto result = file_handler.CheckDirectoryExists(kFolderPath, false);
  ExecAfterScript(kFolderPath);
  EXPECT_FALSE(GetTestResult(result));
}

TEST(FileHandler, PathNOTExistsButFileExist) {
  CreateFile(kFolderPath);
  FileHandler file_handler;
  auto result = file_handler.CheckDirectoryExists(kFolderPath, false);
  ExecAfterScript(kFolderPath);
  EXPECT_FALSE(GetTestResult(result));
}
}  // namespace eval
}  // namespace pointer
