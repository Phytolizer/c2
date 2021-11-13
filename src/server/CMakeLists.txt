add_executable(
  server
  server.c
)

target_link_libraries(
  server
  PRIVATE common pthread
)
target_include_directories(
  server
  PRIVATE "${PROJECT_SOURCE_DIR}/include"
)
