#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <iostream>
# include <memory>
# include "vector_iterator.hpp"
# include "../other_tools/reverse_iterator.hpp"

namespace ft
{
    template <class T, class Allocator = std::allocator<T> >
    class Vector
    {
    public:
        typedef T                                       value_type;
        typedef Allocator                               alloc_type;
        typedef value_type&                             reference;
        typedef const value_type&                       const_ref;
        typedef T*                                      pointer;
        typedef const T*                                const_pointer;
        typedef ft::vector_iterator<T*>                 iterator;
        typedef ft::vector_iterator<const T*>           const_iter;
        typedef ft::reverse_iterator<iterator>          reverse_iter;
        typedef ft::reverse_iterator<const_iter>        const_reverse_iter;
        typedef std::ptrdiff_t                          difference_type;
        typedef std::size_t                             size_type;

    private:
        pointer     vector;
        size_type   _capacity;
        size_type   _size;
        alloc_type  allocator;

    public:
        explicit Vector(const Allocator& alloc = Allocator()) : vector(0), _capacity(0), _size(0), allocator(alloc) {};
        Vector(size_type nb, const_ref value = value_type(), const Allocator &alloc = Allocator())
        {
            if (nb < 0)
                throw std::out_of_range("Vector: out of range.");
            allocator = alloc;
            _capacity = nb;
            _size = nb;
            vector = allocator.allocate(_capacity);
            for (size_t i = 0; i < nb; i++)
                vector[i] = value;
        }

        template <class OtherIter>
        Vector(OtherIter first, OtherIter last, const Allocator &alloc = Allocator(),
               typename ft::enable_if<!ft::is_integral<OtherIter>::value, void>::type* = 0)
               : _capacity(0), _size(0), allocator(alloc)
        {
            vector = allocator.allocate(_capacity);
            this->assign(first, last);
        }
        Vector(const Vector &other) :vector(0), _capacity(other._capacity), _size(other._size), allocator(other.allocator)
        {
            vector = allocator.allocator(other._capacity);
            for (size_t i = 0; i < _size; i++)
                vector[i] = other.vector[i];
        }
        ~Vector()
        {
            this->clear();
            allocator.deallocate(vector, _capacity);
        }
        Vector &operator=(const Vector &other)
        {
            if (this != &other)
            {
                this->clear();
                allocator.deallocate(vector, _capacity);
                _capacity = other._capacity;
                _size = other._size;
                vector = allocator.allocate(_capacity);
                for (size_t i = 0; i < _size; i++)
                    vector[i] = other.vector[i];
            }
            return *this;
        }
        /*============================ ALLOCATOR =============================*/

        alloc_type get_allocator() const
        {
            return (this->allocator);
        }

        /*============================ ITERATORS =============================*/

        iterator            begin()                                 {return (iterator(vector));};
        const_iter          begin() const                           {return (const_iter(vector));};
        iterator            end()                                   {return (iterator(vector + _size));};
        const_iter          end() const                             {return (const_iter(vector + _size));};
        reverse_iter        rbegin()                                {return (reverse_iter(vector + _size - 1));};
        const_reverse_iter  rbegin() const                          {return (const_reverse_iter(vector + _size + 1));};
        reverse_iter        rend()                                  {return (reverse_iter(vector - 1));};
        const_reverse_iter  rend() const                            {return (const_reverse_iter(vector - 1));};

        /*============================ CAPACITY =============================*/

        size_type           size() const                            {return (_size);};
        size_type           max_size() const                        {return (std::min((size_type) std::numeric_limits<difference_type>::max(),
                                                                             std::numeric_limits<size_type>::max() / sizeof (value_type)));};
        size_type           capacity() const                        {return (_capacity);};
        bool                empty() const                           {return (_size <= 0);};

        void reserve(size_type count)
        {
            if (count > _capacity)
            {
                pointer buf = allocator.allocate(count);
                for (size_t i = 0;i < _size; ++i)
                    buf[i] = vector[i];
                if (vector)
                    allocator.deallocate(vector, _capacity);
                _capacity = count;
                vector = buf;
            }
        }

        /*============================ ELEMENT ACCESS =============================*/

        reference           operator[](size_type position)          {return (vector[position]);};
        const_ref           operator[](size_type position) const    {return (vector[position]);};
        reference           front()                                 {return (*vector);};
        const_ref           front() const                           {return (*vector);};
        reference           back()                                  {return (vector[_size - 1]);};
        const_ref           back() const                            {return (vector[_size - 1]);};
        pointer             data()                                  {return (vector);};
        const_pointer       data() const                            {return (vector);};

        reference at(size_type position)
        {
            if (position < _size || position >= _size)
                throw std::out_of_range("Vector: out of range for AT.");
            return (vector[position]);
        }
        const_ref at(size_type position) const
        {
            if (position < _size || position >= _size)
                throw std::out_of_range("Vector: out of range for AT.");
            return (vector[position]);
        }

        /*============================ MODIFIERS =============================*/
        void assign(size_type nb, const_ref value)
        {
            if (nb < 0)
                throw std::out_of_range("Vector: out of range.");
            this->clear();
            this->reserve(nb);
            for (size_type i = 0; i < _size; i++)
                vector[i] = value;
        }

        template<class OtherIter>
        typename ft::enable_if<!ft::is_integral<OtherIter>::value, void>::type
        assign(OtherIter first, OtherIter last)
        {
            int range = last - first;
            if (range < 0)
                throw std::length_error("Vector: out of range for ASSIGN.");
            this->clear();
            this->reserve(range);
            for (; first != last; ++first)
                this->push_back(*first);
        }

    };
}

#endif