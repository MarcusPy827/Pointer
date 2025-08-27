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

#ifndef SRC_BACKEND_SRC_FILE_HANDLER_FILE_HANDLER_H_
#define SRC_BACKEND_SRC_FILE_HANDLER_FILE_HANDLER_H_

#include <string>

#include "src/utils/utils.h"

namespace pointer {
namespace core {

struct FileHandlerResult {
  bool result = false;
  std::string msg;
};

class FileHandler {
 public:
  FileHandlerResult CheckIsDirectoryExists(std::string path, bool create_mode);

  FileHandlerResult CheckIsDirectoryEmpty(std::string path,
    bool ignore_hidden_files, bool create_mode);

  FileHandlerResult CreateWorkSpace(std::string path, std::string name);

 private:
  FileHandlerResult FolderExists(std::string path);

  FileHandlerResult FileExists(std::string path);

  pointer::utils::Utils utils_helper_ = pointer::utils::Utils();
};

}  // namespace core
}  // namespace pointer

#endif  // SRC_BACKEND_SRC_FILE_HANDLER_FILE_HANDLER_H_
