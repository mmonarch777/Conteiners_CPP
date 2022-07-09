#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP
# include <limits>

namespace ft
{
//    ===============enable_if==================
    template <bool Cond, typename T = void>
    struct enable_if {};

    template <typename T>
    struct enable_if<true, T>
    {typedef T type;};

//    ===============is_integral==================
    template <class T, T v>
    struct intergral_constant
    {
        typedef T value_type;
        typedef intergral_constant<T, v> type;

        static const value_type value = v;

        operator value_type() const
        {
            return value;
        }
    };

    template<class T> struct is_integral : ft::intergral_constant<T, false> {};
    template<> struct is_integral<bool> : ft::intergral_constant<bool, true> {};
    template<> struct is_integral<char> : ft::intergral_constant<bool, true> {};
    template<> struct is_integral<char16_t> : ft::intergral_constant<bool, true> {};
    template<> struct is_integral<char32_t> : ft::intergral_constant<bool, true> {};
    template<> struct is_integral<wchar_t> : ft::intergral_constant<bool, true> {};
    template<> struct is_integral<short> : ft::intergral_constant<bool, true> {};
    template<> struct is_integral<int> : ft::intergral_constant<bool, true> {};
    template<> struct is_integral<long> : ft::intergral_constant<bool, true> {};
    template<> struct is_integral<long long> : ft::intergral_constant<bool, true> {};
    template<> struct is_integral<unsigned long> : ft::intergral_constant<bool, true> {};
    template<> struct is_integral<unsigned char> : ft::intergral_constant<bool, true> {};
    template<> struct is_integral<unsigned short> : ft::intergral_constant<bool, true> {};
    template<> struct is_integral<unsigned int> : ft::intergral_constant<bool, true> {};
    template<> struct is_integral<unsigned long long> : ft::intergral_constant<bool, true> {};
}

#endif
