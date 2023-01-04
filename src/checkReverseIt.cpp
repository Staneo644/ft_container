#include <iterator>

#include "reverseIterator.hpp"
#include "vector.hpp"
#include <algorithm>
#include <vector>
#include <iostream>
#include <map>
void testIt()
{
   //using namespace std;
   int i;

   ft::vector<int> vec;
   for ( i = 1 ; i < 6 ; ++i )
   {
      vec.push_back ( 2 * i );
   }
   std::map<int, int>x;

   ft::vector <int>::iterator vIter;
    std::cout << "The vector vec is: ( ";
    for ( vIter = vec.begin ( ) ; vIter != vec.end ( ); vIter++ )
       std::cout << *vIter << " ";
    std::cout << ")." << std::endl;

   
   ft::reverse_iterator<ft::vector<int>::iterator > rvIter;
   std::cout << "The vector vec reversed is: ( ";
   for ( rvIter = vec.rbegin( ) ; rvIter != vec.rend( ); rvIter++)
      std::cout << *rvIter << " ";
   std::cout << ")." << std::endl;

  /* vector <int>::iterator pos, bpos;
   pos = find ( vec.begin ( ), vec.end ( ), 6 );
   cout << "The iterator pos points to: " << *pos << "." << endl;

   typedef reverse_iterator<vector<int>::iterator>::iterator_type it_vec_int_type;

   reverse_iterator<it_vec_int_type> rpos ( pos );
   cout << "The reverse_iterator rpos points to: " << *rpos
        << "." << endl;

   bpos = rpos.base ( );
   cout << "The iterator underlying rpos is bpos & it points to: "
        << *bpos << "." << endl;*/
}