// examples/playground.cpp                                            -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <beman/execution/execution.hpp>
#include <iostream>
#include <string>
#include <tuple>

namespace ex = ::beman::execution;

// ----------------------------------------------------------------------------

int main() {
    auto [result] = ex::sync_wait(ex::when_all(ex::just(std::string("hello, ")), ex::just(std::string("world"))) |
                                  ex::then([](const auto& s1, const auto& s2) { return s1 + s2; }))
                        .value_or(std::tuple(std::string("oops")));
    std::cout << "result='" << result << "'\n";
}
