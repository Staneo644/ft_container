#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <cstddef>
# include <array>
# include <memory>
# include <iostream>
# include <string>
# include "myIterator.hpp"
# include "enable_if.hpp"
# include "reverseIterator.hpp"
//#include <stdexcept>



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


        private :
            pointer MYTABLEAU;
            size_type SIZEOFMYTABLEAU;
            size_type CAPACITYOFMYTABLEAU;
            allocator_type myAlloc;

            void defineElement(const allocator_type& alloc){
                myAlloc = alloc;
                MYTABLEAU = NULL;
                SIZEOFMYTABLEAU = 0;
                CAPACITYOFMYTABLEAU = 0;
            }




		public:
            explicit vector (const allocator_type& alloc = allocator_type()){
                defineElement(alloc);
                resize(0);
                
            }

            explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()){
                defineElement(alloc);
                assign(n, val);
             
            }

            template <class InputIterator>
            vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!std::is_integral<InputIterator>::value>::type* = 0){
                defineElement(alloc);
                assign(first, last);
           
            }

            ~vector(){
                resize(0);
                if (MYTABLEAU != NULL)
                    myAlloc.deallocate( MYTABLEAU, CAPACITYOFMYTABLEAU);
            }

            vector (const vector& x){
                defineElement(x.get_allocator());
                resize(x.size());
                for (size_type i = 0; i < x.size(); i++){
                    MYTABLEAU[i] = x[i];
                }
            }

            //ITERATORS/////////////////////////////////////////////////////////////////////////////////////////////
            iterator begin(){

                return (MYTABLEAU);
            }

            iterator end(){
                return (MYTABLEAU + SIZEOFMYTABLEAU);
            }

            reverse_iterator rbegin(){
                return reverse_iterator(MYTABLEAU + SIZEOFMYTABLEAU - 1);

            }

            const_reverse_iterator rbegin() const{
                return reverse_iterator(MYTABLEAU + SIZEOFMYTABLEAU - 1);
            }

            reverse_iterator rend(){
                return reverse_iterator(MYTABLEAU - 1);
            }

            const_reverse_iterator rend() const{
                return reverse_iterator(MYTABLEAU - 1);
            }

            //CAPACITY/////////////////////////////////////////////////////////////////////////////////////////////

            void resize(size_type count){

                if (count > SIZEOFMYTABLEAU){
                    if (count > CAPACITYOFMYTABLEAU){
                        if (MYTABLEAU != NULL){
                            value_type *myPointer = myAlloc.allocate(CAPACITYOFMYTABLEAU, &MYTABLEAU[CAPACITYOFMYTABLEAU]);
                            if (myPointer != &MYTABLEAU[CAPACITYOFMYTABLEAU]){
                                myAlloc.deallocate(myPointer, CAPACITYOFMYTABLEAU);
                                myPointer = myAlloc.allocate(CAPACITYOFMYTABLEAU * 2);
                                for (size_type i = 0; i < CAPACITYOFMYTABLEAU; i++)
                                {
                                    myPointer[i] = MYTABLEAU[i];
                                }
                                myAlloc.deallocate(MYTABLEAU, CAPACITYOFMYTABLEAU);
                                MYTABLEAU = myPointer;
                            }
                            CAPACITYOFMYTABLEAU *= 2;
                        }
                        else {
                            value_type *myPointer = myAlloc.allocate(count);
                            CAPACITYOFMYTABLEAU = count;
                            SIZEOFMYTABLEAU = count;
                            MYTABLEAU = myPointer;
                        }
                    }
                }

                if (count < SIZEOFMYTABLEAU)
                {
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
                if (CAPACITYOFMYTABLEAU < n){
                    resize(n);
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
                return( this[n]);

            }

            const_reference at (size_type n) const{
                if (n < 0 || n >= SIZEOFMYTABLEAU)
                    throw std::out_of_range("invalid number");
                return( this[n]);
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
            void assign (InputIterator first, InputIterator last){
                clear();
                while (first != last){
                    push_back( *first);

                    first++;
                }
            }


            void assign (size_type n, const value_type& val){
                resize(n);
                for (size_type i = 0; i < n; i++){
                    MYTABLEAU[i] = val;
                }
            }

            void push_back (const value_type& val){
                resize(SIZEOFMYTABLEAU + 1);
                MYTABLEAU[SIZEOFMYTABLEAU - 1] = val;
            }

            void pop_back(){
                resize(SIZEOFMYTABLEAU - 1);
            }



            iterator erase (iterator position){
                iterator ret = position;
                //if (position + 1 == end())
                 //   ret = position;
                for (iterator mypos = position; mypos != &back(); mypos ++){
                    *mypos =  *(mypos + 1);
                }
                pop_back();
                //dprintf(1, "%d", *(position - 1));
                return ret;
            }

            iterator erase (iterator first, iterator last){
                iterator difference = 0;
                iterator ret = first;
                for (iterator mypos = first; mypos != last; mypos ++){
                    if ((last - first + mypos) < end())
                        *mypos = *((last - first) + mypos);
                    difference ++;
                }
                resize(SIZEOFMYTABLEAU - (last - first));
                return ret;
            }

            iterator insert (iterator position, const value_type& val){
                //dprintf(1, "LAAAAAA");
                insert(position, (1),val);
                return position;
            }


            void insert (iterator position, size_type n, const value_type& val){

                iterator difference = end() - 1;
                resize(SIZEOFMYTABLEAU + n);
                for (; difference != position; difference--){
                    *(difference + n) = *difference;
                }
                *(difference + n) = *difference;
                while (n > 0){
                    *(position + n - 1) = val;
                    n--;
                }
            }


            template <class InputIterator>
            void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!std::is_integral<InputIterator>::value>::type* = 0){
                iterator difference = end() - 1;
                resize(SIZEOFMYTABLEAU + (last - first));
                for (; difference != position; difference--){
                    *(difference + (last - first)) = *difference;
                }
                *(difference + (last - first)) = *difference;
                while(first != last){
                    *position = *first;
                    position ++;
                    first ++;
                }
            }

            void clear(){
                resize(0);
            }

            void swap (vector& x){
                dprintf(1, "sfs\n");
                ft::vector<value_type> buffer (x.begin(), x.end());
                dprintf(1, "%d\n", *buffer.begin());

                //x.clear();
                x.assign( this->begin(), this->end());
                //this->clear();
                assign( buffer.begin(), buffer.end());
            }

            //ALLOCATOR//////////////////////////////////////////////////////////////////////

            allocator_type get_allocator() const{
                return myAlloc;
            }


	};

    template <class T, class Alloc>  void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y){
        x.swap(y);
    }
}


#endif