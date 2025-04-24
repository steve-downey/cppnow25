#ifndef INCLUDED_SMD_STREAMS_LIST
#define INCLUDED_SMD_STREAMS_LIST

#include <cstdlib>
#include <functional>
namespace smd {
namespace streams {
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


// cebc5986-c2c2-4525-baf9-8692824506fe
inline constexpr auto Nil = [](auto nil, auto cons) { return nil(); };

inline constexpr auto Cons = [](auto x, auto xs) {
        return [x, xs](auto nil, auto cons) { return cons(x, xs); };
};
// cebc5986-c2c2-4525-baf9-8692824506fe end


// 029a0a98-e47d-4f61-a6d6-1ccb8321c6a9
inline constexpr auto isNil = [](auto l) -> bool {
        return l([]() { return true; }, [](auto x, auto xs) { return false; });
};

inline constexpr auto head = [](auto l) {
        return l([]() { std::abort(); }, [](auto x, auto xs) { return x; });
};

inline constexpr auto tail = [](auto l) {
        return l([]() { std::abort(); }, [](auto x, auto xs) { return xs; });
};
// 029a0a98-e47d-4f61-a6d6-1ccb8321c6a9 end

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
