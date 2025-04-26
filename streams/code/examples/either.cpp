#include <expected>
#include <type_traits>

/* Either<L, R>
left constructor L -> either
right constructor R -> either
isLeft: either -> bool
isRight: either -> bool
fromLeft: either -> R -> R
fromRight: either -> L -> L
either (L -> C) -> (R -> C) -> C
*/

template <typename F, typename R, typename... Args>
concept invocable_r = std::is_invocable_r_v<R, F, Args...>;

static_assert(invocable_r<void(int), void, int>);

// 735bf5a8-0156-4907-96e8-5878efec8255
template <typename E, typename L, typename R> struct EitherTypeclass {
        constexpr auto left(L) const -> E;
        constexpr auto right(R) const -> E;
        constexpr auto isLeft(E) const -> bool;
        constexpr auto isRight(E) const -> bool;
        constexpr auto fromLeft(E, L) const -> L;
        constexpr auto fromRight(E, L) const -> L;
        template <typename C>
        constexpr auto
        either(E e, invocable_r<C, L> auto, invocable_r<C, R> auto) const -> C;
};
// 735bf5a8-0156-4907-96e8-5878efec8255 end

// a1310e75-cee5-4701-8828-9ceef8073ef8
template <typename L, typename R>
struct EitherTypeclass<std::expected<L, R>, L, R> {
        using E = std::expected<L, R>;
        constexpr auto left(L l) const -> E { return l; }
        constexpr auto right(R r) const -> E { return std::unexpected{r}; }
        constexpr auto isLeft(E e) const -> bool { return e.has_value(); }
        constexpr auto isRight(E e) const -> bool { return not e.has_value(); }
        constexpr auto fromLeft(E e, L l) const -> L {
                return isLeft(e) ? e.value() : l;
        }
        constexpr auto fromRight(E e, R r) const -> R {
                return isRight(e) ? e.error() : r;
        }

        template <typename C>
        constexpr auto either(E e,
                              invocable_r<C, L> auto left,
                              invocable_r<C, R> auto right) const -> C {
                return isLeft(e) ? left(e.value()) : right(e.error());
        }
};
// a1310e75-cee5-4701-8828-9ceef8073ef8 end

template <class T, class L, class R> auto either_typeclass = std::false_type{};

template <class L, class R>
constexpr inline auto either_typeclass<std::expected<L, R>, L, R> =
        EitherTypeclass<std::expected<L, R>, L, R>{};

// 3522d0d3-d0e7-46ea-9523-9da2ec0075bd
template <typename Either,
          typename Left,
          typename Right,
          auto either_map = either_typeclass<Either, Left, Right>>
void test_function() {
        constexpr auto l = either_map.left(7);
        constexpr auto r = either_map.right(9.0);
        constexpr bool b1 = either_map.isLeft(l);
        constexpr bool b2 = either_map.isLeft(r);
        constexpr bool b3 = either_map.isRight(l);
        constexpr bool b4 = either_map.isRight(r);
        static_assert(b1 == true);
        static_assert(b2 == false);
        static_assert(b3 == false);
        static_assert(b4 == true);
        // 3522d0d3-d0e7-46ea-9523-9da2ec0075bd end

        // 8a9dbcf7-cee4-474d-ab35-2d433f9a74fb
        constexpr int k1 = either_map.fromLeft(l, 11);
        constexpr int k2 = either_map.fromLeft(r, 11);
        static_assert(k1 == 7);
        static_assert(k2 == 11);

        constexpr double k3 = either_map.fromRight(l, 11);
        constexpr double k4 = either_map.fromRight(r, 11);
        static_assert(k3 == 11.0);
        static_assert(k4 == 9.0);
        // 8a9dbcf7-cee4-474d-ab35-2d433f9a74fb end

        // ef0d2d45-e59e-4d70-a5a7-933016d63238
        constexpr auto match = [=](auto e) {
                return either_map.template either<double>(
                        e,
                        [](auto x) -> double { return 2 * x; },
                        [](auto x) -> double { return 3 * x; });
        };
        constexpr double d1 = match(l);
        constexpr double d2 = match(r);
        static_assert(d1 == 14.0);
        static_assert(d2 == 27.0);
}
// ef0d2d45-e59e-4d70-a5a7-933016d63238 end

// 9a1fd6e9-3ca8-4321-8b6c-7ad48256b9ed
int main() { test_function<std::expected<int, double>, int, double>(); }
// 9a1fd6e9-3ca8-4321-8b6c-7ad48256b9ed end
