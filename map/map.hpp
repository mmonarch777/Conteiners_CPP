#ifndef MAP_HPP
# define MAP_HPP
# include <iostream>
# include "../other_tools/pair.hpp"
# include "../other_tools/red_black_tree.hpp"
# include "../iterators/node_iterator.hpp"
# include "../iterators/reverse_iterator.hpp"

namespace ft
{
    template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
    class map
    {
    public:
        typedef Key                 key_type;
    };
}

#endif