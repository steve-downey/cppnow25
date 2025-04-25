// include/beman/execution/detail/connect.hpp                       -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef INCLUDED_BEMAN_EXECUTION_DETAIL_CONNECT
#define INCLUDED_BEMAN_EXECUTION_DETAIL_CONNECT

#include <beman/execution/detail/transform_sender.hpp>
#include <beman/execution/detail/get_domain_late.hpp>
#include <beman/execution/detail/get_env.hpp>
#include <beman/execution/detail/operation_state.hpp>
#include <beman/execution/detail/connect_awaitable.hpp>
#include <type_traits>
#include <concepts>

// ----------------------------------------------------------------------------

namespace beman::execution::detail {
/*!
 * \brief The actual implementation of the connect customization point type
 * \headerfile beman/execution/execution.hpp <beman/execution/execution.hpp>
 * \internal
 */
struct connect_t {
  private:
    template <typename Sender, typename Receiver>
    static auto make_new_sender(Sender&& sender, Receiver&& receiver)
        //-dk:TODO this noexcept needs to get confirmed/fixed
        noexcept(true) -> decltype(auto) {
        return ::beman::execution::transform_sender(
            decltype(::beman::execution::detail::get_domain_late(::std::forward<Sender>(sender),
                                                                 ::beman::execution::get_env(receiver))){},
            ::std::forward<Sender>(sender),
            ::beman::execution::get_env(receiver));
    }
    template <typename Sender, typename Receiver>
    static constexpr auto connect_noexcept() -> bool {
        if constexpr (requires {
                          make_new_sender(::std::declval<Sender>(), ::std::declval<Receiver>())
                              .connect(::std::declval<Receiver>());
                      }) {
            return noexcept(make_new_sender(::std::declval<Sender>(), ::std::declval<Receiver>())
                                .connect(::std::declval<Receiver>()));
        } else if constexpr (requires {
                                 ::beman::execution::detail::connect_awaitable(
                                     make_new_sender(::std::declval<Sender>(), ::std::declval<Receiver>()),
                                     ::std::declval<Receiver>());
                             }) {
            return noexcept(::beman::execution::detail::connect_awaitable(
                make_new_sender(::std::declval<Sender>(), ::std::declval<Receiver>()), ::std::declval<Receiver>()));
        }
        return true;
    }

  public:
    template <typename Sender, typename Receiver>
    auto operator()(Sender&& sender, Receiver&& receiver) const noexcept(connect_noexcept<Sender, Receiver>()) {
        auto new_sender = [&sender, &receiver]() -> decltype(auto) {
            return make_new_sender(::std::forward<Sender>(sender), ::std::forward<Receiver>(receiver));
        };

        if constexpr (requires { new_sender().connect(::std::forward<Receiver>(receiver)); }) {
            using state_type = decltype(new_sender().connect(::std::forward<Receiver>(receiver)));
            static_assert(::beman::execution::operation_state<state_type>);
            return new_sender().connect(::std::forward<Receiver>(receiver));
        } else if constexpr (requires {
                                 ::beman::execution::detail::connect_awaitable(new_sender(),
                                                                               ::std::forward<Receiver>(receiver));
                             }) {
            return ::beman::execution::detail::connect_awaitable(new_sender(), ::std::forward<Receiver>(receiver));
        } else {
            enum bad_sender {};
            static_assert(::std::same_as<bad_sender, decltype(new_sender())>,
                          "result from transform_sender has no suitable connect()");
        }
    }
};
} // namespace beman::execution::detail

namespace beman::execution {
/*!
 * \brief Type of the connect customization point object.
 * \headerfile beman/execution/execution.hpp <beman/execution/execution.hpp>
 */
using beman::execution::detail::connect_t;
/*!
 * \brief Customization point object used to connect a sender and a receiver.
 * \headerfile beman/execution/execution.hpp <beman/execution/execution.hpp>
 *
 * \details
 * `connect(sender, receiver)` returns the result of calling `sender.connect(receiver)`.
 * The returned object `state` is an `operation_state` object.
 */
inline constexpr connect_t connect{};
} // namespace beman::execution

// ----------------------------------------------------------------------------

#endif
