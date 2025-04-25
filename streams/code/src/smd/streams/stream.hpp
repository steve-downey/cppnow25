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
