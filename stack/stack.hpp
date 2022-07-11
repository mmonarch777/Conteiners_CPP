#ifndef STACK_HPP
# define STACK_HPP
# include "../vector/vector.hpp"

namespace ft
{
    template <class T, class Container = ft::Vector<T> >
    class Stack
    {
    public:
        typedef Container                               container_type;
        typedef typename container_type::value_type     value_type;
        typedef typename container_type::size_type      size_type;

    private:
        container_type ctnr;
    public:
        /*==================== MEMBER FUNCTIONS ====================*/
        /*============== CONSTRUCTORS AND DESTRUCTOR ===============*/
        explicit Stack(const container_type &ctnr = container_type()) : ctnr(ctnr) {}

        Stack(const Stack &other) : ctnr(other.ctnr) {}
        ~Stack() {}

        Stack &operator=(const Stack & other)
        {
            if (this != &other)
                ctnr = other.ctnr;
            return *this;
        }
        /*==================== MEMBER FUNCTIONS ====================*/

        bool            empty() const                   {return ctnr.empty();}
        size_type       size() const                    {return ctnr.size();}
        value_type&     top()                           {return ctnr.back();}
        value_type&     top() const                     {return ctnr.back();}
        void            push(const value_type &value)   {return ctnr.push_back(value);}
        void            pop()                           {return ctnr.pop_back();}

        template<class T1, class Container1>
        friend bool operator==(const ft::Stack<T1, Container1>& first, const ft::Stack<T1, Container1>& second);

        template<class T1, class Container1>
        friend bool operator!=(const ft::Stack<T1, Container1>& first, const ft::Stack<T1, Container1>& second);

        template<class T1, class Container1>
        friend bool operator<(const ft::Stack<T1, Container1>& first, const ft::Stack<T1, Container1>& second);

        template<class T1, class Container1>
        friend bool operator>(const ft::Stack<T1, Container1>& first, const ft::Stack<T1, Container1>& second);

        template<class T1, class Container1>
        friend bool operator<=(const ft::Stack<T1, Container1>& first, const ft::Stack<T1, Container1>& second);

        template<class T1, class Container1>
        friend bool operator>=(const ft::Stack<T1, Container1>& first, const ft::Stack<T1, Container1>& second);

    };
    /*==================== NON-MEMBER FUNCTIONS ====================*/

    template<class T, class Container>
    bool operator==(const ft::Stack<T, Container>& first, const ft::Stack<T, Container>& second)
    {
        return first.ctnr == second.ctnr;
    }

    template<class T, class Container>
    bool operator!=(const ft::Stack<T, Container>& first, const ft::Stack<T, Container>& second)
    {
        return first.ctnr != second.ctnr;
    }

    template<class T, class Container>
    bool operator<(const ft::Stack<T, Container>& first, const ft::Stack<T, Container>& second)
    {
        return first.ctnr < second.ctnr;
    }

    template<class T, class Container>
    bool operator>(const ft::Stack<T, Container>& first, const ft::Stack<T, Container>& second)
    {
        return first.ctnr > second.ctnr;
    }

    template<class T, class Container>
    bool operator<=(const ft::Stack<T, Container>& first, const ft::Stack<T, Container>& second)
    {
        return first.ctnr <= second.ctnr;
    }

    template<class T, class Container>
    bool operator>=(const ft::Stack<T, Container>& first, const ft::Stack<T, Container>& second)
    {
        return first.ctnr >= second.ctnr;
    }
}

#endif