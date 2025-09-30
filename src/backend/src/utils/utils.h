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

#ifndef SRC_BACKEND_SRC_UTILS_UTILS_H_
#define SRC_BACKEND_SRC_UTILS_UTILS_H_

#include <string>
#include <vector>

#include "src/proto_gen/src/proto/utils.pb.h"

namespace pointer {
namespace utils {

enum class SystemType {
  kWindows,
  kMacOS,
  kUnixLike
};

class Utils {
 public:
  static SystemType GetSystemType();

  GenericQueryResult GetUserUuid();

  static std::string GetCurrentUtcTime();

  static int64_t GetCurrentTimestamp();

  std::string GetBackendVersionString();

  double GetBackendVersion();

  std::string GetCompactableWithMinBackendVersionString();

  double GetCompactableWithMinBackendVersion();

  PathHandlerPathResult FolderExists(std::string path);

  PathHandlerPathResult FileExists(std::string path);

  PathHandlerPathResult GetConfigPath();

  PathHandlerPathResult GetUserUUIDPath();

  GenericQueryResult GetUsername();

 private:
  std::string backend_version_string_ = "1.0.0";

  double backend_version_ = 1.0;

  std:: string compactable_with_min_backend_version_string_ = "1.0.0";

  double compactable_with_min_backend_version_ = 1.0;

  const std::string_view kApplicationName = "marcus.pointer.app";

  const std::string_view kDefaultUsername = "%NO_NAME%";
};

}  // namespace utils
}  // namespace pointer

#endif  // SRC_BACKEND_SRC_UTILS_UTILS_H_
