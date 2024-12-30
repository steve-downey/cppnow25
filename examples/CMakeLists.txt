# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

set(ALL_EXAMPLES maybe pair either list)

message("Examples to be built: ${ALL_EXAMPLES}")

foreach(example ${ALL_EXAMPLES})
    add_executable(smd.stream.examples.${example})
    target_sources(smd.stream.examples.${example} PRIVATE ${example}.cpp)
    target_link_libraries(smd.stream.examples.${example} smd::streams)
endforeach()
