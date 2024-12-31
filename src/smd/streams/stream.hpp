#include <cassert>
#include <cstdlib>
#include <utility>
#include <functional>

// MAYBE
/*
nothing = λ. λn.λj.n
   just = λx.λn.λj.j x
*/

inline constexpr auto nothing = []() { return [](auto n) { return [n](auto _) { return n(); }; }; };

inline constexpr auto just = [](auto x) { return [x](auto _) { return [x](auto j) { return j(x); }; }; };

// inline constexpr auto nothing = []() {
//     return [](auto n, auto _) { return n(); };
// };

// inline constexpr auto just = [](auto x) {
//     return [x](auto _, auto j) { return j(x); };
// };

inline constexpr auto isNothing = [](auto m) { return m([]() { return true; })([](auto _) { return false; }); };
inline constexpr auto isJust    = [](auto m) { return m([]() { return false; })([](auto _) { return true; }); };
inline constexpr auto fromJust  = [](auto m) { return m([]() { std::abort(); })([](auto x) { return x; }); };
inline constexpr auto maybe     = [](auto d) {
    return [d](auto f) { return [d, f](auto m) { return m([d]() { return d; })(f); }; };
};

// EITHER
/*
    left   = λa.λl.λr.l a
    right  = λb.λl.λr.r b

    either = λl.λr.λe.e l r
*/

inline constexpr auto left  = [](auto a) { return [a](auto l) { return [l, a](auto _) { return l(a); }; }; };
inline constexpr auto right = [](auto b) { return [b](auto _) { return [b](auto r) { return r(b); }; }; };

inline constexpr auto isLeft = [](auto e) { return e([](auto _) { return true; })([](auto _) { return false; }); };
;
inline constexpr auto isRight = [](auto e) { return e([](auto _) { return false; })([](auto _) { return true; }); };
;

inline constexpr auto fromLeft = [](auto d) {
    return [d](auto e) { return e([](auto x) { return x; })([d](auto _) { return d; }); };
};
inline constexpr auto fromRight = [](auto d) {
    return [d](auto e) { return e([d](auto _) { return d; })([](auto x) { return x; }); };
};

inline constexpr auto either = [](auto l) { return [l](auto r) { return [l, r](auto e) { return e(l)(r); }; }; };

// EITHER2
/*
    left   = λa.λl r.l a
    right  = λb.λl r.r b

    either = λl r.λe.e l r
*/
namespace either2 {
inline constexpr auto left  = [](auto a) { return [a](auto l, auto _) { return l(a); }; };
inline constexpr auto right = [](auto b) { return [b](auto _, auto r) { return r(b); }; };

inline constexpr auto isLeft = [](auto e) { return e([](auto _) { return true; }, [](auto _) { return false; }); };
;
inline constexpr auto isRight = [](auto e) { return e([](auto _) { return false; }, [](auto _) { return true; }); };
;

inline constexpr auto fromLeft = [](auto d, auto e) { return e([](auto x) { return x; }, [d](auto _) { return d; }); };
inline constexpr auto fromRight = [](auto d, auto e) {
    return e([d](auto _) { return d; }, [](auto x) { return x; });
};

inline constexpr auto either = [](auto l, auto r) { return [l, r](auto e) { return e(l, r); }; };
} // namespace either2
// EITHER 3 -- Case Record
namespace either3 {
template <typename A, typename B, typename R>
struct EitherCase {
    std::function<R(A)> left;
    std::function<R(B)> right;
    constexpr EitherCase(std::function<R(A)> left, std::function<R(B)> right) : left(left), right(right) {}
};

template <typename A, typename B>
struct Either {
    inline static constexpr auto left = [](A a) {
        return [a]<typename R>(EitherCase<A, B, R> c) { return c.left(a); };
    };

    inline static constexpr auto right = [](B b) {
        return [b]<typename R>(EitherCase<A, B, R> c) { return c.right(b); };
    };

    template <typename R>
    auto operator()(EitherCase<A, B, R> c) -> R;
};

template <typename A, typename B>
inline constexpr auto isLeft =
    [](auto e) { return e(EitherCase<A, B, bool>{[](auto _) { return true; }, [](auto _) { return false; }}); };

template <typename A, typename B>
inline constexpr auto isRight =
    [](auto e) { return e(EitherCase<A, B, bool>{[](auto _) { return false; }, [](auto _) { return true; }}); };

template <typename A, typename B>
inline constexpr auto fromLeft = [](auto d, auto e) {
    return e(EitherCase<A, B, decltype(d)>{[](auto x) { return x; }, [d](auto _) { return d; }});
};

template <typename A, typename B>
inline constexpr auto fromRight = [](auto d, auto e) {
    return e(EitherCase<A, B, decltype(d)>{[d](auto _) { return d; }, [](auto x) { return x; }});
};

template <typename A, typename B, typename R>
inline constexpr auto either =
    [](std::function<R(A)> l, std::function<R(B)> r) { return [l, r](auto e) { return e(EitherCase{l, r}); }; };

} // namespace either3


// LIST
/*
    nil  =         λn c . n
    cons = λx xs . λn c . c x xs

    isnil  = λl . l (λx xs . false) true
    head   = λl . l nil (λx xs . x)
    tail   = λl . l nil (λx xs . xs)
*/

template <typename A, typename AS, typename R>
struct ScottCase {
    const std::function<R(A, AS)>& nil;
    const std::function<R(A, AS)>& cons;
};

inline constexpr auto Nil = [](auto nil, auto cons) { return nil(); };

inline constexpr auto Cons = [](auto x, auto xs) { return [x, xs](auto nil, auto cons) { return cons(x, xs); }; };

inline constexpr auto isNil = [](auto l) -> bool {
    return l([]() { return true; }, [](auto x, auto xs) { return false; });
};

inline constexpr auto head = [](auto l) { return l([]() { std::abort(); }, [](auto x, auto xs) { return x; }); };

inline constexpr auto tail = [](auto l) { return l([]() { std::abort(); }, [](auto x, auto xs) { return xs; }); };

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
