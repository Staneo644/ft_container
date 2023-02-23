#ifndef MAIN_HPP
# define MAIN_HPP

# include <iostream>
# include <string>
# include <deque>

# if 0
	# include <map>
	# include <stack>
	# include <vector>
	namespace ft = std;
# else
	# include "map.hpp"
	# include "stack.hpp"
	# include "vector.hpp"
# endif

typedef int key;
typedef int value;

enum Container {_vector, _map, _stack};

void    checkVector();
void	checkMap();
void	checkStack();
void    checkReverseIt();

template< class iterator >
void print(iterator first, iterator last, std::string str){
    std::cout << "Map :" << std::endl << str << " : ";
    while (first != last){
        std::cout << first->first << " - " << first->second << ",  ";
        first++;
    }
    std::cout << std::endl << std::endl;
}

template< class iterator >
void print(iterator first, iterator last, std::string str, Container type){
    (void) type;
    std::cout << "Vector : " << std::endl << str << " : ";
    while (first != last){
        std::cout << *first << "  ";
        first++;
    }
    std::cout << std::endl << std::endl;
}

template< class iterator >
void printOneValue(iterator a, std::string str){
    std::cout << "Map : " << std::endl << str << " : ";
    std::cout << a->first << " - " << a->second << ",   ";
    std::cout << std::endl << std::endl;
}

#endif
