#include <beman/execution/execution.hpp>
#include <iostream>

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

int main() {
        using namespace std::string_literals;

        auto result = ex::sync_wait(example_sender(17));
        assert(result);
        assert(*result == std::tuple(17));
        std::cout << std::get<0>(*result) << '\n';
}
