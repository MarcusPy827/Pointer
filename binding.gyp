{
  "includes": ["deps.gypi"], 
  "targets": [
    {
      "target_name": "pointer_core",
      "conditions": [
        ['OS=="win"', {
          "msvs_settings": {
            "VCCLCompilerTool": {
              "AdditionalOptions": [ "/utf-8", "/EHsc" ]
            }
          }
        }]
      ],
      "sources": [
        "./src/backend/src/plugin/plugin.cc",
        "./src/backend/src/file_handler/file_handler.h",
        "./src/backend/src/file_handler/file_handler.cc",
        "./src/backend/src/utils/utils.h",
        "./src/backend/src/utils/utils.cc",
        "./src/backend/src/proto_gen/src/proto/file_handler.pb.h",
        "./src/backend/src/proto_gen/src/proto/file_handler.pb.cc",
        "./src/backend/src/proto_gen/src/proto/utils.pb.h",
        "./src/backend/src/proto_gen/src/proto/utils.pb.cc",
      ],
      "include_dirs": [
        "./node_modules/node-addon-api/",
        "./src/backend/",
        "<(absl_includedir)",
        "src/backend/src/proto_gen",
        "/usr/include",
        "/usr/include/google"
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
            "<(absl_libdir)/libabsl_log_internal_message.a",
            "<(absl_libdir)/libabsl_cord.a",
            "<(absl_libdir)/libabsl_symbolize.a",
            "<(absl_libdir)/libabsl_demangle_internal.a",
            "<(absl_libdir)/libabsl_debugging_internal.a",
            "<(absl_libdir)/libabsl_malloc_internal.a",
            "<(absl_libdir)/libabsl_examine_stack.a",
            "<(absl_libdir)/libabsl_failure_signal_handler.a",
            "<(absl_libdir)/libabsl_log_internal_message.a",
            "<(absl_libdir)/libabsl_log_internal_check_op.a",
            "<(absl_libdir)/libabsl_log_internal_format.a",
            "<(absl_libdir)/libabsl_log_internal_globals.a",
            "-Wl,--end-group",
            "-pthread",
            "-luuid",
            "-lprotobuf",
            "/usr/lib/x86_64-linux-gnu/libprotobuf.a"
          ],
          "ldflags": ["-Wl,--no-as-needed"]
        }], 

        ["OS == 'win'", {
          "defines": [
            "_HAS_EXCEPTIONS=1"
          ],

          "msvs_settings": {
            "VCCLCompilerTool": {
              "ExceptionHandling": 1
            }
          },

          "libraries": [
            "<(absl_libdir)/absl_str_format_internal.lib",
            "<(absl_libdir)/absl_strings.lib",
            "<(absl_libdir)/absl_base.lib",
            "<(absl_libdir)/absl_raw_logging_internal.lib",
            "<(absl_libdir)/absl_spinlock_wait.lib",
            "<(absl_libdir)/absl_log_severity.lib",
            "<(absl_libdir)/absl_log_internal_message.lib",
            "<(absl_libdir)/absl_cord.lib",
            "<(absl_libdir)/absl_symbolize.lib",
            "<(absl_libdir)/absl_demangle_internal.lib",
            "<(absl_libdir)/absl_debugging_internal.lib",
            "<(absl_libdir)/absl_malloc_internal.lib",
            "<(absl_libdir)/absl_examine_stack.lib",
            "<(absl_libdir)/absl_failure_signal_handler.lib",
            "<(absl_libdir)/absl_log_internal_check_op.lib",
            "<(absl_libdir)/absl_log_internal_format.lib",
            "<(absl_libdir)/absl_log_internal_globals.lib",
            "<(absl_libdir)\\absl_int128.lib",
            "<(absl_libdir)\\absl_strings_internal.lib",
            "Rpcrt4.lib"
          ]
        }]
      ]
    }
  ]
}
