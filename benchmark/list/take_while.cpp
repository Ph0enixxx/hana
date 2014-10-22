/*
@copyright Louis Dionne 2014
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#include <boost/hana/bool.hpp>
#include <boost/hana/fwd/list.hpp>

#include "benchmark.hpp"

<%= setup %>

template <int i> struct x { };


int main() {
    auto list = <%= list %>;
    auto pred = [](auto&& x) { return boost::hana::true_; };

    boost::hana::benchmark::measure([=] {
        boost::hana::take_while(list, pred);
    });
}
