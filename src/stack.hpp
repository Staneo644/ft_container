#ifndef STACK_HPP
# define STACK_HPP
# include <iostream>
# include <cstddef>
# include <array>
# include <memory>
# include <string>
# include "vector.hpp"

namespace ft {
    template< class T, class Container = ft::vector<T> > 
    class stack {
        public:
            typedef T value_type;
            typedef Container container_type;	
            typedef typename Container::size_type size_type;
            typedef typename Container::reference reference;
            typedef typename Container::const_reference const_reference;

        protected:
            container_type c;

        public:

            size_type size() const{
                return c.size();
            }

            explicit stack (const container_type& ctnr = container_type()){
                c = ctnr;
        
            }

            bool empty() const{
                return c.empty();
            }

            value_type& top(){
                return c.back();
            }
            
            const value_type& top() const{
                return c.back();
            }

            void push (const value_type& val){
                c.push_back(val);
            }

            void pop(){
                c.pop_back();
            }

            template <class T1, class _C1> 
            friend bool operator==(const stack<T1, _C1>& __x, const stack<T1, _C1>& __y);

            template <class T1, class _C1>
            friend bool operator< (const stack<T1, _C1>& __x, const stack<T1, _C1>& __y);
    };

    template< class T, class Container >
    bool operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ){
        return (lhs.c == rhs.c);

    }
       	
    template< class T, class Container >
    bool operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ){
        return (!(lhs == rhs));
    }
        	
    template< class T, class Container >
    bool operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ){
        return (lhs.c < rhs.c);
    }
        	
    template< class T, class Container >
    bool operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ){
        return (lhs < rhs || lhs == rhs);
    }
      	
    template< class T, class Container >
    bool operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ){
        return (!(lhs <= rhs));
    }
      	
    template< class T, class Container >
    bool operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ){
        return (lhs > rhs || lhs == rhs);
    }
        
}

#endif