#ifndef ITERATORS_TRAITS_HPP
# define ITERATORS_TRAITS_HPP
# include <cstddef>
# include <iterator>
namespace ft
{
//    template <class I>
//    struct iterator_traits
//    {
//    public:
//        typedef typename I::difference_type      difference_type;
//        typedef typename I::value_type           value_type;
//        typedef typename I::pointer              pointer;
//        typedef typename I::const_pointer        const_pointer;
//        typedef typename I::reference            reference;
//        typedef typename I::const_reference      const_reference;
//        typedef typename I::iterator_category    iterator_category;
//    };
//
//    template<typename T>
//    struct iterator_traits<T*>
//    {
//    public:
//        typedef std::ptrdiff_t                  difference_type;
//        typedef T                               value_type;
//        typedef T*                              pointer;
//        typedef const T*                        const_pointer;
//        typedef T&                              reference;
//        typedef const T&                        const_reference;
//        typedef std::random_access_iterator_tag iterator_category;
//    };
    template <typename Iterator>
    struct iterator_traits
    {
    public:
        typedef typename Iterator::difference_type      difference_type;
        typedef typename Iterator::value_type           value_type;
        typedef typename Iterator::pointer              pointer;
        typedef typename Iterator::reference            reference;
        typedef typename Iterator::iterator_category    iterator_category;
    };

    template<typename T>
    struct iterator_traits<T*>
    {
    public:
        typedef std::ptrdiff_t                  difference_type;
        typedef T                               value_type;
        typedef T*                              pointer;
        typedef T&                              reference;
        typedef std::random_access_iterator_tag iterator_category;
    };

    template <typename T>
    struct iterator_traits<const T*>
    {
    public:
        typedef std::ptrdiff_t                  difference_type;
        typedef T                               value_type;
        typedef const T*                        pointer;
        typedef const T&                        reference;
        typedef std::random_access_iterator_tag iterator_category;
    };
}

#endif