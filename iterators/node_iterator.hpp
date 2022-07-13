#ifndef NODE_ITERATOR_HPP
#define NODE_ITERATOR_HPP
#include "iterators_traits.hpp"
#include "../other_tools/enable_integral.hpp"

namespace ft
{
    template <class T, class Pair>
    class node_iterator
    {
    private:
        T node;

    public:
        typedef T                                               iterator_type;
        typedef Pair                                            value_type;
        typedef typename iterator_traits<T>::difference_type    difference_type;
        typedef Pair&                                           reference;
        typedef const Pair&                                     const_ref;
        typedef Pair*                                           pointer;
        typedef const Pair*                                     const_pointer;
        typedef typename iterator_traits<T>::iterator_category  iterator_category;

        /*============================================================================================*/
        /*===================================== MEMBER FUNCTIONS =====================================*/
        /*============================================================================================*/

        node_iterator(T value = nullptr) : node(value) {};
        ~node_iterator() {};

        template <typename N1, typename N2>
        node_iterator(const node_iterator<N1, N2> &other,
                      typename ft::enable_if<std::is_convertible<N1, N2>::type>::type* = 0)
                       : node(other.node) {};

        iterator_type base() const
        {
            return node;
        }
        node_iterator &operator=(const node_iterator &other)
        {
            if (this != &other)
                node = other.node;
            return *this;
        }

    };
}

#endif