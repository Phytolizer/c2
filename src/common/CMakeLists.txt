add_library(
  common
  data.c
  directory.c
  key.c
  libstring.c
  net_client.c
  net_server.c
  term.c
)

target_include_directories(
  common
  PRIVATE "${PROJECT_SOURCE_DIR}/include"
)
