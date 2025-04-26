// smd/streams/boolean.t.cpp                                           -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <smd/streams/boolean.hpp>

#include <smd/streams/boolean.hpp> // test 2nd include OK

#include <gtest/gtest.h>

TEST(BooleanTest, Breathing) {
        constexpr auto t = smd::streams::tru();
        constexpr auto f = smd::streams::fls();
        static_assert(t(true, false) == true);
        static_assert(t(1, 2) == 1);
        static_assert(f(true, false) == false);
        static_assert(f(1, 2) == 2);
}

TEST(BooleanTest, Observe) {
        constexpr auto t = smd::streams::tru();
        constexpr auto f = smd::streams::fls();

        constexpr auto a = smd::streams::And(t, t);
        static_assert(smd::streams::toBool(a) == true);

        static_assert(smd::streams::toBool(smd::streams::And(f, f)) == false);
        static_assert(smd::streams::toBool(smd::streams::And(t, f)) == false);
        static_assert(smd::streams::toBool(smd::streams::And(f, t)) == false);
        static_assert(smd::streams::toBool(smd::streams::And(t, t)) == true);

        static_assert(smd::streams::toBool(smd::streams::Or(f, f)) == false);
        static_assert(smd::streams::toBool(smd::streams::Or(t, f)) == true);
        static_assert(smd::streams::toBool(smd::streams::Or(f, t)) == true);
        static_assert(smd::streams::toBool(smd::streams::Or(t, t)) == true);

        static_assert(smd::streams::toBool(smd::streams::Not(f)) == true);
        static_assert(smd::streams::toBool(smd::streams::Not(t)) == false);
}
