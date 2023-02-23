#ifndef CONTAINERS_MAP_H
#define CONTAINERS_MAP_H
# include <iostream>
//# include <array>
//# include <cstddef>
# include "pair.hpp"
# include "enable_if.hpp"
# include "iterator_traits.hpp"
# include "reverseIterator.hpp"
# include "equal.hpp"

namespace ft {

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


            TreeNode *myRacine;
            TreeNode *Sentinelle;

            static TreeNode* BigInParent( TreeNode *i) {
                if (!i->parent)
                    return (BigValue(i)->big);
                if (superior(i->parent->key(), i->key()))
                    return i->parent;
                return BigInParent(i->parent);
            }

            static TreeNode* Bigger(TreeNode *i) {
                if (i == NULL)
                    return (i);
                if (i->big == NULL && i->parent == NULL)
                    return (i);
                if (i->big == NULL)
                    return(i->little);

                if (i->big->big) {
                    return (LittleValue(i->big));
                }
                else {
                    return (BigInParent(i));
                }
            }


            static  TreeNode* LittleInParent(TreeNode *i){
                if (!i->parent) {
                    return (BigValue(i)->big);
                }
                if (inferior(i->parent->key(), i->key()))
                    return i->parent;
                return LittleInParent(i->parent);
            }

            static TreeNode* Smaller(TreeNode *i) {
                if (i == NULL)
                    return (i);
                if (i->big == NULL && i->parent == NULL)
                    return (i);
                if (i->big == NULL)
                    return(i->parent);

                if (i->little->big)
                    return (BigValue(i->little));
                else {
                    return LittleInParent(i);
                }
            }

        public :
            class map_iterator : std::bidirectional_iterator_tag
            {
                public :
                    typedef typename map::pointer             pointer_traits;

                private :

                public:
                    TreeNode  *i;
                    typedef std::bidirectional_iterator_tag             iterator_category;
                    typedef map::value_type                    value_type;
                    typedef typename map::difference_type      difference_type;
                    typedef value_type&                                 reference;
                    typedef value_type*  pointer;

                    map_iterator() {}

                    map_iterator(TreeNode _i) : i(&_i) {}

                    map_iterator(TreeNode* _i) : i(_i) {}
                    
                    map_iterator(const map_iterator &_i) : i(_i.i){}

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
                        i = map::Smaller(i);
                        return t;
                    }

                    bool operator==( const map_iterator& y) const
                        {
                            if (i == NULL && y.i == NULL)
                                return true;
                            if (i == NULL || y.i == NULL)
                                return false;
                            return i == y.i;}

                    bool operator!=( const map_iterator& y) const
                        {
                            return (!(operator==(y)));}
            };

            class const_map_iterator : std::bidirectional_iterator_tag
            {
                public :
                    typedef typename map::pointer             pointer_traits;

                private :

                public:
                    TreeNode  *i;
                    typedef std::bidirectional_iterator_tag             iterator_category;
                    typedef const map::value_type                    value_type;
                    typedef typename map::difference_type      difference_type;
                    typedef value_type&                                 reference;
                    typedef value_type*  pointer;

                    const_map_iterator() {}

                    const_map_iterator(TreeNode _i) : i(&_i) {}

                    const_map_iterator(TreeNode* _i) : i(_i) {}
                    
                    const_map_iterator(const const_map_iterator &_i) : i(_i.i){}

                    const_map_iterator(const map_iterator &_i) : i(_i.i){}

                    reference operator*() const {return i->myValue;}

                    value_type *operator->() const {return (&(i->myValue));}

                    const_map_iterator& operator++() {i = map::Bigger(i); return *this;}

                    const_map_iterator operator++(int) {
                        const_map_iterator t(*this);
                        i = map::Bigger(i);
                        return t;
                    }

                    const_map_iterator& operator--() {i = map::Smaller(i); return *this;}

                    const_map_iterator operator--(int) {
                        const_map_iterator t(*this);
                        i = map::Smaller(i);
                        return t;
                    }

                    bool operator==( const const_map_iterator& y) const {
                            if (i == NULL && y.i == NULL)
                                return true;
                            if (i == NULL || y.i == NULL)
                                return false;
                            return i == y.i;}

                    bool operator==( const map_iterator& y) const {
                            if (i == NULL && y.i == NULL)
                                return true;
                            if (i == NULL || y.i == NULL)
                                return false;
                            return i == y.i;}

                    bool operator!=( const const_map_iterator& y) const { 
                        return (!(operator==(y)));
                    }
            };

        class value_compare : public std::binary_function<value_type, value_type, bool>
        {
            protected:
                key_compare comp;

            public:
                value_compare(key_compare c) : comp(c) {}
                bool operator()(const value_type& x, const value_type& y) const
                    {return comp(x.first, y.first);}
        };

            typedef map_iterator iterator;
            typedef const_map_iterator const_iterator;
            typedef ft::reverse_iterator<iterator> reverse_iterator;
            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
            
        private :
            size_type SIZEOFMYMAP;

            TreeNode* DefineNode(value_type newValue){
                TreeNode Allocate(newValue);
                SIZEOFMYMAP++;
                TreeNode *myPointer = Allocate.myAlloca.allocate(1);
                Allocate.myAlloca.construct(myPointer, newValue);
                (*myPointer).little = Sentinelle;
                (*myPointer).big = Sentinelle;
                myPointer->parent = NULL;
                (*myPointer).depth = 0;
                return(myPointer);
            }

            TreeNode* DestroyNode(TreeNode* myNode){
                if (myNode == Sentinelle)
                    return (Sentinelle);
                if (myNode == NULL)
                    return (NULL);
                TreeNode Allocate(myNode->myValue);
                SIZEOFMYMAP--;
                Allocate.myAlloca.destroy(myNode);
                
                Allocate.myAlloca.deallocate(myNode, 1);
                myNode = Sentinelle;
                return (Sentinelle);
            }


            TreeNode *SearchNode(key_type key) const {
                if (myRacine == Sentinelle)
                    return Sentinelle;
                TreeNode *myValue = myRacine;
                while (myValue != Sentinelle && !equal(myValue->key(), key))
                {
                    if (superior(key, myValue->key()))
                        myValue = myValue->big;
                
                    else
                        if (inferior(key, myValue->key()))
                            myValue = myValue->little;
                }
                return myValue;
            }

            TreeNode *ApproximativeSearchNode(key_type key) const {
                TreeNode *myValue = myRacine;
                while (((superior(key, myValue->key()) && myValue->big != Sentinelle) || (inferior( key, myValue->key()) && myValue->little != Sentinelle)) && !equal(myValue->key(), key))
                {
                    if (superior(key, myValue->key()) && myValue->big != Sentinelle)
                        myValue = myValue->big;
                
                    else
                        if (inferior(key,  myValue->key()) && myValue->little != Sentinelle)
                            myValue = myValue->little;
                }
                return myValue;
            }

            void RecursiveDestroy(TreeNode* myNode){
                if (myNode == NULL || myNode == Sentinelle)
                    return ;
                RecursiveDestroy(myNode->little);
                RecursiveDestroy(myNode->big);
                DestroyNode(myNode);
            }

            void Init(){
                TreeNode x = TreeNode(value_type());
                Sentinelle = x.myAlloca.allocate(1);
                x.myAlloca.construct(Sentinelle, value_type());
                Sentinelle->big = NULL;
                Sentinelle->depth = 0;
                myRacine = Sentinelle;
                SIZEOFMYMAP = 0;
            }

            static TreeNode * LittleValue(TreeNode *myNode) {
                if (myNode->big == NULL || myNode->little->big == NULL)
                    return (myNode);
                return (LittleValue(myNode->little));
            }

            static TreeNode * BigValue(TreeNode *myNode) {
                if (myNode->big == NULL || myNode->big->big == NULL)
                    return (myNode);
                return (BigValue(myNode->big));
            }

            int ChangeDepth(TreeNode *myNode){
                if (myNode == NULL || myNode == Sentinelle)
                    return (0);
                if (myNode->little->depth >= myNode->big->depth){
                    myNode->depth = myNode->little->depth + 1;
                }
                else 
                {
                    myNode->depth = myNode->big->depth + 1;
                }
                return (1);
            }

            void ChangeParent(TreeNode *myNode){
                if (myNode == Sentinelle)
                    return ;
                if (myNode->big != Sentinelle)
                    myNode->big->parent = myNode;
                if (myNode->little != Sentinelle)
                    myNode->little->parent = myNode;
            }

            static bool inferior(const key_type a , const key_type  b){
                key_compare comp;
                return (comp(a, b ));
            }

            static bool superior(const key_type  a, const key_type  b){
                key_compare comp;
                return (comp(b, a));
            }

            static bool equal(const key_type  a, const key_type b){
                return (!superior(a, b) && !inferior(a, b));
            }

            TreeNode* PutValue(TreeNode *myValue, TreeNode *myNode){
                    if (myNode == Sentinelle){
                        return myValue;
                    }

                    if (myValue == Sentinelle)
                        return (myNode);

                    if (inferior(myValue->key(), myNode->key())){
                        myNode->little = PutValue(myValue, (myNode->little));
                        myNode->little->parent = myNode;
                        ChangeDepth(myNode);
                    }

                    if (superior(myValue->key(), myNode->key())){
                        myNode->big = PutValue(myValue, (myNode->big));
                        myNode->big->parent = myNode;
                        ChangeDepth(myNode);
                    }
                    return (myNode);
            }

            /*void changeRecursiveParent(TreeNode* myNode){
                if (myNode == Sentinelle)
                    return ;
                if (myNode->big != Sentinelle){
                    myNode->big->parent = myNode;
                    changeRecursiveParent(myNode->big);
                }
                if (myNode->little != Sentinelle){
                    myNode->little->parent = myNode;
                    changeRecursiveParent(myNode->little);
                }
            }

            void changeRecursiveDepth(TreeNode* myNode){
                if (myNode == Sentinelle)
                    return ;
                //dprintf(1, " DEPTH ");
                
                changeRecursiveDepth(myNode->big);
                changeRecursiveDepth(myNode->little);
                ChangeDepth(myNode);
            }*/

            TreeNode* rotatelittle(TreeNode* a){
                if (a != Sentinelle && a->little != Sentinelle){
                    TreeNode* temp = a->little->big;
                    a->little->big = a;
                    TreeNode* tempP = a->parent;
                    a->parent = a->little;
                    a->little = temp;

                    ChangeDepth(a->little);
                    ChangeDepth(a);
                    ChangeDepth(a->parent);

                    a->parent->parent = tempP;

                    ChangeParent(a->little);
                    ChangeParent(a);
                    ChangeParent(a->parent);

                    return (a->parent);
                }
                return Sentinelle;
            }

            TreeNode* rotatebig(TreeNode* a){
                if (a != Sentinelle && a->big != Sentinelle){
                    TreeNode* temp = a->big->little;
                    a->big->little = a;
                    TreeNode* tempP = a->parent;
                    a->parent = a->big;
                    a->big = temp;

                    ChangeDepth(a->big);
                    ChangeDepth(a);
                    ChangeDepth(a->parent);

                    a->parent->parent = tempP;

                    ChangeParent(a->big);
                    ChangeParent(a);
                    ChangeParent(a->parent);

                    return (a->parent);
                }
                return Sentinelle;
            }

            TreeNode* adjust(TreeNode *a){
                if (a == Sentinelle)
                    return (Sentinelle);
                int depthBig = a->big->depth;
                int depthLittle = a->little->depth;
                if ((depthBig - depthLittle) > 1)
                    a = rotatebig(a);
                if ((depthLittle - depthBig) > 1)
                    a = rotatelittle(a);
                return a;
            }

            TreeNode* balanceAVL(TreeNode* a, key_type myKey){
                if (a == Sentinelle)
                    return (Sentinelle);
                a = adjust(a);
                if (superior(myKey, a->key()))
                    a->big = balanceAVL(a->big, myKey);
                if (inferior(myKey, a->key()))
                    a->little = balanceAVL(a->little, myKey);
                return a;
            }

            void OneChangement(key_type myKey){
                myRacine->parent = NULL;
                myRacine = balanceAVL(myRacine, myKey);
                if (myRacine == Sentinelle){
                    Sentinelle->parent = NULL;
                    Sentinelle->little = NULL;
                    return ;
                }
                
                myRacine->parent = NULL;
                Sentinelle->parent = BigValue(myRacine);
                Sentinelle->little = LittleValue(myRacine);
                //print();
            }


            /*bool prufung(TreeNode *myRac, int a, int b){
                int c = b;
                while (c-- > 0){
                    std::cout << " ";
                }
                if (myRac == Sentinelle){
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
                    std::cout << " clée: " << (*myRac).key();
                    if (myRac->parent)
                        std::cout << "-" << myRac->parent->key();
                    return (true);
                }
            }

            void print(){
  
                int b = 40;
                int a = 0;
                std::cout << "__________________ " << SIZEOFMYMAP << " ______________________________________________________________________\n"; 
                while (prufung(myRacine, a++, b) == true)
                {
                    std::cout << "\n\n";
                    b /= 2;
                }
                std::cout << "\n";
            }*/











        public:
            map& operator= (const map& x){

                clear();
                insert(x.begin(), x.end());
                return (*this);
            }

            ~map(){
                clear();
                TreeNode Allocate(Sentinelle->myValue);
                Allocate.myAlloca.destroy(Sentinelle);
                
                Allocate.myAlloca.deallocate(Sentinelle, 1);
            }

            //////////////////CONSTRUCTOR///////////////////////////////////////////

            template <class InputIterator>  map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0){
              
                (void)comp;
                (void)alloc;
                Init();
                insert(first, last);

            }
            
            explicit map( const Compare& comp,
              const Allocator& alloc = Allocator() ){
                    (void)alloc;
                    (void)comp;
                Init();
            }

            map(){
                Init();
            }

            map (const map& x){
                Init();
                insert(x.begin(), x.end());
            }

            /////////////////////////ITERATORS///////////////////////////////////////////

            iterator begin(){
                return (LittleValue(myRacine));
            }
            
            const_iterator begin() const{
                return (const_iterator(LittleValue(myRacine))); 
            }

            iterator end(){
                return Sentinelle;
            }
            
            const_iterator end() const{
                return const_iterator(Sentinelle);
            }

            reverse_iterator rbegin(){
                return (reverse_iterator(end()));
            }

            const_reverse_iterator rbegin() const{
                return const_reverse_iterator(end());
            }

            reverse_iterator rend(){
                return (reverse_iterator(begin()));
            }

            const_reverse_iterator rend() const{
                return const_reverse_iterator(begin());
            }

            ////////////////////CAPACITY////////////////////////////////////////////////////////////

            bool empty() const{
                return (myRacine == Sentinelle);
            }

            size_type size() const{
                return SIZEOFMYMAP;
            }

            size_type max_size() const{
                return myRacine->myAlloca.max_size();
            }

            //////////////////////MODIFIER//////////////////////////////////////////////////////////////

            void clear(){
                RecursiveDestroy(myRacine);
                myRacine = Sentinelle;
            }

            ft::pair<iterator,bool> insert (const value_type& val){
                ft::pair<iterator,bool> ret;
                if (SearchNode(val.first) == Sentinelle) {
                    ret.second = true;
              
                    myRacine = PutValue(DefineNode(val), myRacine);
                    OneChangement(val.first);
                  
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
                
                while (first != last){
                    insert(*first);
                    first++;
                }          
            }

            void erase (iterator position){
                erase(position->first);
            }


            size_type erase (const key_type& k){
                TreeNode *NodeErase = SearchNode(k);
                if (NodeErase == Sentinelle)
                    return 0;

                TreeNode *tempb = NodeErase->big;
                TreeNode *templ = NodeErase->little;

                if (NodeErase->parent != NULL){
                    if (NodeErase->parent->little == NodeErase)
                        NodeErase->parent->little = Sentinelle;
                    if (NodeErase->parent->big == NodeErase)
                        NodeErase->parent->big = Sentinelle;
                }
                if (NodeErase == myRacine){
                    myRacine = tempb;
                    myRacine = PutValue(templ, myRacine);
                    OneChangement(k);
                    NodeErase = DestroyNode(NodeErase);
                    return (1);
                }
                NodeErase = DestroyNode(NodeErase);
                myRacine = PutValue(templ, myRacine);
                myRacine = PutValue(tempb, myRacine);
                OneChangement(k);
                return 1;
            }

            void erase (iterator first, iterator last){
                iterator temp;
                while (first != last){
                    temp = first;
                    temp++;
                    erase(first);
                    first = temp;
                }

            }

            void swap (map& x){
                TreeNode* temprac = myRacine;
                size_type tempsiz = SIZEOFMYMAP;
                TreeNode* tempsen = Sentinelle;

                myRacine = x.myRacine;
                SIZEOFMYMAP = x.SIZEOFMYMAP;
                Sentinelle = x.Sentinelle;

                x.myRacine = temprac;
                x.SIZEOFMYMAP = tempsiz;
                x.Sentinelle = tempsen;
                }

            mapped_type& operator[] (const key_type& k){
                mapped_type &z = insert(ft::make_pair(k, T())).first->second;
                return z;
            }

            mapped_type& at (const key_type& k){
                TreeNode *ret = SearchNode(k);
                if (ret != Sentinelle){
                    return (&((*ret)->myValue()));
                }
                throw std::out_of_range("invalid number");
            }
            
            
            const mapped_type& at (const key_type& k) const{
                TreeNode ret = SearchNode(k);
                if (ret != Sentinelle){
                    return (&((*ret)->myValue()));
                }
                throw std::out_of_range("invalid number");
            }

            size_type count (const key_type& k) const{
                if (SearchNode(k) != Sentinelle)
                    return (1);
                return (0);
            }

            iterator find (const key_type& k){
                return (SearchNode(k));
            }

            const_iterator find (const key_type& k) const{
                return (SearchNode(k));
            }

            ft::pair<iterator,iterator> equal_range( const Key& key ){
                return ft::make_pair<iterator, iterator>(lower_bound(key), upper_bound(key));
            }

            ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const{
                return ft::make_pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
            }


        //////////////////////OBSERVERS//////////////////////////////////////////////////////////////

        key_compare key_comp() const{
            return key_compare() ;
        }

        value_compare value_comp() const{
            return value_compare(key_comp());
        }

        iterator lower_bound( const Key& key ){
            TreeNode* a = ApproximativeSearchNode(key);
            if (inferior(a->key(), key))
                a = Bigger(a);
            return (a);
        }

        const_iterator lower_bound( const Key& key ) const{
            TreeNode* a (ApproximativeSearchNode(key));
            if (inferior(a->key(), key)){
                const_iterator b(Bigger(a));
                return (b);
            }
            const_iterator b(a);
            return (b);
        }

        iterator upper_bound( const Key& key ){
            TreeNode* a = ApproximativeSearchNode(key);
            if (inferior(a->key(), key) || equal(a->key(), key))
                a = Bigger(a);
            return (a);
        }

        const_iterator upper_bound( const Key& key ) const{
            TreeNode* a = ApproximativeSearchNode(key);
            if (inferior(a->key(), key) || equal(a->key(), key)){
                const_iterator b(Bigger(a));
                return (b);
            }
            const_iterator b(a);
            return (b);
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
        typedef typename ft::map<Key, T, Compare, Alloc>::const_iterator iterator;
        return (ft::equal<iterator, iterator>(lhs.begin(), lhs.end(), rhs.begin()) && lhs.size() == rhs.size());
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator!=( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs ){
        return (!(lhs == rhs));
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator<( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs ){
        typedef typename ft::map<Key, T>::const_iterator iterator;
        return (ft::lexicographical_compare<iterator, iterator>(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator<=( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs ){
        typedef typename ft::map<Key, T>::const_iterator iterator;
        return (ft::lexicographical_compare<iterator, iterator>(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) || (rhs == lhs));
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator>( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs ){
        typedef typename ft::map< Key, T, Compare, Alloc>::const_iterator iterator;
        return (ft::lexicographical_compare<iterator, iterator>(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
    }

    template< class Key, class T, class Compare, class Alloc >
    bool operator>=( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs ){
        typedef typename ft::map<Key, T>::const_iterator iterator;
        return (ft::lexicographical_compare<iterator, iterator>(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()) || (rhs == lhs));
    }
}

#endif
