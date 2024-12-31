#include <smd/streams/stream.hpp>

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
    list_test();
    return 0;
}
