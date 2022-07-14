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
        T rbt_node;

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

        node_iterator(T value = nullptr) : rbt_node(value) {};
        ~node_iterator() {};

        template <typename N1, typename N2>
        node_iterator(const node_iterator<N1, N2> &other,
                      typename ft::enable_if<std::is_convertible<N1, N2>::type>::type* = 0)
                       : rbt_node(other.rbt_node) {};

        iterator_type base() const
        {
            return rbt_node;
        }
        node_iterator &operator=(const node_iterator &other)
        {
            if (this != &other)
                rbt_node = other.rbt_node;
            return *this;
        }
        node_iterator operator++(int)
        {
            node_iterator tmp = *this;
            increment();
            return tmp;
        }
        node_iterator &operator++()
        {
            increment();
            return *this;
        }
        node_iterator operator--(int)
        {
            node_iterator tmp = *this;
            decrement();
            return tmp;
        }
        node_iterator &operator--()
        {
            decrement();
            return *this;
        }
        reference operator*()
        {
            return *(rbt_node->pair);
        }
        const_ref operator*() const
        {
            return *(rbt_node->pair);
        }
        pointer operator->()
        {
            return (rbt_node->pair);
        }
        const_pointer operator->() const
        {
            return (rbt_node->pair);
        }
        bool operator==(node_iterator const &other) const
        {
            return rbt_node == other.rbt_node;
        };
        bool operator!=(node_iterator const &other) const
        {
            return rbt_node != other.rbt_node;
        };
        bool operator>(node_iterator const &other) const
        {
            return rbt_node->pair > other.rbt_node->pair;
        };
        bool operator<(node_iterator const &other) const
        {
            return other.rbt_node->pair > rbt_node->pair;
        };
        bool operator<=(node_iterator const &other) const
        {
            return rbt_node->pair <= other.rbt_node->pair;
        };
        bool operator>=(node_iterator const &other) const
        {
            return rbt_node->pair >= other.rbt_node->pair;
        };

        void increment()
        {
            if (rbt_node->NIL)
                rbt_node = rbt_node->begin;
            else if (!rbt_node->right->NIL)
            {
                rbt_node = rbt_node->right;
                while (!rbt_node->left->NIL)
                    rbt_node = rbt_node->left;
            }
            else
            {
                T current = rbt_node;
                T tmp = rbt_node;
                rbt_node = rbt_node->parent;
                if (!rbt_node) { rbt_node = current->right; return; }
                while (rbt_node->left != tmp)
                {
                    if (!rbt_node->parent)
                    {
                        rbt_node = current->right;
                        break;
                    }
                    tmp = rbt_node;
                    rbt_node = rbt_node->parent;
                }
            }
        }
        void decrement()
        {
            if (!rbt_node->left->NIL)
            {
                rbt_node = rbt_node->left;
                while (!rbt_node->right->NIL)
                    rbt_node = rbt_node->right;
            }
            else
            {
                T tmp = rbt_node;
                rbt_node = rbt_node->parent;
                while (rbt_node->right != tmp)
                {
                    tmp = rbt_node;
                    if (!rbt_node->parent)
                    {
                        rbt_node = tmp->left;
                        break;
                    }
                    rbt_node = rbt_node->parent;
                }
            }
        }
    };
}

#endif