/*!
@file
Defines `boost::hana::Logical`.

@copyright Louis Dionne 2014
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_LOGICAL_HPP
#define BOOST_HANA_LOGICAL_HPP

#include <boost/hana/fwd/logical.hpp>

#include <boost/hana/core/datatype.hpp>
#include <boost/hana/core/operators.hpp>
#include <boost/hana/detail/std/enable_if.hpp>
#include <boost/hana/detail/std/forward.hpp>


namespace boost { namespace hana {
    //! Minimal complete definition: `eval_if` and `not_`
    struct Logical::mcd {
        template <typename X, typename Y>
        static constexpr auto or_impl(X x, Y y)
        { return if_(x, x, y); }

        template <typename X, typename Y>
        static constexpr auto and_impl(X x, Y y)
        { return if_(x, y, x); }

        template <typename C, typename T, typename E>
        static constexpr auto if_impl(C c, T t, E e) {
            return eval_if(c,
                [=](auto) { return t; },
                [=](auto) { return e; }
            );
        }
    };

    namespace operators {
        //! Equivalent to `and_`.
        //! @relates boost::hana::Logical
        template <typename X, typename Y, typename = typename detail::std::enable_if<
            enable_operators<Logical, datatype_t<X>>::value ||
            enable_operators<Logical, datatype_t<Y>>::value
        >::type>
        constexpr decltype(auto) operator&&(X&& x, Y&& y) {
            return and_(
                detail::std::forward<X>(x),
                detail::std::forward<Y>(y)
            );
        }

        //! Equivalent to `or_`.
        //! @relates boost::hana::Logical
        template <typename X, typename Y, typename = typename detail::std::enable_if<
            enable_operators<Logical, datatype_t<X>>::value ||
            enable_operators<Logical, datatype_t<Y>>::value
        >::type>
        constexpr decltype(auto) operator||(X&& x, Y&& y) {
            return or_(
                detail::std::forward<X>(x),
                detail::std::forward<Y>(y)
            );
        }

        //! Equivalent to `not_`.
        //! @relates boost::hana::Logical
        template <typename X, typename = typename detail::std::enable_if<
            enable_operators<Logical, datatype_t<X>>::value
        >::type>
        constexpr decltype(auto) operator!(X&& x) {
            return not_(detail::std::forward<X>(x));
        }
    }
}} // end namespace boost::hana

#endif // !BOOST_HANA_LOGICAL_HPP
