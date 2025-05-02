// smd/streams/sender_either.t.cpp -*-C++-*- SPDX-License-Identifier:
// Apache-2.0 WITH LLVM-exception

#include <smd/streams/sender_either.hpp>

#include <smd/streams/sender_either.hpp> // test 2nd include OK

#include <gtest/gtest.h>

TEST(SenderEitherTest, Breathing) {
        using namespace smd::churchsender::senderEither;
        auto l = left(7);
        auto r = right(9.0);
        auto [b1] = *ex::sync_wait(isLeft(l));
        auto [b2] = *ex::sync_wait(isLeft(r));
        auto [b3] = *ex::sync_wait(isRight(l));
        auto [b4] = *ex::sync_wait(isRight(r));
        EXPECT_TRUE(b1 == true);
        EXPECT_TRUE(b2 == false);
        EXPECT_TRUE(b3 == false);
        EXPECT_TRUE(b4 == true);

        // auto [k1] = *ex::sync_wait(fromLeft(11, l));
        // auto [k2] = *ex::sync_wait(fromLeft(11, r));
        // EXPECT_TRUE(k1 == 7);
        // EXPECT_TRUE(k2 == 11);

        // auto [k3] = *ex::sync_wait(fromRight(11, l));
        // auto [k4] = *ex::sync_wait(fromRight(11, r));
        // EXPECT_TRUE(k3 == 11.0);
        // EXPECT_TRUE(k4 == 9.0);

        // auto match =
        //         either([](auto x) -> double { return 2 * x; },
        //                [](auto x) -> double { return 3 * x; });

        // auto m1 = ex::just(l) | match;
        // auto m2 = ex::just(r) | match;
        // auto [d1] = *ex::sync_wait(m1);
        // auto [d2] = *ex::sync_wait(m2);
        // EXPECT_TRUE(d1 == 14.0);
        // EXPECT_TRUE(d2 == 27.0);
}
