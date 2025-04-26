#include <cassert>
#include <cstdlib>
#include <functional>
#include <utility>

// LIST
/*
    nil  =         λn c . n
    cons = λx xs . λn c . c x xs

    isnil  = λl . l true (λx xs . false)
    head   = λl . l error (λx xs . x)
    tail   = λl . l nil (λx xs . xs)

    length = λl . l 0 (λ x xs . (+) 1 (length xs))
*/

inline constexpr auto Nil = [](auto nil, auto cons) { return nil(); };

inline constexpr auto Cons = [](auto x, auto xs) {
        return [x, xs](auto nil, auto cons) { return cons(x, xs); };
};

inline constexpr auto isNil = [](auto l) -> bool {
        return l([]() { return true; }, [](auto x, auto xs) { return false; });
};

inline constexpr auto head = [](auto l) {
        return l([]() { std::abort(); }, [](auto x, auto xs) { return x; });
};

inline constexpr auto tail = [](auto l) {
        return l([]() { std::abort(); }, [](auto x, auto xs) { return xs; });
};

inline constexpr auto length = [](this const auto &self, auto l) {
        return l([]() { return 0; },
                 [self](auto x, auto xs) { return 1 + self(xs); });
};

// STREAM co-inductively
/*
  StrA := ∃α . α × (α → A × α)

  data Stream a = S a (Stream a)

  hd (S a as) = a
  tl (S a as) = as

  S = λ a as . λ s . s a as
  hd = \ s . s \ a as . a
  tl = \ s . s \ a as . as
*/

inline constexpr auto hd = [](auto s) {
        return s([](auto a, auto as) { return a; });
};

inline constexpr auto tl = [](auto s) {
        return s([](auto a, auto as) { return as; });
};

inline constexpr auto S = [](auto a, auto as) {
        return [a, as](auto s) { return s(a, as); };
};

inline constexpr auto constStream = [](auto k) {
        return [k](this const auto &self, auto s) { return s(k, self); };
};

struct CountStream {
        const int start;
        constexpr CountStream(int start) : start(start) {}
        constexpr auto operator()(auto s) const {
                return s(start, CountStream{start + 1});
        }
};

inline constexpr auto countStream = [](int start) {
        return CountStream(start);
};
