// include/beman/execution/detail/sends_stopped.hpp                 -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef INCLUDED_BEMAN_EXECUTION_DETAIL_SENDS_STOPPED
#define INCLUDED_BEMAN_EXECUTION_DETAIL_SENDS_STOPPED

#include <beman/execution/detail/completion_signatures_of_t.hpp>
#include <beman/execution/detail/empty_env.hpp>
#include <beman/execution/detail/gather_signatures.hpp>
#include <beman/execution/detail/sender_in.hpp>
#include <beman/execution/detail/set_stopped.hpp>
#include <beman/execution/detail/type_list.hpp>
#include <concepts>

// ----------------------------------------------------------------------------

namespace beman::execution {
template <typename Sender, typename Env = ::beman::execution::empty_env>
    requires ::beman::execution::sender_in<Sender, Env>
inline constexpr bool sends_stopped{not::std::same_as<
    ::beman::execution::detail::type_list<>,
    ::beman::execution::detail::gather_signatures< ::beman::execution::set_stopped_t,
                                                   ::beman::execution::completion_signatures_of_t<Sender, Env>,
                                                   ::beman::execution::detail::type_list,
                                                   ::beman::execution::detail::type_list> >};
}

// ----------------------------------------------------------------------------

#endif
