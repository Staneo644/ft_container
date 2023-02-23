#include "../src/main.hpp"

void checkReverseIt()
{
   {
      std::cout << "Vector reverse Iterator:" << std::endl;
      ft::vector<value> vec;
      for (value i = 1 ; i < 6 ; ++i ) {
         vec.push_back(2 * i);
      }

      ft::vector<value> newVec(vec.rbegin(), vec.rend());
      ft::vector<value>::reverse_iterator unConstRevIt = newVec.rbegin();
      ft::vector<value>::const_reverse_iterator revIt(unConstRevIt);
      std::cout << "Reverse iterator : ";
      while (revIt != newVec.rend())
      {
         std::cout << *revIt << " ";
         revIt++;
      }
      std::cout << "\n\n";
      std::cout << "Before last " << *(--(newVec.rend())) << std::endl << std::endl ;
   }

   std::cout << "\n\n";

   { 
      std::cout << "Map reverse Iterator:" << std::endl;
      ft::map<value, key> map;
      for (value i = 1 ; i < 6 ; ++i ) {
         map.insert(ft::make_pair<value, key> (2 * i, i));
      }

      ft::map<value, key> newMap(map.rbegin(), map.rend());
      ft::map<value, key>::reverse_iterator unConstRevIt = newMap.rbegin();
      ft::map<value, key>::const_reverse_iterator revIt(unConstRevIt);
      std::cout << "Reverse iterator : ";
      while (revIt != newMap.rend())
      {
         std::cout << revIt->first << " ";
         revIt++;
      }
      std::cout << "\n\n";
      std::cout << "Before last " << (--(newMap.rend()))->first << std::endl << std::endl ;
   }
}