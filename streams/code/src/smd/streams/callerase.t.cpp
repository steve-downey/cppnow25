// src/smd/streams/callerase.t.cpp                      -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <smd/streams/callerase.hpp>

#include <smd/streams/callerase.hpp> // test 2nd include OK

#include <gtest/gtest.h>

consteval auto test_empty() {
  smd::streams::callerase f = [] { return 42; };
  return f();
}

consteval auto test_arg() {
  smd::streams::callerase f = [](int i) { return i; };
  return f(42);
}

consteval auto test_capture() {
  int i = 42;
  smd::streams::callerase f = [&] { return i; };
  return f();
}

TEST(CallEraseTest, Breathing) {
  static_assert(42 == test_empty());
  static_assert(42 == test_arg());
  static_assert(42 == test_capture());
}
