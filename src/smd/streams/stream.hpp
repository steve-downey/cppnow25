#include <cassert>
#include <cstdlib>
#include <functional>
#include <utility>

// LIST
/*
    nil  =         λn c . n
    cons = λx xs . λn c . c x xs

    isnil  = λl . l (λx xs . false) true
    head   = λl . l nil (λx xs . x)
    tail   = λl . l nil (λx xs . xs)
*/

template <typename A, typename AS, typename R> struct ScottCase {
  const std::function<R(A, AS)> &nil;
  const std::function<R(A, AS)> &cons;
};

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
