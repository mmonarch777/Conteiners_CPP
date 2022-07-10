#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <iostream>
# include <memory>
# include "vector_iterator.hpp"
# include "../other_tools/reverse_iterator.hpp"
# include "../other_tools/lexicographical_compare.hpp"
# include "../other_tools/equal.hpp"

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
        typedef ft::vector_iterator<pointer>            iterator;
        typedef ft::vector_iterator<const_pointer>      const_iter;
        typedef ft::reverse_iterator<iterator>          reverse_iter;
        typedef ft::reverse_iterator<const_iter>        const_reverse_iter;
        typedef std::ptrdiff_t                          difference_type;
        typedef std::size_t                             size_type;

    private:
        pointer     array;
        size_type   _capacity;
        size_type   _size;
        alloc_type  allocator;

    public:
        /*============================================================================================*/
        /*===================================== MEMBER FUNCTIONS =====================================*/
        /*============================================================================================*/

        explicit Vector(const Allocator& alloc = Allocator()) : array(0), _capacity(0), _size(0), allocator(alloc) {};
        Vector(size_type nb, const_ref value = value_type(), const Allocator &alloc = Allocator())
        {
            if (nb < 0)
                throw std::out_of_range("Vector: out of range.");
            allocator = alloc;
            _capacity = nb;
            _size = nb;
            array = allocator.allocate(_capacity);
            for (size_t i = 0; i < nb; i++)
                array[i] = value;
        }

        template <class OtherIter>
        Vector(OtherIter first, OtherIter last, const Allocator &alloc = Allocator(),
               typename ft::enable_if<!ft::is_integral<OtherIter>::value, void>::type* = 0)
               : _capacity(0), _size(0), allocator(alloc)
        {
            array = allocator.allocate(_capacity);
            this->assign(first, last);
        }
        Vector(const Vector &other) :array(0), _capacity(other._capacity), _size(other._size), allocator(other.allocator)
        {
            array = allocator.allocator(other._capacity);
            for (size_t i = 0; i < _size; i++)
                array[i] = other.array[i];
        }
        ~Vector()
        {
            this->clear();
            allocator.deallocate(array, _capacity);
        }
        Vector &operator=(const Vector &other)
        {
            if (this != &other)
            {
                this->clear();
                allocator.deallocate(array, _capacity);
                _capacity = other._capacity;
                _size = other._size;
                array = allocator.allocate(_capacity);
                for (size_t i = 0; i < _size; i++)
                    array[i] = other.array[i];
            }
            return *this;
        }

        /*============================================================================================*/
        /*======================================== ITERATORS =========================================*/
        /*============================================================================================*/

        iterator            begin()                                 {return (iterator(array));};
        const_iter          begin() const                           {return (const_iter(array));};
        iterator            end()                                   {return (iterator(array + _size));};
        const_iter          end() const                             {return (const_iter(array + _size));};
        reverse_iter        rbegin()                                {return (reverse_iter(array + _size - 1));};
        const_reverse_iter  rbegin() const                          {return (const_reverse_iter(array + _size + 1));};
        reverse_iter        rend()                                  {return (reverse_iter(array - 1));};
        const_reverse_iter  rend() const                            {return (const_reverse_iter(array - 1));};

        /*============================================================================================*/
        /*========================================= CAPACITY ==========================================*/
        /*============================================================================================*/

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
                {
                    allocator.construct(buf + i, array[i]);
                    allocator.destroy(array + i);
                }
                if (array)
                    allocator.deallocate(array, _capacity);
                _capacity = count;
                array = buf;
            }
        }
        /*============================================================================================*/
        /*====================================== ELEMENT ACCESS =======================================*/
        /*============================================================================================*/

        reference           operator[](size_type position)          {return (array[position]);};
        const_ref           operator[](size_type position) const    {return (array[position]);};
        reference           front()                                 {return (*array);};
        const_ref           front() const                           {return (*array);};
        reference           back()                                  {return (array[_size - 1]);};
        const_ref           back() const                            {return (array[_size - 1]);};
        pointer             data()                                  {return (array);};
        const_pointer       data() const                            {return (array);};

        reference at(size_type position)
        {
            if (position < _size || position >= _size)
                throw std::out_of_range("Vector: out of range for AT.");
            return (array[position]);
        }
        const_ref at(size_type position) const
        {
            if (position < _size || position >= _size)
                throw std::out_of_range("Vector: out of range for AT.");
            return (array[position]);
        }

        /*============================================================================================*/
        /*======================================== MODIFIERS =========================================*/
        /*============================================================================================*/

        void assign(size_type nb, const_ref value)
        {
            if (nb < 0)
                throw std::out_of_range("Vector: out of range.");
            this->clear();
            this->reserve(nb);
            for (size_type i = 0; i < _size; i++)
                array[i] = value;
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
        void clear()
        {
            for (size_type i = 0; i < _size; i++)
                allocator.destroy(array + i);
            _size = 0;
        }
        void insert(iterator position, size_type count, const_ref val)
        {
            difference_type id = position - begin();
            if (count == 0)
                return;
            while (_size != (_size + count))
            {
                if (_size == _capacity && _capacity)
                    reserve(_capacity * 2);
                else
                    reserve(1);
                _size++;
            }
            for (size_type i = _size; i > (size_type)id; i--)
                array[i + count - 1] = array[i - 1];
            for (size_type i = 0; i < count; i++)
                allocator.construct(array + id + i, val);
            _size = _size + count;
        }

        iterator insert(iterator position, const_ref val)
        {
            size_type id = position - begin();
            this->insert(position, 1, val);
            return iterator(array + id);
        }

        template <class OtherIter>
        void insert(iterator position, OtherIter first, OtherIter last,
                    typename ft::enable_if< !ft::is_integral<OtherIter>::value, OtherIter>::type* = 0)
        {
            if (first == last)
                return;
            size_type id = static_cast<size_type>(position - this->begin());
            size_type count = static_cast<size_type>(last - first);
            while (_size != (_size + count))
            {
                if (_size == _capacity && _capacity)
                    reserve(_capacity * 2);
                else
                    reserve(1);
                _size++;
            }
            for (size_type i = _size; i > (size_type)id; i--)
                array[i + count - 1] = array[i - 1];
            for (size_type i = 0; i < count; i++, ++first)
                allocator.construct(array + id + i, *first);
            _size = _size + count;
        }

        iterator erase(iterator position)
        {
            size_type id = static_cast<size_type>(position - this->begin());
            allocator.destroy(array + id);
            for (size_type i = id; i < _size - 1; i++)
                array[i] = array[i + 1];
            --_size;
            return position;
        }
        iterator erase(iterator first, iterator last)
        {
            size_type id = static_cast<size_type>(first - this->begin());
            if (first == last)
                return iterator(array + id);
            size_type count = static_cast<size_type>(last - first);
            for (iterator i = first; i != last; i++)
                allocator.destroy(array + i);
            for (size_type i = id; i < (_size - count); i++)
                array[i] = array[i + count];
            _size = _size - count;
            return first;
        }

        void push_back(const_ref value)
        {
            while (_size != (_size + 1))
            {
                if (_size == _capacity && _capacity)
                    reserve(_capacity * 2);
                else
                    reserve(1);
                _size++;
            }
            allocator.constructor(array + _size, value);
        }

        void pop_back()
        {
            if (_size == 0)
                return;
            allocator.destroy(array + (_size - 1));
            --_size;
        }

        void resize(size_type count, value_type value = value_type())
        {
            if ( count < _size)
            {
                while(_size > count)
                    pop_back();
            }
            else if (count > _size)
            {
                while(_size < count)
                    push_back(value);
            }
        }

        void swap(Vector &other)
        {
            std::swap(_size, other._size);
            std::swap(_capacity, other._capacity);
            std::swap(array, other.array);
            std::swap(allocator, other.allocator);
        }

        /*============================================================================================*/
        /*======================================== ALLOCATOR =========================================*/
        /*============================================================================================*/
        alloc_type get_allocator() const
        {
            return (this->allocator);
        }

    };
    /*============================================================================================*/
    /*================================= NON-MEMBER FUNCTIONS =====================================*/
    /*============================================================================================*/

    template<class T, class A>
    bool operator==(const ft::Vector<T, A>& _first, const ft::Vector<T, A>& _second)
    {
        return _first.size() == _second.size() && ft::equal(_first.begin(), _first.end(), _second.begin());
    }

    template<class T, class A>
    bool operator!=(const ft::Vector<T, A>& _first, const ft::Vector<T, A>& _second)
    {
        return !(_first == _second);
    }

    template<class T, class A>
    bool operator<(const ft::Vector<T, A>& _first, const ft::Vector<T, A>& _second)
    {
        return ft::lexicographical_compare(_first.begin(), _first.end(), _second.begin(), _second.end());
    }

    template<class T, class A>
    bool operator>(const ft::Vector<T, A>& _first, const ft::Vector<T, A>& _second)
    {
        return _second < _first;
    }

    template<class T, class A>
    bool operator<=(const ft::Vector<T, A>& _first, const ft::Vector<T, A>& _second)
    {
        return !(_second < _first);
    }

    template<class T, class A>
    bool operator>=(const ft::Vector<T, A>& _first, const ft::Vector<T, A>& _second)
    {
        return !(_first < _second);
    }

    template<class T, class A>
    void swap(ft::Vector<T, A>& _first, ft::Vector<T, A>& _second)
    {
        _first.swap(_second);
    }
}

#endif
