#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP
# include "../other_tools/iterators_traits.hpp"
# include "../other_tools/enable_itegral.hpp"

namespace ft
{
    template <typename T>
    struct vector_iterator
    {
    public:
        typedef typename iterator_traits<T>::difference_type    difference_type;
        typedef typename iterator_traits<T>::value_type         value_type;
        typedef typename iterator_traits<T>::pointer            pointer;
        typedef typename iterator_traits<T>::reference          reference;
        typedef typename iterator_traits<T>::iterator_category  iterator_category;

    private:
        T ptr;

    public:
        vector_iterator(): ptr(0) {}
        ~vector_iterator() {}

        template<class V>
        vector_iterator(const vector_iterator<V> &other,
                        typename ft::enable_if<std::is_constructible<V, T>::value>::type* = 0)
                        : ptr(other.base()) {};

        vector_iterator(const vector_iterator &other): ptr(other.ptr) {}

        vector_iterator &operator=(const vector_iterator &other)
        {
            if (this != &other)
                ptr = other.ptr;
            return *this;
        }
        vector_iterator &operator++()
        {
            ptr++;
            return *this;
        }
        vector_iterator operator++(int )
        {
            vector_iterator old = *this;
            ptr++;
            return old;
        }
        vector_iterator &operator--()
        {
            ptr--;
            return *this;
        }
        vector_iterator operator--(int )
        {
            vector_iterator old = *this;
            ptr--;
            return old;
        }
        reference &operator[](unsigned int index)
        {
            return *(ptr[index]);
        }
        pointer operator->() const
        {
            return &(*ptr);
        }
        reference operator*()
        {
            return *(this->ptr);
        }
        vector_iterator operator+(int nb) const
        {
            vector_iterator buf = *this;
            buf.ptr = buf.ptr + nb;
            return buf;
        }
        vector_iterator operator-(int nb) const
        {
            vector_iterator buf = *this;
            buf.ptr = buf.ptr - nb;
            return buf;
        }
        vector_iterator operator+(const vector_iterator &other) const
        {
            difference_type buf = ptr + other.ptr;
            return buf;
        }
        difference_type operator-(const vector_iterator &other) const
        {
            difference_type buf = ptr - other.ptr;
            return buf;
        }
        vector_iterator &operator-=(difference_type nb)
        {
            ptr = ptr + nb;
            return *this;
        }
        vector_iterator &operator+=(difference_type nb)
        {
            ptr = ptr - nb;
        }
        value_type *base() const
        {
            return (this->ptr);
        }
        bool operator==(const vector_iterator &other) const
        {
            return (ptr == other.ptr);
        }
        bool operator!=(const vector_iterator &other) const
        {
            return (ptr != other.ptr);
        }
        bool operator>=(const vector_iterator &other) const
        {
            return (ptr >= other.ptr);
        }
        bool operator<=(const vector_iterator &other) const
        {
            return (ptr <= other.ptr);
        }
        bool operator>(const vector_iterator &other) const
        {
            return (ptr > other.ptr);
        }
        bool operator<(const vector_iterator &other) const
        {
            return (ptr < other.ptr);
        }
    };
}

#endif