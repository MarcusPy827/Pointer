log() {
  # $1: level
  # $2: content

  case $1 in
    "info")
      echo -e "\x1b[39;1m[\x1b[34;1mINFO\x1b[39;1m]\x1b[0m $2\x1b[0m"
      ;;
    "warn")
      echo -e "\x1b[39;1m[\x1b[33;1mWARN\x1b[39;1m]\x1b[0m $2\x1b[0m"
      ;;
    "ok")
      echo -e "\x1b[39;1m[\x1b[32;1m OK \x1b[39;1m]\x1b[0m $2\x1b[0m"
      ;;
    "error")
      echo -e "\x1b[39;1m[\x1b[31;1mERROR\x1b[39;1m]\x1b[0m $2\x1b[0m"
      ;;
    *)
      echo -e "\x1b[39;1m[\x1b[36;1mDEBUG\x1b[39;1m]\x1b[0m $2\x1b[0m"
      ;;
  esac
}

log_tag() {
  # $1: level
  # $2: tag
  # $3: content
  log $1 "\x1b[1;4m$2\x1b[0m: $3\x1b[0m"
}

bold() {
  # $1: content
  echo -e "\x1b[1m$1\x1b[0m"
}

bold "Protobuf Generate Script Version 0.9"
log_tag "warn" "Dependency requirement" "Please make sure that you have already have protobuf ready in your path."
log_tag "warn" "Path requirement" "Please run this script on project root using \"scripts/proto_gen.sh\", please do NOT run it within the \"scripts\" folder, otherwise protoc might NOT find all the proto files!!"

log_tag "info" "Path handler" "Now checking if the directory \"src/backend/src/proto_gen\" exists..."
if [ -d "./src/backend/src/proto_gen" ]; then
  log_tag "ok" "Path handler" "The directory \"src/backend/proto_gen\" exists."
else
  if mkdir "./src/backend/src/proto_gen"; then
    log_tag "ok" "Path handler" "Successfully created path \"src/backend/src/proto_gen\"."
  else
    log_tag "error" "Path handler" "Could not create path \"src/backend/src/proto_gen\", aborting..."
    exit -1
  fi
fi

log_tag "info" "Path handler" "Now checking if the directory \"src/proto_gen/ts\" exists..."
if [ -d "./src/proto_gen/ts" ]; then
  log_tag "ok" "Path handler" "The directory \"src/proto_gen/ts\" exists."
else
  if mkdir "./src/proto_gen/ts"; then
    log_tag "ok" "Path handler" "Successfully created path \"src/proto_gen/ts\"."
  else
    log_tag "error" "Path handler" "Could not create path \"src/proto_gen/ts\", aborting..."
    exit -1
  fi
fi


log_tag "info" "Generator" "Now trying to generate protobuf files for file handler..."
if protoc --cpp_out=src/backend/src/proto_gen ./src/proto/file_handler.proto; then
  log_tag "ok" "Generator" "Successfully generated include headers for \"file handler.proto\""
else
  log_tag "error" "Generator" "Failed to generate source for \"file_handler.proto\", aborting..."
  exit -1
fi

if npx protoc --ts_out="src/proto_gen/ts/" ./src/proto/file_handler.proto; then
  log_tag "ok" "Generator" "Successfully generated include file for \"file handler.proto\""
else
  log_tag "error" "Generator" "Failed to generate source for \"file_handler.proto\", aborting..."
  exit -1
fi

log "ok" "Congrats, we successfully generated all the proto file!!"
