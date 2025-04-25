#include <smd/streams/list.hpp>

#include <gtest/gtest.h>
TEST(ListTest, Breathing) {
        constexpr auto l1 = smd::streams::Nil;
        constexpr auto l2 = smd::streams::Cons(5, smd::streams::Nil);
        constexpr auto l3 = smd::streams::Cons(6, l2);
        static_assert(smd::streams::isNil(l1) == true);
        static_assert(smd::streams::isNil(l2) == false);
        static_assert(smd::streams::head(l2) == 5);
        static_assert(smd::streams::isNil(smd::streams::tail(l2)));
        static_assert(smd::streams::head(l3) == 6);
        static_assert(smd::streams::head(smd::streams::tail(l3)) == 5);
}

TEST(ListTest, Observe) {
        constexpr auto l1 = smd::streams::Nil;
        constexpr auto l2 = smd::streams::Cons(5, smd::streams::Nil);
        constexpr auto l3 = smd::streams::Cons(6, l2);
        static_assert(smd::streams::length(l1) == 0);
        static_assert(smd::streams::length(l2) == 1);
        static_assert(smd::streams::length(l3) == 2);
}
