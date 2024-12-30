# Create the library target and named header set for smd.streams
add_library(smd.streams STATIC)
target_sources(
  smd.streams
  PUBLIC FILE_SET smd_streams_headers TYPE HEADERS BASE_DIRS .
)

add_library(smd::streams ALIAS smd.streams)

add_subdirectory(smd)
