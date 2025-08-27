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

#include "src/path_handler/path_handler.h"

struct GenericQueryResult {
  bool query_result = false;
  std::string err_msg;
  std::string result;
};

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

 private:
  PathHandler path_handler_helper_ = PathHandler();
};

}  // namespace utils
}  // namespace pointer

#endif  // SRC_BACKEND_SRC_UTILS_UTILS_H_
