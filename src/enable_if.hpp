//
// Created by Aurele Josserand on 10/13/22.
//

#ifndef CONTAINERS_ENABLE_IF_H
#define CONTAINERS_ENABLE_IF_H

namespace ft {
    template<bool Cond, class T = void>
    struct enable_if {
    };

    template<class T>
    struct enable_if<true, T> {
        typedef T type;
    };

    template< class T >
    struct is_integral{
        /*typedef _LIBCPP_BOOL_CONSTANT(true)  true_type;
        typedef _LIBCPP_BOOL_CONSTANT(false) false_type;

        template <class _Tp> struct is_integral                     : public false_type {};
        template <>          struct is_integral<bool>               : public true_type {};
        template <>          struct is_integral<char>               : public true_type {};
        template <>          struct is_integral<signed char>        : public true_type {};
        template <>          struct is_integral<unsigned char>      : public true_type {};
        template <>          struct is_integral<wchar_t>            : public true_type {};*/

        };
}
#endif //CONTAINERS_ENABLE_IF_H
