// streams/code/src/smd/streams/sender_pair.t.cpp                      -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <smd/streams/sender_pair.hpp>

#include <smd/streams/sender_pair.hpp> // test 2nd include OK

#include <gtest/gtest.h>

TEST(SenderPairTest, Breathing) {
        using namespace smd::churchsender::senderPair;

        auto p1 = pair(7, 0);
        auto [k] = *ex::sync_wait(fst(p1));
        auto [j] = *ex::sync_wait(snd(p1));
        EXPECT_EQ(k, 7);
        EXPECT_EQ(0, j);
}
