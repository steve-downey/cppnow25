// src/smd/streams/maybe.t.cpp                      -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <smd/streams/maybe.hpp>

#include <smd/streams/maybe.hpp> // test 2nd include OK

#include <gtest/gtest.h>

TEST(MaybeTest, Breathing) {

    constexpr auto m1 = smd::streams::nothing();
    constexpr auto m2 = smd::streams::just(5);

    constexpr bool b1 = smd::streams::isNothing(m1);
    constexpr bool b2 = smd::streams::isJust(m2);
    constexpr bool b3 = smd::streams::isNothing(m2);
    constexpr bool b4 = smd::streams::isJust(m1);
    static_assert(b1 == true);
    static_assert(b2 == true);
    static_assert(b3 == false);
    static_assert(b4 == false);

    constexpr int k = smd::streams::fromJust(m2);
    static_assert(k == 5);

    //    constexpr int k2 = fromJust(m1);

    constexpr int j = smd::streams::maybe(7)([](int i) { return 2 * i; })(m2);
    constexpr int l = smd::streams::maybe(7)([](int i) { return 2 * i; })(m1);
    static_assert(j == 10);
    static_assert(l == 7);

    return;
}
