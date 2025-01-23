// src/smd/streams/pair.t.cpp                                         -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <smd/streams/pair.hpp>

#include <smd/streams/pair.hpp> // test 2nd include OK

#include <gtest/gtest.h>

TEST(PairTest, ConstexprBreating) {
  constexpr auto p1 = smd::streams::pair(7, 0);
  constexpr int k = smd::streams::fst(p1);
  static_assert(k == 7);
  static_assert(0 == smd::streams::snd(p1));
}

TEST(PairTest, Breating) {
  auto p1 = smd::streams::pair(7, 0);
  int k = smd::streams::fst(p1);
  EXPECT_EQ(k, 7);
  EXPECT_EQ(0, smd::streams::snd(p1));
}
