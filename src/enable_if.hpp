//
// Created by Aurele Josserand on 10/13/22.
//
#ifndef CONTAINERS_ENABLE_IF_H
#define CONTAINERS_ENABLE_IF_H

# include <iostream>
# include <cstddef>
# include <array>
# include <memory>

namespace ft {
    template<bool Cond, class T = void>
    struct enable_if {
    };

    template<class T>
    struct enable_if<true, T> {
        typedef T type;
    };

        template <class _Tp> struct is_integral                     : public std::false_type {};
        template <>          struct is_integral<bool>               : public std::true_type {};
        template <>          struct is_integral<char>               : public std::true_type {};
        template <>          struct is_integral<signed char>        : public std::true_type {};
        template <>          struct is_integral<unsigned char>      : public std::true_type {};
        template <>          struct is_integral<wchar_t>            : public std::true_type {};
        template <>          struct is_integral<short>              : public std::true_type {};
        template <>          struct is_integral<unsigned short>     : public std::true_type {};
        template <>          struct is_integral<int>                : public std::true_type {};
        template <>          struct is_integral<unsigned int>       : public std::true_type {};
        template <>          struct is_integral<long>               : public std::true_type {};
        template <>          struct is_integral<unsigned long>      : public std::true_type {};
        template <>          struct is_integral<long long>          : public std::true_type {};
        template <>          struct is_integral<unsigned long long> : public std::true_type {};

}
#endif 