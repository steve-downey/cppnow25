// streams/code/src/smd/streams/sender_stream.t.cpp                   -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <smd/streams/sender_stream.hpp>

#include <smd/streams/sender_stream.hpp> // test 2nd include OK

#include <gtest/gtest.h>

TEST(SenderStreamTest, Breathing) {
        using namespace smd::churchsender::senderStream;
        auto s1 = constStream(7);
        auto k1 = hd(s1);
        auto s2 = tl(s1);
        auto k2 = hd(s2);
        //        static_assert(hd(s1) == 7);
        // static_assert(hd(s2) == 7);
}
