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

#include <fstream>

#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/log/log.h"

#include "src/utils/utils.h"

#include "3rdparty/nlohmann/json/json.h"

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

  auto uuid_path_raw = path_handler_helper_.GetUserUUIDPath();
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

}  // namespace utils
}  // namespace pointer
