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

// 85dedb42-2c9c-43d5-8157-edc8dbc1df34
inline constexpr auto pair = [](auto l, auto r) {
        return [l, r](auto p) { return p(l, r); };
};
// 85dedb42-2c9c-43d5-8157-edc8dbc1df34 end

// d7eb7f23-6f65-42c7-9814-9f85163d755f
inline constexpr auto fst = [](auto p) {
        return p([](auto l, auto r) { return l; });
};

inline constexpr auto snd = [](auto p) {
        return p([](auto l, auto r) { return r; });
};
// d7eb7f23-6f65-42c7-9814-9f85163d755f end

int main() {
        using namespace std::string_literals;

        auto result = ex::sync_wait(example_sender(17));
        assert(result);
        assert(*result == std::tuple(17));
        std::cout << std::get<0>(*result) << '\n';

        ex::sender auto pair = ex::just(3.14, 42);
        auto fst = [](ex::sender auto p) -> ex::sender auto {
                return ex::then(p, [](auto l, auto r) { return l; });
        };

        auto snd = [](ex::sender auto p) -> ex::sender auto {
                return ex::then(p, [](auto l, auto r) { return r; });
        };

        auto result2 = ex::sync_wait(fst(pair));
        std::cout << std::get<0>(*result2) << '\n';

        auto result3 = ex::sync_wait(snd(pair));
        std::cout << std::get<0>(*result3) << '\n';
}
