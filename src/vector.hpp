#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <cstddef>
# include <array>
# include <memory>
# include <iostream>
# include <string>
# include "enable_if.hpp"
# include "reverseIterator.hpp"
# include "equal.hpp"

namespace ft {
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
        public:
			typedef Alloc allocator_type;
			typedef T value_type;
			typedef std::size_t size_type;
			typedef typename allocator_type::reference	reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef ptrdiff_t difference_type;
            typedef pointer iterator;
            typedef const_pointer const_iterator;
            typedef typename ft::reverse_iterator<iterator> reverse_iterator;
            typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;


        private:
            pointer MYTABLEAU;
            size_type SIZEOFMYTABLEAU;
            size_type CAPACITYOFMYTABLEAU;
            allocator_type myAlloc;
            bool Construct;

            void defineElement(const allocator_type& alloc){
                Construct = true;
                myAlloc = alloc;
                MYTABLEAU = NULL;
                SIZEOFMYTABLEAU = 0;
                CAPACITYOFMYTABLEAU = 0;
            }

		public:
            explicit vector (const allocator_type& alloc = allocator_type()){
                defineElement(alloc);
                clear();
                
            }

            template <class InputIterator>
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0){
                defineElement(alloc);
                assign(first, last);
           
            }

            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()){
                defineElement(alloc);
                MYTABLEAU = myAlloc.allocate(n);
                if (val != value_type()) {
                    for (size_type mem = SIZEOFMYTABLEAU; mem < n; mem++){
                        myAlloc.construct( &(MYTABLEAU[mem]), val);
                    }
                }
                else
                    Construct = false;
                CAPACITYOFMYTABLEAU = n;
                SIZEOFMYTABLEAU = n;
            }



            ~vector(){
                if (Construct)
                    clear();
                if (MYTABLEAU != NULL && CAPACITYOFMYTABLEAU){
                    myAlloc.deallocate( MYTABLEAU, CAPACITYOFMYTABLEAU);
                }
            }

            vector (const vector& x){
                defineElement(x.get_allocator());
                assign(x.begin(), x.end());
            }

            vector& operator= (const vector& x){
                defineElement(x.get_allocator());
                assign(x.begin(), x.end());
                return (*this);
            }

            //ITERATORS/////////////////////////////////////////////////////////////////////////////////////////////
            iterator begin(){
                return (MYTABLEAU);
            }

            iterator end(){
                return (MYTABLEAU + SIZEOFMYTABLEAU);
            }

            const_iterator begin() const {
                return (MYTABLEAU);
            }

            const_iterator end() const {
                return (MYTABLEAU + SIZEOFMYTABLEAU);
            }

            reverse_iterator rbegin(){
                return reverse_iterator(end());

            }

            const_reverse_iterator rbegin() const{
                return reverse_iterator(end());
            }

            reverse_iterator rend(){
                return reverse_iterator(begin());
            }

            const_reverse_iterator rend() const{
                return reverse_iterator(begin());
            }

            //CAPACITY/////////////////////////////////////////////////////////////////////////////////////////////

            void resize( size_type count, T value = T() ){
                if (count > SIZEOFMYTABLEAU){
                    if (count > CAPACITYOFMYTABLEAU){
                        reserve(((CAPACITYOFMYTABLEAU * 2) * (MYTABLEAU != NULL)) + (count * (MYTABLEAU == NULL)));
                    }
                    for (size_type mem = SIZEOFMYTABLEAU; mem < count; mem++){
                        MYTABLEAU[mem] = value;
                    }
                }

                if (count < SIZEOFMYTABLEAU){
                    while (count < SIZEOFMYTABLEAU)
                    {
                        myAlloc.destroy(&MYTABLEAU[SIZEOFMYTABLEAU]);
                        SIZEOFMYTABLEAU--;
                    }
                }
                SIZEOFMYTABLEAU = count;
            }


            size_type max_size() const
            {
                return myAlloc.max_size();
            }


			std::size_t size() const {
                return (SIZEOFMYTABLEAU);
            }
            

            bool empty () const{
                return (SIZEOFMYTABLEAU == 0);
            }

            size_type capacity() const{
                return (CAPACITYOFMYTABLEAU);
            }

            void reserve (size_type n){
                if (n > CAPACITYOFMYTABLEAU){
                    if (MYTABLEAU == NULL){
                        MYTABLEAU = myAlloc.allocate(n);
                    }
                    else {
                        value_type *myPointer = myAlloc.allocate(n);
                        for (size_type i = 0; i < SIZEOFMYTABLEAU; i++){
                            myPointer[i] = MYTABLEAU[i];
                        }

                        for (size_type temp = 0; temp < SIZEOFMYTABLEAU; temp++){
                            myAlloc.destroy(&MYTABLEAU[temp]);
                        }
                        myAlloc.deallocate(MYTABLEAU, CAPACITYOFMYTABLEAU);
                        MYTABLEAU = myPointer;
                    }
                    CAPACITYOFMYTABLEAU = n;
                }
            }

            //ELEMENT ACCESS/////////////////////////////////////////////////////////////

            reference operator[] (size_type n){
                return MYTABLEAU[n];
            }

            const_reference operator[] (size_type n) const{
                return MYTABLEAU[n];
            }

            reference at (size_type n){
                if (n < 0 || n >= SIZEOFMYTABLEAU)
                    throw std::out_of_range("invalid number");
                return((*this)[n]);

            }

            const_reference at (size_type n) const{
                if (n < 0 || n >= SIZEOFMYTABLEAU)
                    throw std::out_of_range("invalid number");
                return((*this)[n]);
            }

            reference front(){
                return MYTABLEAU[0];
            }

            const_reference front() const{
                return MYTABLEAU[0];
            }

            reference back(){
                return MYTABLEAU[SIZEOFMYTABLEAU - 1];
            }

            const_reference back() const{
                return MYTABLEAU[SIZEOFMYTABLEAU - 1];
            }

            value_type* data()  {
                return MYTABLEAU;
            }

            const value_type* data() const {
                return MYTABLEAU;
            }

            //MODIFIERS//////////////////////////////////////////////////////////////////


            template <class InputIterator>
            void assign (InputIterator first, InputIterator last,typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0 ){
                clear();
                while (first != last){
                    push_back(*first);
                    first++;
                }
            }


            void assign (size_type n, const value_type& val){
                clear();
                resize(n, val);
            }

            void push_back (const value_type& val){
                resize(SIZEOFMYTABLEAU + 1, val);
            }

            void pop_back(){
                resize(SIZEOFMYTABLEAU - 1);
            }



            iterator erase (iterator position){
                iterator ret = position;
                if (position == end())
                    return end();
                myAlloc.destroy(position);
                if (position + 1 == end()){
                    pop_back();
                    return end();
                }
                for (; position != (end() - 1); position ++){
                    *position = *(position + 1);
                }
                pop_back();
                return ret;
            }

            iterator erase (iterator first, iterator last){
                if (first == last)
                    return (first);
                last--;

                while (first != last){
                    erase(last);
                    last--;
                }
                erase(last);
                return (first);
            }

            void print (){
                std::cout << SIZEOFMYTABLEAU << std::endl;
                for (iterator x = begin();x != end(); x++) {
                    std::cout << x[0] << std::endl;
                }
                
            }

            value_type *newAllocate (size_type n){
                value_type *myPointer;
                if ((SIZEOFMYTABLEAU + n) > (SIZEOFMYTABLEAU * 2)){
                    myPointer = myAlloc.allocate((SIZEOFMYTABLEAU + n));
                    CAPACITYOFMYTABLEAU = SIZEOFMYTABLEAU + n;
                }
                else{
                    myPointer = myAlloc.allocate((SIZEOFMYTABLEAU * 2));
                    CAPACITYOFMYTABLEAU = SIZEOFMYTABLEAU * 2;
                }
                return (myPointer);
            }

            void newDestroy (size_type Oldcap){
                for (size_type temp = 0; temp < SIZEOFMYTABLEAU; temp++) {
                    myAlloc.destroy(&MYTABLEAU[temp]);
                }
                myAlloc.deallocate(MYTABLEAU, Oldcap);
            }

            iterator insert (iterator position, const value_type& val){
                iterator difference = (end());
                if (begin() == end()){
                    push_back(val);
                    return(begin());
                }
                
                if (position == end()){
                    push_back(val);
                    return (end() - 1);
                }

                if (1 + SIZEOFMYTABLEAU > CAPACITYOFMYTABLEAU){
                    size_type i = 0;
                    size_type Oldcap = CAPACITYOFMYTABLEAU;
                    value_type *myPointer = newAllocate(1);

                    for (; &(MYTABLEAU[i]) != position; i++) {
                        myPointer[i] = MYTABLEAU[i];
                    }
                    myPointer[i] = val;
                    while (&(MYTABLEAU[i]) != end()) {
                        myPointer[i + 1] = MYTABLEAU[i];
                        i++;
                    }

                    newDestroy(Oldcap);
                    SIZEOFMYTABLEAU += 1;
                    MYTABLEAU = myPointer;
                }

                else {
                    resize(SIZEOFMYTABLEAU + 1);
                    for (; difference != position; difference --){
                        *(difference) = *(difference - 1);
                    }
                    *(difference) = val;
                }
                return position;
            }



            void insert (iterator position, size_type n, const value_type& val){

                if (n + SIZEOFMYTABLEAU > CAPACITYOFMYTABLEAU){
                    size_type i = 0;
                    size_type Oldcap = CAPACITYOFMYTABLEAU;
                    value_type *myPointer = newAllocate(n);
                    

                    for (; &(MYTABLEAU[i]) != position; i++){
                        myPointer[i] = MYTABLEAU[i];
                    }
                    size_type j = i;
                    while (n > 0)
                    {
                        myPointer[i] = val;
                        i++;
                        n--;
                    }
                    while (&(MYTABLEAU[j]) != end())
                    {
                        myPointer[i] = MYTABLEAU[j];
                        i++;
                        j++;
                    }

                    newDestroy(Oldcap);
                    SIZEOFMYTABLEAU = i;
                    MYTABLEAU = myPointer;
                }
                else {
                    while (n > 0)
                    {
                        insert(position, val);
                        n--;
                    }
                }
                
            }


            template <class InputIterator>
            void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0){
                size_type x = std::distance(first, last);
                if (x + SIZEOFMYTABLEAU > CAPACITYOFMYTABLEAU){
                    size_type i = 0;
                    size_type Oldcap = CAPACITYOFMYTABLEAU;
                    value_type *myPointer = newAllocate(x);
                    
                    for (; &(MYTABLEAU[i]) != position; i++){
                        myPointer[i] = MYTABLEAU[i];
                    }
                    size_type j = i;
                    while (first != last){
                        myPointer[i] = *first;
                        i++;
                        first++;
                    }
                    while (&(MYTABLEAU[j]) != end()){
                        myPointer[i] = MYTABLEAU[j];
                        i++;
                        j++;
                    }

                    newDestroy(Oldcap);
                    MYTABLEAU = myPointer;
                    SIZEOFMYTABLEAU = i;
                }

                else {
                    while (first != last)
                    {
                        insert(position, *first);
                        position++;
                        first++;
                    }
                }
            }

            void clear(){
                erase(begin(), end());
            }

            void swap (vector& x){
                value_type* tempTab = MYTABLEAU;
                size_type tempSiz = SIZEOFMYTABLEAU;
                size_type tempCap = CAPACITYOFMYTABLEAU;

                MYTABLEAU = x.MYTABLEAU;
                SIZEOFMYTABLEAU = x.SIZEOFMYTABLEAU;
                CAPACITYOFMYTABLEAU = x.CAPACITYOFMYTABLEAU;

                x.MYTABLEAU = tempTab;
                x.SIZEOFMYTABLEAU = tempSiz;
                x.CAPACITYOFMYTABLEAU = tempCap;
            }

            //ALLOCATOR//////////////////////////////////////////////////////////////////////

            allocator_type get_allocator() const{
                return myAlloc;
            }


	};

    template< class T, class Alloc >
    bool operator==( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs ){
        typedef typename ft::vector<T,Alloc>::const_iterator iterator;
            return (ft::equal<iterator, iterator>(lhs.begin(), lhs.end(), rhs.begin()) && lhs.size() == rhs.size());
    }

    template< class T, class Alloc >
    bool operator!=( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs ){
            return (!(lhs == rhs));
    }

    template< class T, class Alloc >
    bool operator<( const ft::vector<T,Alloc>& lhs,
                const ft::vector<T,Alloc>& rhs ){
        typedef typename ft::vector<T,Alloc>::const_iterator iterator;
        return (ft::lexicographical_compare<iterator, iterator>(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template< class T, class Alloc >
    bool operator>( const ft::vector<T,Alloc>& lhs,
                const ft::vector<T,Alloc>& rhs ){
        typedef typename ft::vector<T,Alloc>::const_iterator iterator;
        return (ft::lexicographical_compare<iterator, iterator>(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
    }

    template< class T, class Alloc >
    bool operator<=( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs ){
        typedef typename ft::vector<T,Alloc>::const_iterator iterator;
        return (ft::lexicographical_compare<iterator, iterator>(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) || (rhs == lhs));
    }

    template< class T, class Alloc >
    bool operator>=( const ft::vector<T,Alloc>& lhs,
                 const ft::vector<T,Alloc>& rhs ){
        typedef typename ft::vector<T,Alloc>::const_iterator iterator;
        return (ft::lexicographical_compare<iterator, iterator>(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()) || (rhs == lhs));
    }

    template <class T, class Alloc>  void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y){
        x.swap(y);
    }
}


#endif