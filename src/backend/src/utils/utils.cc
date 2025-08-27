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

#include "src/utils/utils.h"

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

}  // namespace utils
}  // namespace pointer
