#include <beman/execution/execution.hpp>
#include <smd/streams/callerase.hpp>

#include <iostream>
#include <cassert>

namespace ex = beman::execution;

struct example_sender {
        template <ex::receiver Receiver> struct state {
                using operation_state_concept = ex::operation_state_t;
                std::remove_cvref_t<Receiver> receiver;
                int value;
                auto start() & noexcept {
                        ex::set_value(std::move(this->receiver), this->value);
                }
        };

        using sender_concept = ex::sender_t;
        using completion_signatures =
                ex::completion_signatures<ex::set_value_t(int)>;

        int value{};
        template <ex::receiver Receiver>
        auto connect(Receiver &&receiver) const -> state<Receiver> {
                return {std::forward<Receiver>(receiver), this->value};
        }
};

static_assert(ex::sender<example_sender>);

template <typename Value> struct sender2 {
        template <ex::receiver Receiver> struct state {
                using operation_state_concept = ex::operation_state_t;
                std::remove_cvref_t<Receiver> receiver;
                Value value;
                auto start() & noexcept {
                        ex::set_value(std::move(this->receiver), this->value);
                }
        };

        using sender_concept = ex::sender_t;
        using completion_signatures =
                ex::completion_signatures<ex::set_value_t(Value)>;

        template <ex::receiver Receiver>
        auto connect(Receiver &&receiver) const -> state<Receiver> {
                return {std::forward<Receiver>(receiver), this->value};
        }

        Value value{};
};

static_assert(ex::sender<sender2<int>>);
static_assert(ex::sender<sender2<std::string>>);

/*
nothing = λ. λn.λj.n
   just = λx.λn.λj.j x
*/

inline constexpr auto nothing = []() {
        return [](auto n) { return [n](auto _) { return n(); }; };
};

inline constexpr auto just = [](auto x) {
        return [x](auto _) { return [x](auto j) { return j(x); }; };
};

/*
    pair = λl r p. p l r
    fst = λp. p (λl r. l)
    snd = λp. p (λl r. r)
*/

inline constexpr auto churchPair = [](auto l, auto r) {
        return [l, r](auto p) { return p(l, r); };
};

inline constexpr auto churcFst = [](auto p) {
        return p([](auto l, auto r) { return l; });
};

inline constexpr auto churchSnd = [](auto p) {
        return p([](auto l, auto r) { return r; });
};

inline constexpr auto pair = [](auto l, auto r) {
  return ex::just(l, r);
};

inline constexpr auto fst = [](ex::sender auto p) -> ex::sender auto{
        return ex::then(p, [](auto l, auto r) { return l; });
};

inline constexpr auto snd = [](ex::sender auto p) -> ex::sender auto{
        return ex::then(p, [](auto l, auto r) { return r; });
};

namespace churchEither {
// EITHER
/*
    left   = λa.λl.λr.l a
    right  = λb.λl.λr.r b

    either = λl.λr.λe.e l r
*/

inline constexpr auto left = [](auto a) {
  return [a](auto l) { return [l, a](auto _) { return l(a); }; };
};

inline constexpr auto right = [](auto b) {
  return [b](auto _) { return [b](auto r) { return r(b); }; };
};

inline constexpr auto isLeft = [](auto e) {
  return e([](auto _) { return true; })([](auto _) { return false; });
};

inline constexpr auto isRight = [](auto e) {
  return e([](auto _) { return false; })([](auto _) { return true; });
};

inline constexpr auto fromLeft = [](auto d) {
  return [d](auto e) {
    return e([](auto x) { return x; })([d](auto _) { return d; });
  };
};

inline constexpr auto fromRight = [](auto d) {
  return [d](auto e) {
    return e([d](auto _) { return d; })([](auto x) { return x; });
  };
};

inline constexpr auto either = [](auto l) {
  return [l](auto r) { return [l, r](auto e) { return e(l)(r); }; };
};
} // namespace churchEither

// inline constexpr auto fst = [](ex::sender auto p) -> ex::sender auto{
//         return ex::then(p, [](auto l, auto r) { return l; });
// };

inline constexpr auto left = [](auto a) {
  // return [a](auto l) { return [l, a](auto _) { return l(a); }; };
  return [a](auto l) { return [l, a](auto _) { return ex::just(a) | l ; }; };
};

inline constexpr auto isLeft = [](auto e) {
  // return e([](auto _) { return true; })([](auto _) { return false; });
  return e | ex::then([](auto _){return true;}) | ex::then([](auto _){return false;});
 };


int main() {
        using namespace std::string_literals;

        auto result = ex::sync_wait(example_sender(17));
        assert(result);
        assert(*result == std::tuple(17));
        std::cout << std::get<0>(*result) << '\n';

        ex::sender auto pair1 = ex::just(3.14, 42);

        auto result2 = ex::sync_wait(fst(pair1));
        std::cout << std::get<0>(*result2) << '\n';

        auto result3 = ex::sync_wait(snd(pair1));
        std::cout << std::get<0>(*result3) << '\n';

        auto p2 = pair(9, 13);
        auto r4 = fst(p2);
        auto r5 = snd(p2);

        auto k4 = ex::sync_wait(r4);
        auto k5 = ex::sync_wait(r5);
        std::cout << std::get<0>(*k4) << '\n';
        std::cout << std::get<0>(*k5) << '\n';

}


inline auto tst = [](bool cond,
                     ex::sender auto left,
                     ex::sender auto right) -> ex::sender auto {
        if (cond)
                return left;
        else
                return right;
};
