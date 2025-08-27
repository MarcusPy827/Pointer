{
  "variables": {
    "absl_includedir": "/usr/local/include",
    "absl_libdir": "/usr/local/lib"
  },
  "targets": [
    {
      "target_name": "pointer_core",
      "sources": [
        "./src/backend/src/plugin/plugin.cc",
        "./src/backend/src/file_handler/file_handler.h",
        "./src/backend/src/file_handler/file_handler.cc",
        "./src/backend/src/path_handler/path_handler.h",
        "./src/backend/src/path_handler/path_handler.cc",
        "./src/backend/src/utils/utils.h",
        "./src/backend/src/utils/utils.cc"
      ],
      "include_dirs": [
        "./node_modules/node-addon-api/",
        "./src/backend/",
        "<(absl_includedir)"
      ],
      "defines": [
        "NODE_ADDON_API_CPP_EXCEPTIONS",
        "UUID_USING_CXX20_SPAN"
      ],
      "cflags": ["-fexceptions"],
      "cflags_cc!": [ "-fno-exceptions" ],
      "cflags_cc": ["-fPIC", "-fexceptions", "-std=gnu++20"],
      "conditions": [
        ["OS == 'linux'", {
          "libraries": [
            "-Wl,--no-as-needed",
            "-Wl,--start-group",
            "<(absl_libdir)/libabsl_str_format_internal.a",
            "<(absl_libdir)/libabsl_strings.a",
            "<(absl_libdir)/libabsl_base.a",
            "<(absl_libdir)/libabsl_raw_logging_internal.a",
            "<(absl_libdir)/libabsl_spinlock_wait.a",
            "<(absl_libdir)/libabsl_log_severity.a",
            "<(absl_libdir)/libabsl_throw_delegate.a",
            "-Wl,--end-group",
            "-pthread",
            "-luuid"
          ],
          "ldflags": ["-Wl,--no-as-needed"]
        }]
      ]
    }
  ]
}
