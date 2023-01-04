#ifndef CONTAINERS_MAP_H
#define CONTAINERS_MAP_H
# include <iostream>
//# include <array>
//# include <cstddef>
# include "pair.hpp"
# include "enable_if.hpp"
# include "iterator_traits.hpp"
# include "reverseIterator.hpp"

namespace ft {
    
    template<class InputIt>
    bool lexicographical_compare(InputIt first1, InputIt last1,
                                InputIt first2, InputIt last2) 
    {
        InputIt x = first1;
        InputIt y = first2;
        for (; (x != y) && (y != last2); (void) ++x, (void) ++y)
        {
            if (*x < *y)
                return true;
            if (*y < *x)
                return false;
        }
        return (x == last1) && (y != last2);
    }

    template<
        class Key,
        class T,
        class Compare = std::less<Key>,
        class Allocator = std::allocator<ft::pair<const Key, T > > >

    class map{

        public:
            typedef Key key_type;
            typedef T mapped_type ;
            typedef ft::pair<const Key, T> value_type;
            typedef std::size_t size_type;
            typedef std::ptrdiff_t difference_type;
            typedef Compare key_compare;
            typedef Allocator allocator_type;
            typedef const value_type& const_reference;
            typedef typename Allocator::pointer pointer;
            typedef typename Allocator::const_pointer const_pointer;

        private :            
            struct TreeNode {
                typedef typename allocator_type::template rebind<TreeNode>::other    node_allocator;
                node_allocator myAlloca;

                value_type myValue;
                unsigned int depth;
                TreeNode *little;
                TreeNode *big;
                TreeNode *parent;
                key_type key(){return myValue.first;}
                T Value(){return myValue.second;}

                TreeNode(value_type myNewValue) : myValue(myNewValue){}
                ~TreeNode(){}

                TreeNode & operator= (const TreeNode &x) { myValue(x.myValue); little(x.little); big(x.big);}
                TreeNode(const TreeNode& x) : myValue(x.myValue), little(x.little), big(x.big){
                }

                bool operator== ( const TreeNode& y){
                    return myValue == y.myValue;
                }

                bool operator!= ( const TreeNode& y){
                    return myValue != y.myValue;
                }
            };

            TreeNode* EndOfTree;

            static TreeNode* BigInParent(TreeNode *i) {
                if (!i->parent)
                    return (NULL);
                if (i->parent->big != i)
                    return i->parent;
                return BigInParent(i->parent);
            }

            static TreeNode* Bigger(TreeNode *i) {
                if (i->big)
                    return (LittleValue(i->big));
                else
                    return BigInParent(i);
            }

            TreeNode *myRacine;

            static  TreeNode* LittleInParent(TreeNode *i){
                if (!i->parent)
                    return (NULL);
                if (i->parent->little != i)
                    return i->parent;
                return LittleInParent(i->parent);
            }

            static TreeNode* Smaller(TreeNode *i) {

                if (i->big)
                    return (LittleValue(i->big));
                else {
                    return LittleInParent(i);
                }
            }

        public :

            class map_iterator : std::bidirectional_iterator_tag
            {
                public :
                    /*typedef typename TreeIterator::NodeTypes                   NodeTypes;*/
                    typedef typename map::pointer             pointer_traits;

                private :

                public:
                    TreeNode  *i;
                    typedef std::bidirectional_iterator_tag             iterator_category;
                    //typedef typename map::TreeNode                      TreeNode;
                    typedef typename map::value_type                    value_type;
                    typedef typename map::difference_type      difference_type;
                    typedef value_type&                                 reference;
                    typedef typename map::pointer  pointer;

                    map_iterator() {}

                    map_iterator(TreeNode _i) : i(&_i) {}

                    map_iterator(TreeNode* _i) : i(_i) {}

                    reference operator*() const {return i->myValue;}

                    value_type *operator->() const {return (&(i->myValue));}

                    map_iterator& operator++() {i = map::Bigger(i); return *this;}

                    map_iterator operator++(int) {
                        map_iterator t(*this);
                        i = map::Bigger(i);
                        return t;
                    }

                    map_iterator& operator--() {i = map::Smaller(i); return *this;}

                    map_iterator operator--(int) {
                        map_iterator t(*this);
                        i = map::Smaller(*this);
                        return t;
                    }

                    bool operator==( const map_iterator& y) const
                        {
                            if (i == NULL && y.i == NULL)
                                return true;
                            if (i == NULL || y.i == NULL)
                                return false;
                            return i->myValue == y.i->myValue;}

                    bool operator!=( const map_iterator& y) const
                        {
                            if (i == NULL && y.i == NULL)
                                return false;
                            if (i == NULL || y.i == NULL)
                                return true;
                            return i->myValue != y.i->myValue;}
            };

        private :

        class value_compare : public std::binary_function<value_type, value_type, bool>
        {
            protected:
                key_compare comp;

                value_compare(key_compare c) : comp(c) {}
            public:
                bool operator()(const value_type& x, const value_type& y) const
                    {return comp(x.first, y.first);}
        };


        public :
            typedef map_iterator iterator;
            typedef const map_iterator const_iterator;
            typedef ft::reverse_iterator<iterator> reverse_iterator;
            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
           // typedef /*iterator_traits<iterator>::difference_type*/ std::ptrdiff_t difference_type;

            
        private :
            size_type SIZEOFMYMAP;

            TreeNode* DefineNode(value_type newValue){
                TreeNode Allocate(newValue);
                SIZEOFMYMAP++;
                TreeNode *myPointer = Allocate.myAlloca.allocate(1);
                Allocate.myAlloca.construct(myPointer, newValue);
                (*myPointer).little = NULL;
                (*myPointer).big = NULL;
                myPointer->parent = NULL;
                (*myPointer).depth = 0;
                return(myPointer);
            }

            TreeNode* DestroyNode(TreeNode* myNode){
                TreeNode Allocate(myNode->myValue);
                SIZEOFMYMAP--;
                Allocate.myAlloca.destroy(myNode);
                Allocate.myAlloca.deallocate(myNode, 1);
                return (NULL);
            }


            TreeNode *SearchNode(key_type key){
                TreeNode *myValue = myRacine;
                while (myValue != NULL && myValue->key() != key)
                {
                    if (key > myValue->key())
                        myValue = myValue->big;
                
                    else
                        if (key < myValue->key())
                            myValue = myValue->little;
                }
                return myValue;
            }

            TreeNode *ApproximativeSearchNode(key_type key){
                TreeNode *myValue = myRacine;
                while (((key > myValue->key() && myValue->big != NULL) || (key < myValue->key() && myValue->little != NULL)) && myValue->key() != key)
                {
                    if (key > myValue->key() && myValue->big != NULL)
                        myValue = myValue->big;
                
                    else
                        if (key < myValue->key() && myValue->little != NULL)
                            myValue = myValue->little;
                }
                return myValue;
            }

            void RecursiveDestroy(TreeNode* myNode){
                if (myNode == NULL)
                    return ;
                RecursiveDestroy(myNode->little);
                RecursiveDestroy(myNode->big);
                DestroyNode(myNode);
            }

            void Init(){
                myRacine = NULL;
                SIZEOFMYMAP = 0;
                EndOfTree = NULL;
            }

            static TreeNode * LittleValue(TreeNode *myNode){
                if (myNode == NULL || myNode->little == NULL)
                    return (myNode);
                return (LittleValue(myNode->little));
            }

            static TreeNode * BigValue(TreeNode *myNode){
                if (myNode == NULL || myNode->big == NULL)
                    return (myNode);
                return (BigValue(myNode->big));
            }

            int ChangeDepth(TreeNode *myNode){
                if (myNode->little == NULL && myNode->big == NULL)
                {
                    myNode->depth = 0;
                    return 1;
                }
                if (myNode->little == NULL)
                {
                    myNode->depth = myNode->big->depth + 1;
                    return 1;
                }
                if (myNode->big == NULL)
                {
                    myNode->depth = myNode->little->depth + 1;
                    return 1;
                }
                myNode->depth = ((myNode->little->depth >= myNode->big->depth) * myNode->little->depth) + ((myNode->little->depth < myNode->big->depth) * myNode->big->depth) + 1;
                return (1);
            }

            TreeNode* PutValue(TreeNode *myValue, TreeNode *myNode){
                    if (myNode == NULL){
                        return myValue;
                    }

                    if (myValue->myValue.first < myNode->key()){
                        myNode->little = PutValue(myValue, (myNode->little));
                        myNode->little->parent = myNode;
                        ChangeDepth(myNode);
                    }

                    if (myValue->myValue.first > myNode->key()){
                        myNode->big = PutValue(myValue, (myNode->big));
                        myNode->big->parent = myNode;
                        ChangeDepth(myNode);
                    }
                    return (myNode);
            }

            void changeRecursiveParent(TreeNode* myNode){
                if (myNode->big){
                    myNode->big->parent = myNode;
                    changeRecursiveParent(myNode->big);
                }
                if (myNode->little){
                    myNode->little->parent = myNode;
                    changeRecursiveParent(myNode->little);
                }
            }

            void changeRecursiveDepth(TreeNode* myNode){
                if (myNode == NULL)
                    return ;
                changeRecursiveDepth(myNode->big);
                changeRecursiveDepth(myNode->little);
                ChangeDepth(myNode);
            }



            TreeNode* rotatelittle(TreeNode* a){
                if (a && a->little){
                    TreeNode* temp = a->little->big;
                    a->little->big = a;
                    a->parent = a->little;
                    a->little = temp;
                    return (a->parent);
                }
                return NULL;
            }

            TreeNode* rotatebig(TreeNode* a){
                if (a && a->big){
                    TreeNode* temp = a->big->little;
                    a->big->little = a;
                    a->parent = a->big;
                    a->big = temp;
                    return (a->parent);
                }
                return NULL;
            }

            bool notGoodDepth(TreeNode* a){
                if (a == NULL)
                    return false;
                int depthBig = 0;
                if (a->big)
                    depthBig = a->big->depth;
                int depthLittle = 0;
                if (a->little)
                    depthLittle = a->little->depth;
                if ((depthBig - depthLittle) >= 1)
                    return true;
                if ((depthLittle - depthBig) >= 1)
                    return true;
                return false;
            }

            TreeNode* adjust(TreeNode *a){
                if (a == NULL)
                    return (NULL);
                int depthBig = 0;
                if (a->big)
                    depthBig = a->big->depth;
                int depthLittle = 0;
                if (a->little)
                    depthLittle = a->little->depth;
                if (depthBig > depthLittle)
                    a = rotatebig(a);
                else
                    a = rotatelittle(a);
                changeRecursiveParent(a);
                changeRecursiveDepth(a);
                return a;
            }

            TreeNode* balanceAVL(TreeNode* a){
                if (a == NULL)
                    return (NULL);
                changeRecursiveDepth(a);
                if (notGoodDepth(a)){
                    std::cout << "key : " << a->key() << std::endl;
                //dprintf(1, "OUI");
                    a = adjust(a);
                    //print();
                }
                //dprintf(1, "NON");
                a->big = balanceAVL(a->big);
                a->little = balanceAVL(a->little);
                //
                return a;
            }

        public:

            bool prufung(TreeNode *myRac, int a, int b){
                int c = b;
                while (c-- > 0)
                {
                    std::cout << " ";
                }
                if (myRac == NULL){
                    std::cout << "          ";
                    return false;
                }
                if (a > 0){
                    bool ab = prufung(myRac->little, a - 1, b);
                    bool bb = prufung(myRac->big, a - 1, b);
                    return (bb || ab);
                }
                else
                {
                    std::cout << " clée: " << (*myRac).key();//" valeur " << (*myRac).Value();
                    if (myRac->parent)
                        std::cout << "-" << myRac->parent->key();
                    return (true);
                }
                
            }

            void print(){
                int b = 40;
                int a = 0;
                changeRecursiveParent(myRacine);
                changeRecursiveDepth(myRacine);
                std::cout << "__________________ " << SIZEOFMYMAP << " ______________________________________________________________________\n"; 
                while (prufung(myRacine, a++, b) == true)
                {
                    std::cout << "\n\n";
                    b /= 2;
                }
                std::cout << "\n";
                
                /*std::cout << "profondeur: "<< myRac->depth << " clée: " << (*myRac).key() << " valeur " << (*myRac).Value();
                if ((*myRac).little != NULL)
                    print(myRac->little, a / 2);
                if ((*myRac).big != NULL)
                    print(myRac->big, a / 2);*/
            }



















            map& operator= (const map& x){
                myRacine = x.myRacine;
            }

            ~map(){
                RecursiveDestroy(myRacine);
            }

            //////////////////CONSTRUCTOR///////////////////////////////////////////


            template <class InputIterator>  map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(), typename ft::enable_if<!std::is_integral<InputIterator>::value>::type* = 0){
                (void)comp;
                Init();
                insert(first, last);

            }

            //explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()){

            //}
            
            explicit map( const Compare& comp,
              const Allocator& alloc = Allocator() ){
                   (void)comp;
                Init();
            }

            map(){
                Init();
            }

            map (const map& x){
                Init();
                myRacine = x.myRacine;
            }

            /////////////////////////ITERATORS///////////////////////////////////////////

            iterator begin(){
                return (LittleValue(myRacine));
            }
            
            const_iterator begin() const{
                return (LittleValue(myRacine)); 
            }

            iterator end(){
                return NULL;
            }
            
            const_iterator end() const{
                return NULL;
            }

            reverse_iterator rbegin(){
                return (reverse_iterator(iterator( BigValue(myRacine))));
            }

            const_reverse_iterator rbegin() const{
                return reverse_iterator(BigValue(myRacine));
            }

            reverse_iterator rend(){
                return (reverse_iterator( iterator(NULL)));
            }

            const_reverse_iterator rend() const{
                return reverse_iterator(NULL);
            }

            ////////////////////CAPACITY////////////////////////////////////////////////////////////

            bool empty() const{
                return (SIZEOFMYMAP == 0);
            }


            size_type size() const{
                return SIZEOFMYMAP;
            }

            size_type max_size() const{
                return myRacine->myAlloc.max_size();
            }

            //////////////////////MODIFIER//////////////////////////////////////////////////////////////

            void clear(){
                RecursiveDestroy(myRacine);
                myRacine = NULL;
            }

            ft::pair<iterator,bool> insert (const value_type& val){
                ft::pair<iterator,bool> ret;
                if (SearchNode(val.first) == NULL) {
                    ret.second = true;
                    myRacine = PutValue(DefineNode(val), myRacine);
                    myRacine = balanceAVL(myRacine);
                    myRacine->parent = NULL;
                    print();
                }
                else {
                    ret.second = false;
                }
                ret.first = ((SearchNode(val.first)));
                return ret;
            }

            iterator insert (iterator position, const value_type& val){
                (void)position;
                return (insert(val).first);
            }

            template <class InputIterator>
            void insert (InputIterator first, InputIterator last){
                while (first != last)
                {
                    insert(first);
                    first++;
                }
                insert(last);              
            }

            void erase (iterator position){
                erase(position->i->Key());
            }


            size_type erase (const key_type& k){
                TreeNode *NodeErase = SearchNode(k);
                if (NodeErase == NULL)
                    return 0;

                TreeNode *tempr = NodeErase->big;
                TreeNode *templ = NodeErase->little;

                if (NodeErase->parent != NULL){
                    if (NodeErase->parent->little == NodeErase)
                        NodeErase->parent->little = NULL;
                    if (NodeErase->parent->big == NodeErase)
                        NodeErase->parent->big = NULL;
                }
                if (NodeErase == myRacine)
                    myRacine = NULL;
                DestroyNode(NodeErase);
                if (templ)
                    myRacine = PutValue(templ, myRacine);
                if (tempr)
                    myRacine = PutValue(tempr, myRacine);
                
                myRacine = balanceAVL(myRacine);
                return 1;
            }

            void erase (iterator first, iterator last){
                while (first != last){
                    erase(first);
                    first++;
                }
                erase(last);
            }

            void swap (map& x){
                TreeNode * temp = myRacine;
                myRacine = x.myRacine;
                x.myRacine = myRacine;
            }

            mapped_type& operator[] (const key_type& k){
                mapped_type &z = insert(ft::make_pair(k, T())).first->second;
                return z;
            }

            mapped_type& at (const key_type& k){
                TreeNode *ret = SearchNode(k);
                if (ret != NULL){
                    return (&((*ret)->myValue()));
                }
                throw std::out_of_range("invalid number");
            }
            
            
            const mapped_type& at (const key_type& k) const{
                TreeNode ret = SearchNode(k);
                if (ret != NULL){
                    return (&((*ret)->myValue()));
                }
                throw std::out_of_range("invalid number");
            }

            iterator find (const key_type& k){
                return (SearchNode(k));
            }
            

            const_iterator find (const key_type& k) const{
                return (SearchNode(k));
            }

            std::pair<iterator,iterator> equal_range( const Key& key ){
                return ft::make_pair<iterator, iterator>(lower_bound(key), upper_bound(key));
            }

            std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const{
                return ft::make_pair<iterator, iterator>(lower_bound(key), upper_bound(key));
            }


        //////////////////////OBSERVERS//////////////////////////////////////////////////////////////

        key_compare key_comp() const{
            return key_compare() ;
            };

        value_compare value_comp() const{
            return value_compare(key_comp());
        }

        iterator lower_bound( const Key& key ){
            TreeNode* a = ApproximativeSearchNode(key);
            if (a->key() < key)
                a = Bigger(a);
            return (a);
        }

        const_iterator lower_bound( const Key& key ) const{
            TreeNode* a = ApproximativeSearchNode(key);
            if (a->key() < key)
                a = Bigger(a);
            return (a);
        }

        iterator upper_bound( const Key& key ){
            TreeNode* a = ApproximativeSearchNode(key);
            if (a->key() <= key)
                a = Bigger(a);
            return (a);
        }

        const_iterator upper_bound( const Key& key ) const{
            TreeNode* a = ApproximativeSearchNode(key);
            if (a->key() <= key)
                a = Bigger(a);
            return (a);
        }
    };

    template< class Key, class T, class Compare, class Alloc >
    void swap(map<Key,T,Compare,Alloc>& lhs,
           map<Key,T,Compare,Alloc>& rhs ){
        lhs.swap(rhs);
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator==( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs ){
        typedef typename ft::map<Key, T, Compare, Alloc>::iterator iterator;
        //typedef ft::map<Key, T, Compare, Alloc> map;
        iterator lit = lhs.begin();
        iterator rit = rhs.begin();

        //std::cout << "coucou " << (lit != lhs.end()) <<std::endl;
        for (; lit != lhs.end() && rit != rhs.end(); rit++, lit++)
        {
            //std::cout << "coucou" << std::endl;
            //std::cout <<  lit->first << " hh " << rit->first << "\n\n";
            if (lit != rit)
                return false;
        }
        if (rit == rhs.end() && lit == lhs.end())
            return (true);
        //std::cout <<  lit->second << " rr " << rit->second << "\n\n";
        return (false);
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator!=( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs ){
        return (!(lhs == rhs));
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator<( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs ){
        typedef typename ft::map<Key, T>::iterator iterator;
        return (ft::lexicographical_compare<iterator>(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator<=( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs ){
        typedef typename ft::map<Key, T>::iterator iterator;
        return (ft::lexicographical_compare<iterator>(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) || (rhs == lhs));
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator>( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs ){
        typedef typename ft::map< Key, T, Compare, Alloc>::const_iterator iterator;
        return (std::lexicographical_compare<iterator, iterator>(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator>=( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs ){
        typedef typename ft::map<Key, T>::const_iterator iterator;
        map<Key,T,Compare,Alloc> crhs = rhs;
        map<Key,T,Compare,Alloc> clhs = lhs;
        return (std::lexicographical_compare<iterator, iterator>(crhs.begin(), crhs.end(), clhs.begin(), clhs.end()) || (rhs == lhs));
    }
}

#endif
