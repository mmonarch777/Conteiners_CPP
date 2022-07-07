#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP
# include "iterators_traits.hpp"

namespace ft
{
    template <class Iterator>
    class reverse_iterator
    {
    public:
        typedef Iterator                                                    iterator_type;
        typedef typename iterator_traits<iterator_type>::value_type         value_type;
        typedef typename iterator_traits<iterator_type>::pointer            pointer;
        typedef typename iterator_traits<iterator_type>::reference          reference;
        typedef typename iterator_traits<iterator_type>::difference_type    difference_type;

    protected:
        iterator_type ptr;

    public:
        reverse_iterator() : ptr(NULL) {};
        explicit reverse_iterator(iterator_type ptr): ptr(ptr) {};

        template <class Iter>
        reverse_iterator(const reverse_iterator<Iter> & other) : ptr(other.base()) {}
        virtual ~reverse_iterator() {};

        reverse_iterator &operator=(const reverse_iterator &other)
        {
            if (this != &other)
                ptr = other.ptr;
            return *this;
        }
        reverse_iterator operator-=(iterator_type p )
        {
            ptr = ptr + p;
            return *this;
        }
        reverse_iterator operator+=(iterator_type p )
        {
            ptr = ptr - p;
            return *this;
        }
        reverse_iterator operator-(iterator_type p ) const
        {
            ptr = ptr + p;
            return *this;
        }
        reverse_iterator operator+(iterator_type p ) const
        {
            ptr = ptr - p;
            return *this;
        }
        difference_type operator-(const reverse_iterator &other) const
        {
            return (other.ptr - ptr);
        }
        reference operator*() const
        {
            iterator_type buf = ptr;
            buf--;
            return *buf;
        }
        pointer operator->() const
        {
            return &(*this);
        }
        reference operator[](difference_type p ) const
        {
            iterator_type buf = ptr - p - 1;
            return *buf;
        }
        iterator_type base() const
        {
            return *this;
        }

        reverse_iterator & operator++()
        {
            this->ptr--;
            return *this;
        }
        reverse_iterator &operator--()
        {
            this->ptr++;
            return *this;
        }
        reverse_iterator operator++(int )
        {
            reverse_iterator buf = *this;
            this->ptr--;
            return buf;
        }
        reverse_iterator operator--(int )
        {
            reverse_iterator buf = *this;
            this->ptr++;
            return buf;
        }

        bool operator==(const reverse_iterator &other)
        {
            return (ptr = other.ptr);
        }
        bool operator!=(const reverse_iterator &other)
        {
            return (ptr !=other.ptr);
        }
        bool operator>(const reverse_iterator &other) const
        {
            return (ptr < other.ptr);
        }
        bool operator<(const reverse_iterator &other) const
        {
            return (ptr > other.ptr);
        }
        bool operator>=(const reverse_iterator &other) const
        {
            return (ptr <= other.ptr);
        }
        bool operator<=(const reverse_iterator &other) const
        {
            return (ptr >= other.ptr);
        }
    };

    template <class Iterator, class Iterator2>
    bool operator!=(reverse_iterator<Iterator> const &rev1, reverse_iterator<Iterator2> const &rev2)
    {
        return (rev1.base() != rev2.base());
    }
    template <class Iterator, class Iterator2>
    bool operator==(reverse_iterator<Iterator> const &rev1, reverse_iterator<Iterator2> const &rev2)
    {
        return (rev1.base() == rev2.base());
    }
    template <class Iterator, class Iterator2>
    bool operator>(reverse_iterator<Iterator> const &rev1, reverse_iterator<Iterator2> const &rev2)
    {
        return (rev1.base() < rev2.base());
    }
    template <class Iterator, class Iterator2>
    bool operator<(reverse_iterator<Iterator> const &rev1, reverse_iterator<Iterator2> const &rev2)
    {
        return (rev1.base() > rev2.base());
    }
    template <class Iterator, class Iterator2>
    bool operator>=(reverse_iterator<Iterator> const &rev1, reverse_iterator<Iterator2> const &rev2)
    {
        return (rev1.base() <= rev2.base());
    }
    template <class Iterator, class Iterator2>
    bool operator<=(reverse_iterator<Iterator> const &rev1, reverse_iterator<Iterator2> const &rev2)
    {
        return (rev1.base() >= rev2.base());
    }
    template <typename Iterator>
    reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type nb,
            const reverse_iterator<Iterator> &rev )
    {
        return (reverse_iterator<Iterator>(rev.base() - nb));
    }
    template <typename Iterator>
    reverse_iterator<Iterator> operator-(typename reverse_iterator<Iterator>::difference_type nb,
             const reverse_iterator<Iterator> &rev )
    {
        return (reverse_iterator<Iterator>(rev.base() + nb));
    }
}
#endif