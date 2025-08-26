{
  "targets": [
    {
      "target_name": "pointer_core",
      "sources": [
        "./src/backend/src/plugin/plugin.cc",
        "./src/backend/src/file_handler/file_handler.h",
        "./src/backend/src/file_handler/file_handler.cc"
      ],
      "include_dirs": [
        "./node_modules/node-addon-api/",
        "./src/backend/"
      ],
      "cflags": ["-fno-exceptions"]
    }
  ]
}
