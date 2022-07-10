#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <iostream>
# include <memory>
# include "vector_iterator.hpp"
# include "../other_tools/reverse_iterator.hpp"
# include "../other_tools/lexicographical_compare.hpp"
# include "../other_tools/equal.hpp"
# include "../other_tools/enable_integral.hpp"

namespace ft
{
    template<class T, class Allocator = std::allocator<T> >
    class Vector {
    public:

        typedef T											value_type;
        typedef Allocator									alloc_type;
        typedef typename alloc_type::reference				reference;
        typedef typename alloc_type::const_reference		const_ref;
        typedef typename alloc_type::size_type				size_type;
        typedef typename alloc_type::difference_type		difference_type;
        typedef typename alloc_type::pointer				pointer;
        typedef typename alloc_type::const_pointer			const_pointer;
        typedef ft::vector_iterator<value_type>				iterator;
        typedef ft::vector_iterator<const value_type>		const_iter;
        typedef ft::reverse_iterator<iterator>				reverse_iter;
        typedef ft::reverse_iterator<const_iter>			const_reverse_iter;

    private:
        pointer			array;
        size_type 		_size;
        size_type 		_capacity;
        alloc_type	allocator;
    public:

        /*============================================================================================*/
        /*===================================== MEMBER FUNCTIONS =====================================*/
        /*============================================================================================*/

        Vector() : array(0), _size(0), _capacity(0), allocator(alloc_type()) {}
        explicit Vector(const alloc_type& alloc) : array(0), _size(0), _capacity(0), allocator(alloc) {}

        explicit Vector(size_type n, const value_type& value = value_type(),
                        const alloc_type& alloc = alloc_type()) : array(0), _size(0), _capacity(0), allocator(alloc) {
            if (n >= 0) {
                reserve(n);
                for (size_t i = 0; i < n; ++i) {
                    allocator.construct(array + i, value);
                }
                this->_size = n;
            }
        }

        template<class InputIter>
        Vector(InputIter first, InputIter last,
               const alloc_type& alloc = alloc_type(),
               typename ft::enable_if<!ft::is_integral<InputIter>::value, InputIter>::type* = 0)
               : array(0), _size(0), _capacity(0), allocator(alloc)
        {
            clear();
            reserve(std::distance(first, last));
            for (InputIter it = first; it != last; ++it)
            {
                allocator.construct(array + _size, *it);
                ++_size;
            }
        }

        Vector(const Vector& other) : array(0), _size(0), _capacity(0), allocator(other.allocator)
        {
            clear();
            reserve(other._capacity);
            for (size_t i = 0; i < other._size; ++i)
                this->allocator.construct(this->array + i, other.array[i]);
            this->_size = other._size;
        }

        virtual ~Vector(void)
        {
            clear();
            if (_capacity)
                allocator.deallocate(array, _capacity);
        }

        Vector& operator=(const Vector& other)
        {
            if (this != &other)
            {
                clear();
                this->allocator.deallocate(array, _capacity);
                this->_size = other.size();
                this->_capacity = other.capacity();
                this->array = allocator.allocate(_capacity);
                for (size_t i = 0; i < other._size; ++i)
                    this->allocator.construct(this->array + i, other.array[i]);
            }
            return *this;
        }

        /*============================================================================================*/
        /*======================================== ITERATORS =========================================*/
        /*============================================================================================*/

        iterator            begin()         {return iterator(array);}
        const_iter          begin() const   {return const_iter(array);}
        iterator            end()           {return iterator(array + _size);}
        const_iter          end() const     {return const_iter(array + _size);}
        reverse_iter        rbegin()        {return reverse_iter(end());}
        const_reverse_iter  rbegin() const  {return const_reverse_iter(end());}
        reverse_iter        rend()          {return reverse_iter(begin());}
        const_reverse_iter  rend() const    {return const_reverse_iter(begin());}

        /*============================================================================================*/
        /*======================================== CAPACITY ==========================================*/
        /*============================================================================================*/

        size_type   size() const            {return _size;}
        size_type   max_size() const        {return allocator.max_size();}
        size_type   capacity() const        {return _capacity;}
        bool        empty() const           {return size() == 0;}

        void reserve(size_type n)
        {
            if (n > _capacity)
            {
                pointer newArr = allocator.allocate(n);
                for (size_t i = 0; i < _size; ++i)
                {
                    allocator.construct(newArr + i, array[i]);
                    allocator.destroy(array + i);
                }
                allocator.deallocate(array, _capacity);
                this->array = newArr;
                this->_capacity = n;
            }
        }

        void resize(size_type count, value_type value = value_type()) {
            if (count < _size)
            {
                while (_size > count)
                    pop_back();
            } else if (count > _size)
            {
                while (_size < count)
                    push_back(value);
            }
        }

        /*============================================================================================*/
        /*====================================== ELEMENT ACCESS ======================================*/
        /*============================================================================================*/

        reference       operator[](size_type pos)       {return *(array + pos);}
        const_ref       operator[](size_type pos) const {return *(array + pos);}
        reference       front()                         {return *array;}
        const_ref       front() const                   {return *array;}
        reference       back()                          {return *(array + (_size - 1));}
        const_ref       back() const                    {return *(array + (_size - 1));}
        pointer         data()                          {return array;}
        const_pointer   data() const                    {return array;}

        reference at(size_type pos)
        {
            if (pos >= _size)
                throw std::out_of_range("Out of range");
            return *(array + pos);
        }

        const_ref at(size_type pos) const
        {
            if (pos >= _size)
                throw std::out_of_range("Out of range");
            return *(array + pos);
        }

        /*============================================================================================*/
        /*======================================== MODIFIERS =========================================*/
        /*============================================================================================*/

        void assign(size_type count, const value_type& value)
        {
            if (count > 0) {
                clear();
                reserve(count);
                for (size_t i = 0; i < count; ++i)
                    push_back(value);
            }
        }

        template<class inputIt>
        void assign(inputIt first, inputIt last,
                    typename ft::enable_if<!ft::is_integral<inputIt>::value, inputIt>::type* = 0) {
            clear();
            reserve(std::distance(first, last));
            for (; first != last; ++first) {
                push_back(*first);
            }
        }

        void clear(void) {
            if (array)
            {
                for (size_t i = 0; i < _size; ++i) {
                    allocator.destroy(array + i);
                }
            }
            _size = 0;
        }

        iterator insert(iterator pos, const value_type& value)
        {
            difference_type start = std::distance(this->begin(), pos);
            size_type i = 0;
            if (_capacity == _size && _capacity)
                reserve(2 * _capacity);
            else
                reserve(1);
            for (i = _size; i > static_cast<size_type>(start); --i)
                array[i] = array[i - 1];
            allocator.construct(array + i, value);
            ++_size;
            return iterator(array + start);
        }

        void insert(iterator pos, size_type count, const value_type& value)
        {
            difference_type start = std::distance(this->begin(), pos);
            if (count == 0)
                return;
            if (_size + count > _capacity)
            {
                if (count > _size)
                    reserve(_size + count);
                else
                    reserve(2 * _capacity);
            }
            for (size_type i = _size; i > static_cast<size_type>(start); --i)
                array[i + count - 1] = array[i - 1];
            for (size_type i = 0; i < count; ++i)
                allocator.construct(array + start + i, value);
            _size += count;
        }

        template<class InputIter>
        void insert(iterator pos, InputIter first, InputIter last,
                    typename ft::enable_if< !ft::is_integral< InputIter >::value, InputIter >::type* = 0)
        {
            if (first == last)
                return;
            difference_type start = std::distance(this->begin(), pos);
            difference_type count = std::distance(first, last);
            if (!valid_iterator(first, last, count))
                throw std::exception();
            if (_size + static_cast<size_type>(count) > _capacity)
            {
                if (static_cast<size_type>(count) > _size)
                    reserve(_size + static_cast<size_type>(count));
                else
                    reserve(2 * _capacity);
            }
            size_type i = 0;
            for (i = _size; i > static_cast<size_type>(start); --i)
                array[i + static_cast<size_type>(count) - 1] = array[i - 1];
            for (i = 0; i < static_cast<size_type>(count); ++i, ++first)
                allocator.construct(array + start + i, *first);
            _size += count;
        }

        iterator erase(iterator pos) {
            difference_type start = std::distance(this->begin(), pos);
            allocator.destroy(array + start);
            for (size_type i = static_cast<size_type>(start); i < _size - 1; ++i) {
                array[i] = array[i + 1];
            }
            --_size;
            return pos;
        }

        iterator erase(iterator first, iterator last) {
            difference_type start = std::distance(this->begin(), first);
            if (first == last) {
                return iterator(array + start);
            }
            difference_type count = std::distance(first, last);
            for (iterator it = first; it != last; ++it) {
                allocator.destroy(&(*it));
            }
            for (size_type i = static_cast<size_type>(start); i < _size - count; ++i) {
                array[i] = array[i + count];
            }
            _size -= count;
            return first;
        }

        void push_back(const T& value) {
            if (_capacity == _size && _capacity) {
                reserve(2 * _size);
            } else {
                reserve(1);
            }
            allocator.construct(array + _size, value);
            ++_size;
        }

        void pop_back() {
            if (!_size) {
                return;
            }
            allocator.destroy(array + (_size - 1));
            --_size;
        }

        void swap(Vector& other) {
            std::swap(array, other.array);
            std::swap(_size, other._size);
            std::swap(_capacity, other._capacity);
            std::swap(allocator, other.allocator);
        }

        /*============================================================================================*/
        /*======================================== ALLOCATOR =========================================*/
        /*============================================================================================*/

        alloc_type get_allocator(void) const {
            return this->allocator;
        }

    private:

        template<class InputIt>
        typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type
        valid_iterator(InputIt first, InputIt last, size_t range) {
            pointer reserved_buffer;
            reserved_buffer = allocator.allocate(range);
            bool result = true;
            size_t i = 0;

            for (;first != last; ++first, ++i) {
                try { reserved_buffer[i] = *first; }
                catch (...) { result = false; break; }
            }
            allocator.deallocate(reserved_buffer, range);
            return result;
        }
    };

    /*============================================================================================*/
    /*================================== NON-MEMBER FUNCTIONS ====================================*/
    /*============================================================================================*/


    template<class T, class Al>
    bool operator==(const ft::Vector<T, Al>& _first, const ft::Vector<T, Al>& _second)
    {
        return _first.size() == _second.size() && ft::equal(_first.begin(), _first.end(), _second.begin());
    }
    template<class T, class Al>
    bool operator!=(const ft::Vector<T, Al>& _first, const ft::Vector<T, Al>& _second)
    {
        return !(_first == _second);
    }
    template<class T, class Al>
    bool operator<(const ft::Vector<T, Al>& _first, const ft::Vector<T, Al>& _second)
    {
        return ft::lexicographical_compare(_first.begin(), _first.end(), _second.begin(), _second.end());
    }
    template<class T, class Al>
    bool operator<=(const ft::Vector<T, Al>& _first, const ft::Vector<T, Al>& _second)
    {
        return !(_second < _first);
    }
    template<class T, class Al>
    bool operator>(const ft::Vector<T, Al>& _first, const ft::Vector<T, Al>& _second)
    {
        return _second < _first;
    }
    template<class T, class Al>
    bool operator>=(const ft::Vector<T, Al>& _first, const ft::Vector<T, Al>& _second)
    {
        return !(_first < _second);
    }
    template<class T, class Al>
    void swap(ft::Vector<T, Al>& _first, ft::Vector<T, Al>& _second)
    {
        _first.swap(_second);
    }
}

#endif
