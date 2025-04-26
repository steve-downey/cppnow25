#include <type_traits>
#include <utility>

/* Pair <L, R>
constructor L R -> pair
left: pair -> L
right: pair -> R
match (L -> R -> C) -> C
*/

template <typename F, typename R, typename... Args>
concept invocable_r = std::is_invocable_r_v<R, F, Args...>;

static_assert(invocable_r<void(int), void, int>);

// 735bf5a8-0156-4907-96e8-5878efec8255
template <typename P, typename L, typename R> struct PairTypeclass {
        constexpr auto pair(L, R) const -> P;
        constexpr auto first(P) const -> L;
        constexpr auto second(P) const -> R;
        template <typename C>
        constexpr auto apply(P e, invocable_r<C, L, R> auto) const -> C;
};
// 735bf5a8-0156-4907-96e8-5878efec8255 end

// a1310e75-cee5-4701-8828-9ceef8073ef8
template <typename L, typename R> struct PairTypeclass<std::pair<L, R>, L, R> {
        using P = std::pair<L, R>;
        constexpr auto pair(L l, R r) const -> P { return {l, r}; }
        constexpr auto first(P p) const -> L { return p.first; }
        constexpr auto second(P p) const -> R { return p.second; }

        template <typename C>
        constexpr auto apply(P p, invocable_r<C, L, R> auto f) const -> C {
                return f(p.first, p.second);
        }
};
// a1310e75-cee5-4701-8828-9ceef8073ef8 end

template <class T, class L, class R> auto pair_typeclass = std::false_type{};

template <class L, class R>
constexpr inline auto pair_typeclass<std::pair<L, R>, L, R> =
        PairTypeclass<std::pair<L, R>, L, R>{};

// 3522d0d3-d0e7-46ea-9523-9da2ec0075bd
template <typename Pair,
          typename Left,
          typename Right,
          auto pair_map = pair_typeclass<Pair, Left, Right>>
void test_function() {
        constexpr auto p1 = pair_map.pair(7, 9.0);
        // 3522d0d3-d0e7-46ea-9523-9da2ec0075bd end

        // 8a9dbcf7-cee4-474d-ab35-2d433f9a74fb
        constexpr int k1 = pair_map.first(p1);
        static_assert(k1 == 7);

        constexpr double k3 = pair_map.second(p1);
        static_assert(k3 == 9.0);
        // 8a9dbcf7-cee4-474d-ab35-2d433f9a74fb end

        // ef0d2d45-e59e-4d70-a5a7-933016d63238
        constexpr auto match = [=](auto p) -> double {
                return pair_map.template apply<double>(
                        p, [](auto x, auto y) -> double {
                                return 2 * x + 3 * y;
                        });
        };
        constexpr double d1 = match(p1);
        static_assert(d1 == 41.0);
}
// ef0d2d45-e59e-4d70-a5a7-933016d63238 end

// 9a1fd6e9-3ca8-4321-8b6c-7ad48256b9ed
int main() { test_function<std::pair<int, double>, int, double>(); }
// 9a1fd6e9-3ca8-4321-8b6c-7ad48256b9ed end
