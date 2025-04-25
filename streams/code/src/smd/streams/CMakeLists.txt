# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

# target_sources(smd.streams PRIVATE stream.cpp)

target_sources(
    smd.streams
    PUBLIC
        FILE_SET smd_streams_headers
        TYPE HEADERS
        FILES stream.hpp pair.hpp maybe.hpp either.hpp list.hpp callerase.hpp
)

set_target_properties(smd.streams PROPERTIES VERIFY_INTERFACE_HEADER_SETS ON)

install(
    TARGETS smd.streams
    EXPORT smd.streams
    DESTINATION
    {CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION {CMAKE_INSTALL_BINDIR}
    FILE_SET smd_streams_headers DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

include(GoogleTest)

add_executable(smd.streams.tests)
target_sources(
    smd.streams.tests
    PRIVATE stream.t.cpp pair.t.cpp maybe.t.cpp either.t.cpp list.t.cpp callerase.t.cpp
)

target_link_libraries(
    smd.streams.tests
    PRIVATE smd::streams GTest::gtest GTest::gtest_main
)

gtest_add_tests(smd.streams.tests "" AUTO)
