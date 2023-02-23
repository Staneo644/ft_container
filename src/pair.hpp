
namespace ft{
    template <class T1, class T2> struct pair{
        
		typedef T1 first_type;
		typedef T2 second_type;

		////////////////////////CONSTRUCTOR////////////////

		first_type first;
		second_type second;

		pair() : first(first_type()), second(second_type()){
			// first() = default;
			// second() = default;
		}

		template<class U, class V> pair (const pair<U,V>& pr) : first(pr.first), second(pr.second){
			//pair<U,V>(pr.first, pr.second);
		}


		pair (const first_type& a, const second_type& b) : first(a), second(b) {
			//second = b;
		}

		/////////////////////////

		pair& operator= (const pair& pr){
			if (std::is_copy_assignable<T1>::value && std::is_copy_assignable<T2>::value){
				first = pr.first;
				second = pr.second;
			}
			return *this;
		}
    };

	template< class T1, class T2 >
	ft::pair<T1, T2> make_pair( T1 t, T2 u ){
		return (ft::pair<T1, T2>(t, u));	
	}

	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first == rhs.first && lhs.second == rhs.second; }

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs == rhs); }

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second); }

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(rhs < lhs); }

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return rhs < lhs; }

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs < rhs); }
}