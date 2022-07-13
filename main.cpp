#include "./iterators//iterators_traits.hpp"
#include "./iterators/reverse_iterator.hpp"
//#include <vector>
#include "./vector/vector.hpp"
#include <iostream>

int main()
{
//    std::vector<int> first(5, 1);
    ft::Vector<int> first(5, 1);
    int num;
    for (int i = 0; i < (int)first.size(); i++)
        first[i] = i + 1;
    for (int i = 0; i < (int)first.size(); i++)
        std::cout << first[i] << " ";
    std::cout << std::endl;
    num = (int)first.size();
    std::cout << num << std::endl;
    std::cout << std::endl;
    std::cout << "=========================" << std::endl;
    typedef ft::Vector<int>::iterator ter;
    ter from(first.begin());
    ter until(first.end());
    ter ran(first.begin());
    ft::reverse_iterator<ter> rev_until(from);
    ft::reverse_iterator<ter> rev_ran(ran);
    from += 3;
    ft::reverse_iterator<ter> rev_from(until);
    ft::reverse_iterator<ter> randonm(from);
    std::cout << *rev_from << " " << *rev_until << " " << *rev_ran << " " << *randonm << std::endl;
    *rev_ran += *rev_from;
//    *rev_ran = *rev_ran - 6;
    std::cout << "revers random: " << *rev_ran << std::endl;
//    for (int i = 0; rev_from[i] != rev_until[0]; i++)
//    {
//        std::cout << rev_from[i] << " ";
//    }
//    std::cout << std::endl;
//    std::cout << "=========================" << std::endl;
//    while (rev_from != rev_until)
//        std::cout << *rev_from++ << " ";
//
//    std::cout << std::endl;
//    std::cout << "=========================" << std::endl;
}
