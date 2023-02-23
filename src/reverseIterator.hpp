#ifndef REVERSEITERATOR_HPP
# define REVERSEITERATOR_HPP


# include <cstddef>
# include <array>
# include <memory>
# include <iostream>
# include <string>
# include <iterator>

# include "iterator_traits.hpp"

namespace ft {

	template< class Iter >
	class reverse_iterator 
	{
		public:
			typedef Iter iterator_type;

			typedef typename ft::iterator_traits<Iter>::value_type 			value_type;
			typedef typename ft::iterator_traits<Iter>::iterator_category 	iterator_category;
		 	typedef typename ft::iterator_traits<Iter>::difference_type 	difference_type;
			typedef typename ft::iterator_traits<Iter>::pointer 			pointer;
			typedef typename ft::iterator_traits<Iter>::reference 			reference;
		

		protected :
			Iter current;

		public:

			reverse_iterator() : current(){
			}

			explicit reverse_iterator( iterator_type x ) : current(x) {
			}

			template< class U >
			reverse_iterator( const reverse_iterator<U>& other ) : current(other.base()){
			}

			template< class U > reverse_iterator& operator=( const reverse_iterator<U>& other ){
				current = other.base(); return *this;
			}

			reference operator*() const{
				//return *(--base());
				Iter tmp = current; tmp--; return *tmp;
			}

			pointer operator->() const {
				Iter tmp = current; tmp--;
				return (&(*tmp));
				//return &(operator*());
			}

			reverse_iterator operator++(int){
				reverse_iterator __tmp(*this); --current; return __tmp;
			}

			reverse_iterator operator--(int){
				reverse_iterator __tmp(*this); ++current; return __tmp;
			}

			reverse_iterator& operator++(){
				current--;
				return *this;
			}

			reverse_iterator& operator--(){
				current++;
				return *this;
			}

			reverse_iterator& operator-=( difference_type n ){
				current += n; return *this;
			}

			reverse_iterator& operator+=( difference_type n ){
				current -= n; return *this;
			}

			reverse_iterator operator-( difference_type n ) const{
				return reverse_iterator(current + n);
			}

			reverse_iterator operator+( difference_type n ) const{
				return reverse_iterator(current - n);
			}

			iterator_type base() const{
				return current;
			}

			reference operator[]( difference_type n ) const{
				return ((base()[-n - 1]));
			}


			//reverse_iterator end()   { return reverse_iterator(&m_data[0]); }


	};

	template< class Iterator1, class Iterator2 >
	bool operator==( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs ){
					 return lhs.base() == rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator!=( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs ){
					 return lhs.base() != rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator<( const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs ){
					return lhs.base() > rhs.base();
	}


	template< class Iterator1, class Iterator2 >
	bool operator<=( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs ){
					 return lhs.base() >= rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator>( const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs ){
					return lhs.base() < rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator>=( const ft::reverse_iterator<Iterator1>& lhs,
                 const ft::reverse_iterator<Iterator2>& rhs ){
					 return lhs.base() <= rhs.base();
	}

	template< class Iter >
	reverse_iterator<Iter> operator+( typename reverse_iterator<Iter>::difference_type n, 
		const reverse_iterator<Iter>& it ){
			return reverse_iterator<Iter>(it.base() - n);
		}

	template< class Iterator1, class Iterator2 >
	typename reverse_iterator<Iterator1>::difference_type
    operator-( const reverse_iterator<Iterator1>& lhs,
               const reverse_iterator<Iterator2>& rhs ){
			return (rhs.base() - lhs.base());
		}
}

#endif