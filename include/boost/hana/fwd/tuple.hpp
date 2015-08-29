/*!
@file
Forward declares `boost::hana::tuple`.

@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_TUPLE_HPP
#define BOOST_HANA_FWD_TUPLE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/integral_constant.hpp>
#include <boost/hana/fwd/type.hpp>


namespace boost { namespace hana {
    //! @ingroup group-datatypes
    //! General purpose index-based heterogeneous sequence with a fixed length.
    //!
    //! The tuple is the bread and butter for static metaprogramming.
    //! Conceptually, it is like a `std::tuple`; it is a container able
    //! of holding objects of different types and whose size is fixed at
    //! compile-time. However, Hana's tuple provides much more functionality
    //! than its `std` counterpart, and it is also much more efficient than
    //! all standard library implementations tested so far.
    //!
    //! Tuples are index-based sequences. If you need an associative
    //! sequence with a key-based access, then you should consider
    //! `hana::map` or `hana::set` instead.
    //!
    //!
    //! Modeled concepts
    //! ----------------
    //! `Sequence`, and all the concepts it refines
    //!
    //!
    //! Provided operators
    //! ------------------
    //! For convenience, the following operators are provided:
    //! @code
    //!     xs == ys        ->          equal(xs, ys)
    //!     xs != ys        ->          not_equal(xs, ys)
    //!
    //!     xs < ys         ->          less(xs, ys)
    //!     xs <= ys        ->          less_equal(xs, ys)
    //!     xs > ys         ->          greater(xs, ys)
    //!     xs >= ys        ->          greater_equal(xs, ys)
    //!
    //!     xs | f          ->          chain(xs, f)
    //!
    //!     xs[n]           ->          at(xs, n)
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/tuple/tuple.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename ...Xn>
    struct tuple {
        //! Default constructs the `tuple`. Only exists when all the elements
        //! of the tuple are default constructible.
        constexpr tuple();

        //! Initialize each element of the tuple with the corresponding element
        //! from `xn...`. Only exists when all the elements of the tuple are
        //! copy-constructible.
        //!
        //! @note
        //! Unlike the corresponding constructor for `std::tuple`, this
        //! constructor is not explicit. This allows returning a tuple
        //! from a function with the brace-initialization syntax.
        constexpr tuple(Xn const& ...xn);

        //! Initialize each element of the tuple by perfect-forwarding the
        //! corresponding element in `yn...`. Only exists when all the
        //! elements of the created tuple are constructible from the
        //! corresponding perfect-forwarded value.
        //!
        //! @note
        //! Unlike the corresponding constructor for `std::tuple`, this
        //! constructor is not explicit. This allows returning a tuple
        //! from a function with the brace-initialization syntax.
        template <typename ...Yn>
        constexpr tuple(Yn&& ...yn);

        //! Copy-initialize a tuple from another tuple. Only exists when all
        //! the elements of the constructed tuple are copy-constructible from
        //! the corresponding element in the source tuple.
        template <typename ...Yn>
        constexpr tuple(tuple<Yn...> const& other);

        //! Move-initialize a tuple from another tuple. Only exists when all
        //! the elements of the constructed tuple are move-constructible from
        //! the corresponding element in the source tuple.
        template <typename ...Yn>
        constexpr tuple(tuple<Yn...>&& other);

        //! Assign a tuple to another tuple. Only exists when all the elements
        //! of the destination tuple are assignable from the corresponding
        //! element in the source tuple.
        template <typename ...Yn>
        constexpr tuple& operator=(tuple<Yn...> const& other);

        //! Move-assign a tuple to another tuple. Only exists when all the
        //! elements of the destination tuple are move-assignable from the
        //! corresponding element in the source tuple.
        template <typename ...Yn>
        constexpr tuple& operator=(tuple<Yn...>&& other);
    };
#else
    template <typename ...Xn>
    struct tuple;
#endif

    //! Tag representing `hana::tuple`s.
    //! @related tuple
    struct Tuple { };

#ifdef BOOST_HANA_DOXYGEN_INVOKED
    //! Function object for creating a `tuple`.
    //! @relates hana::tuple
    //!
    //! Given zero or more objects `xs...`, `make<Tuple>` returns a new tuple
    //! containing those objects. The elements are held by value inside the
    //! resulting tuple, and they are hence copied or moved in. This is
    //! analogous to `std::make_tuple` for creating Hana tuples.
    //!
    //!
    //! Example
    //! -------
    //! @include example/tuple/make.cpp
    template <>
    constexpr auto make<Tuple> = [](auto&& ...xs) {
        return tuple<std::decay_t<decltype(xs)>...>{forwarded(xs)...};
    };
#endif

    //! Alias to `make<Tuple>`; provided for convenience.
    //! @relates hana::tuple
    constexpr auto make_tuple = make<Tuple>;

    //! Create a tuple specialized for holding `Type`s.
    //! @relates hana::tuple
    //!
    //! This is functionally equivalent to `make<Tuple>(type<T>...)`, except
    //! that using `tuple_t` allows the library to perform some compile-time
    //! optimizations. Also note that the type of the objects returned by
    //! `tuple_t` and an equivalent call to `make<Tuple>` may differ.
    //!
    //!
    //! Example
    //! -------
    //! @include example/tuple/tuple_t.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename ...T>
    constexpr unspecified-type tuple_t{};
#else
    template <typename ...T>
    constexpr auto tuple_t = hana::make<Tuple>(gcc_wknd::mktype<T>()...);
#endif

    //! Create a tuple specialized for holding `hana::integral_constant`s.
    //! @relates hana::tuple
    //!
    //! This is functionally equivalent to `make<Tuple>(integral_c<T, v>...)`,
    //! except that using `tuple_c` allows the library to perform some
    //! compile-time optimizations. Also note that the type of the objects
    //! returned by `tuple_c` and an equivalent call to `make<Tuple>` may differ.
    //!
    //!
    //! Example
    //! -------
    //! @include example/tuple/tuple_c.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename T, T ...v>
    constexpr unspecified-type tuple_c{};
#else
    template <typename T, T ...v>
    constexpr auto tuple_c = hana::make_tuple(hana::integral_constant<T, v>{}...);
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_TUPLE_HPP
