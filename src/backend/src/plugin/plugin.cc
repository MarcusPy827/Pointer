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

#include <napi.h>  // NOLINT

#include "../file_handler/file_handler.h"
#include "../utils/utils.h"

pointer::core::FileHandler file_handler_;
pointer::utils::Utils utils_;

inline Napi::Object FileHandlerResult2Object(Napi::Env env,
    pointer::core::FileHandlerResult result) {
  Napi::Object object_gen = Napi::Object::New(env);
  object_gen.Set("result", Napi::Boolean::New(env, result.result));
  object_gen.Set("msg", Napi::String::New(env, result.msg));
  return object_gen;
}

inline Napi::Object ThrowError(Napi::Env env, const std::string_view err_msg) {
  Napi::Object object_gen = Napi::Object::New(env);
  object_gen.Set("result", Napi::Boolean::New(env, false));
  object_gen.Set("msg", Napi::String::New(env, err_msg.data()));
  return object_gen;
}

Napi::Value CheckDirectoryExistsWrapper(const Napi::CallbackInfo&
    callback_info) {
  Napi::Env env = callback_info.Env();
  Napi::Object result;
  std::string_view err_msg;

  if (callback_info.Length() != 2) {
    err_msg = "Argument amount MISMATCH!! Except 2 arguments, aborting...";
    result = ThrowError(env, err_msg);
    return result;
  } else if (!callback_info[0].IsString()) {
    err_msg =
      "Argument type MISMATCH!! The first argument MUST be string, aborting...";
    result = ThrowError(env, err_msg);
    return result;
  } else if (!callback_info[1].IsBoolean()) {
    err_msg =
      "Argument type MISMATCH!! "
      "The second argument MUST be boolean, aborting...";
    result = ThrowError(env, err_msg);
    return result;
  }

  // Get argument
  std::string dir_path = callback_info[0].As<Napi::String>().Utf8Value();
  bool create_mode = callback_info[1].As<Napi::Boolean>().Value();

  // Execute function
  pointer::core::FileHandlerResult original_result = file_handler_
    .CheckIsDirectoryExists(dir_path, create_mode);
  result = FileHandlerResult2Object(env, original_result);
  return result;
}

Napi::Value CheckIsDirectoryEmptyWrapper(const Napi::CallbackInfo&
    callback_info) {
  Napi::Env env = callback_info.Env();
  Napi::Object result;
  std::string_view err_msg;

  if (callback_info.Length() != 3) {
    err_msg = "Argument amount MISMATCH!! Except 3 arguments, aborting...";
    result = ThrowError(env, err_msg);
    return result;
  } else if (!callback_info[0].IsString()) {
    err_msg =
      "Argument type MISMATCH!! The first argument MUST be string, aborting...";
    result = ThrowError(env, err_msg);
    return result;
  } else if (!callback_info[1].IsBoolean()) {
    err_msg =
      "Argument type MISMATCH!! "
      "The second argument MUST be boolean, aborting...";
    result = ThrowError(env, err_msg);
    return result;
  } else if (!callback_info[2].IsBoolean()) {
    err_msg =
      "Argument type MISMATCH!! "
      "The third argument MUST be boolean, aborting...";
    result = ThrowError(env, err_msg);
    return result;
  }

  // Get argument
  std::string dir_path = callback_info[0].As<Napi::String>().Utf8Value();
  bool ignore_hidden_files = callback_info[1].As<Napi::Boolean>().Value();
  bool create_mode = callback_info[2].As<Napi::Boolean>().Value();

  // Execute function
  pointer::core::FileHandlerResult original_result = file_handler_
    .CheckIsDirectoryEmpty(dir_path, ignore_hidden_files, create_mode);
  result = FileHandlerResult2Object(env, original_result);
  return result;
}

Napi::Value CreateWorkspaceWrapper(const Napi::CallbackInfo& callback_info) {
  Napi::Env env = callback_info.Env();
  Napi::Object result;
  std::string_view err_msg;

  if (callback_info.Length() != 2) {
    err_msg = "Argument amount MISMATCH!! Except 2 arguments, aborting...";
    result = ThrowError(env, err_msg);
    return result;
  } else if (!callback_info[0].IsString()) {
    err_msg =
      "Argument type MISMATCH!! The first argument MUST be string, aborting...";
    result = ThrowError(env, err_msg);
    return result;
  } else if (!callback_info[1].IsString()) {
    err_msg =
      "Argument type MISMATCH!! "
      "The second argument MUST be string, aborting...";
    result = ThrowError(env, err_msg);
    return result;
  }

  // Get argument
  std::string path = callback_info[0].As<Napi::String>().Utf8Value();
  std::string name = callback_info[1].As<Napi::String>().Utf8Value();

  // Execute function
  pointer::core::FileHandlerResult original_result = file_handler_
    .CreateWorkSpace(path, name);
  result = FileHandlerResult2Object(env, original_result);
  return result;
}

static Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set("checkDirectoryExists", Napi::Function::New(env,
    CheckDirectoryExistsWrapper, "checkDirectoryExists"));
  exports.Set("checkIsDirectoryEmpty", Napi::Function::New(env,
    CheckIsDirectoryEmptyWrapper, "checkIsDirectoryEmpty"));
  exports.Set("createWorkspace", Napi::Function::New(env,
    CreateWorkspaceWrapper, "createWorkspace"));
  return exports;
}

NODE_API_MODULE(pointer_core, Init);
