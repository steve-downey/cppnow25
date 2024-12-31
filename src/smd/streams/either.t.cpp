// src/smd/streams/either.t.cpp                      -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <smd/streams/either.hpp>

#include <smd/streams/either.hpp> // test 2nd include OK

#include <gtest/gtest.h>

TEST(EitherTest, Breathing) {
    constexpr auto l  = smd::streams::left(7);
    constexpr auto r  = smd::streams::right(9.0);
    constexpr bool b1 = smd::streams::isLeft(l);
    constexpr bool b2 = smd::streams::isLeft(r);
    constexpr bool b3 = smd::streams::isRight(l);
    constexpr bool b4 = smd::streams::isRight(r);
    static_assert(b1 == true);
    static_assert(b2 == false);
    static_assert(b3 == false);
    static_assert(b4 == true);

    constexpr int k1 = smd::streams::fromLeft(11)(l);
    constexpr int k2 = smd::streams::fromLeft(11)(r);
    static_assert(k1 == 7);
    static_assert(k2 == 11);

    constexpr double k3 = smd::streams::fromRight(11)(l);
    constexpr double k4 = smd::streams::fromRight(11)(r);
    static_assert(k3 == 11.0);
    static_assert(k4 == 9.0);

    constexpr auto match =
        smd::streams::either([](auto x) -> double { return 2 * x; })([](auto x) -> double { return 3 * x; });
    constexpr double d1 = match(l);
    constexpr double d2 = match(r);
    static_assert(d1 == 14.0);
    static_assert(d2 == 27.0);
}

TEST(Either2Test, Breathing) {
    using namespace smd::streams::either2;
    constexpr auto l  = left(7);
    constexpr auto r  = right(9.0);
    constexpr bool b1 = isLeft(l);
    constexpr bool b2 = isLeft(r);
    constexpr bool b3 = isRight(l);
    constexpr bool b4 = isRight(r);
    static_assert(b1 == true);
    static_assert(b2 == false);
    static_assert(b3 == false);
    static_assert(b4 == true);

    constexpr int k1 = fromLeft(11, l);
    constexpr int k2 = fromLeft(11, r);
    static_assert(k1 == 7);
    static_assert(k2 == 11);

    constexpr double k3 = fromRight(11, l);
    constexpr double k4 = fromRight(11, r);
    static_assert(k3 == 11.0);
    static_assert(k4 == 9.0);

    constexpr auto   match = either([](auto x) -> double { return 2 * x; }, [](auto x) -> double { return 3 * x; });
    constexpr double d1    = match(l);
    constexpr double d2    = match(r);
    static_assert(d1 == 14.0);
    static_assert(d2 == 27.0);
}

TEST(Either3Test, Breathing) {
    using namespace smd::streams::either3;
    constexpr auto l  = Either<int, double>::left(7);
    constexpr auto r  = Either<int, double>::right(9.0);
    bool           b1 = isLeft<int, double>(l);
    bool           b2 = isLeft<int, double>(r);
    bool           b3 = isRight<int, double>(l);
    bool           b4 = isRight<int, double>(r);
    assert(b1 == true);
    assert(b2 == false);
    assert(b3 == false);
    assert(b4 == true);

    int k1 = fromLeft<int, double>(11, l);
    int k2 = fromLeft<int, double>(11, r);
    assert(k1 == 7);
    assert(k2 == 11);

    double k3 = fromRight<int, double>(11, l);
    double k4 = fromRight<int, double>(11, r);
    assert(k3 == 11.0);
    assert(k4 == 9.0);

    auto match =
        either<int, double, double>([](auto x) -> double { return 2 * x; }, [](auto x) -> double { return 3 * x; });
    double d1 = match(l);
    double d2 = match(r);
    assert(d1 == 14.0);
    assert(d2 == 27.0);
}
