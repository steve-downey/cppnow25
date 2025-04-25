#include <smd/streams/stream.hpp>

#include <gtest/gtest.h>
TEST(StreamTest, Breathing) {
        constexpr auto l1 = Nil;
        constexpr auto l2 = Cons(5, Nil);
        constexpr auto l3 = Cons(6, l2);
        static_assert(isNil(l1) == true);
        static_assert(isNil(l2) == false);
        static_assert(head(l2) == 5);
        static_assert(isNil(tail(l2)));
        static_assert(head(l3) == 6);
        static_assert(head(tail(l3)) == 5);
}

TEST(StreamTest, Observe) {
        [[maybe_unused]] constexpr auto l1 = Nil;
        [[maybe_unused]] constexpr auto l2 = Cons(5, Nil);
        [[maybe_unused]] constexpr auto l3 = Cons(6, l2);
        static_assert(length(l1) == 0);
        static_assert(length(l2) == 1);
        static_assert(length(l3) == 2);
}
