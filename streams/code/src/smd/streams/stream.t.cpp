#include <smd/streams/stream.hpp>

#include <gtest/gtest.h>

TEST(StreamTest, constStreamTest) {
        constexpr auto s1 = constStream(7);
        static_assert(hd(s1) == 7);
        constexpr auto s2 = tl(s1);
        static_assert(hd(s2) == 7);
}

TEST(StreamTest, countStreamTest) {
        constexpr auto s1 = countStream(7);
        static_assert(hd(s1) == 7);
        constexpr auto s2 = tl(s1);
        static_assert(hd(s2) == 8);
}
