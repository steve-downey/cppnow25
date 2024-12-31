#include <smd/streams/stream.hpp>


void either_test() {
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

    constexpr int k1 = fromLeft(11)(l);
    constexpr int k2 = fromLeft(11)(r);
    static_assert(k1 == 7);
    static_assert(k2 == 11);

    constexpr double k3 = fromRight(11)(l);
    constexpr double k4 = fromRight(11)(r);
    static_assert(k3 == 11.0);
    static_assert(k4 == 9.0);

    constexpr auto   match = either([](auto x) -> double { return 2 * x; })([](auto x) -> double { return 3 * x; });
    constexpr double d1    = match(l);
    constexpr double d2    = match(r);
    static_assert(d1 == 14.0);
    static_assert(d2 == 27.0);
}

namespace either2 {
void either_test() {
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
} // namespace either2

namespace either3 {

void either_test() {
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
} // namespace either3


void list_test() {
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

// List functions
/*
 */
// inline constexpr auto take = [](this const auto& self, auto n, auto l) {
//     if (isNil(l))
//         return Nil;
//     else if (n == 0)
//         return Nil;
//     else
//         return Cons(head(l), self(n - 1, tail(l)));
// };

void list_function_test() {
    constexpr auto l1 = Nil;
    constexpr auto l2 = Cons(5, Nil);
    constexpr auto l3 = Cons(6, l2);
    // constexpr auto l  = take(1, l3);
    // static_assert(head(l) == 5);
}

int all_main() {
    either2::either_test();
    either3::either_test();
    list_test();
    return 0;
}
