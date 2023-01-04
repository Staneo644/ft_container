#include "map.hpp"
#include <map>
#include <iterator>

#include <iostream>



#include "vector.hpp"
void testMap(){
	std::map<char,int> mymap;

	/*mymap['b']=200;
	mymap['a']=100;*/
	mymap['c']=300;
	mymap['c']=400;
	mymap['d']=400;
	std::cout << mymap.equal_range('c').first->second << mymap.equal_range('c').second->second << std::endl;
	ft::pair<int, int>mypair;
	//std::cout << (mymap.begin()->first) << " => " << (mymap.begin()->second) <<  '\n';
	ft::map<int, int> myvec;
	mymap.value_comp();
	myvec[12] = 5;
	myvec[8] = 5;
	myvec[7] = 9;
	myvec[9] = 3;
	
	myvec.insert(ft::make_pair<int, int>(4,5));
	// myvec.insert(ft::make_pair<int, int>(6,5));
	// myvec.insert(ft::make_pair<int, int>(8,5));
	// myvec.insert(ft::make_pair<int, int>(6,5));
	// myvec.insert(ft::make_pair<int, int>(9,5));
	// myvec.insert(ft::make_pair<int, int>(10,5));
	// myvec.insert(ft::make_pair<int, int>(3,2));
	//myvec.erase(12);
	
	dprintf(1, "%d\n", myvec.find(8)->second);
	//myvec.print(NULL);
	//dprintf(1, "FIN");
	//myvec.clear();
	std::cout << myvec.size() << std::endl;
	//std::cout << "Map is " << mymap.begin()->second << std::endl;
	
/*
	std::cout << myvec.begin()->second << std::endl;
	std::cout << (++myvec.begin())->second << std::endl;
*/

    struct ModCmp {
        bool operator()(const int lhs, const int rhs) const
        {
            return (lhs % 97) < (rhs % 97);
        }
    };

    ft::map<int, char> cont;
    cont[1] = 'a';
    cont[2] = 'b';
    cont[3] = 'c';
    cont[4] = 'd';
    cont[5] = 'e';
	std::cout << "Map is " << (++cont.begin())->second << std::endl;
	/*cont[7] = 'f';
	cont[6] = 'f';
	cont[8] = 'f';
	cont[18] = 'f';
	cont[17] = 'f';
	cont[16] = 'f';
    cont[15] = 'e';
    cont[14] = 'd';
    cont[13] = 'c';
    cont[12] = 'b';
    cont[11] = 'a';*/
	//cont.print();

	ft::map<int, char> con;
    con[1] = 'h';
    con[2] = 'b';
    con[3] = 'c';
    con[4] = 'd';
    con[5] = 'e';
	ft::map<int, char>::iterator It;
	It = con.begin();
	while (It != con.end())
	{
		std::cout << It->first << "\n";
		It++;
	}

	ft::vector<int> co;
	co.insert(0, 1);
	ft::vector<int>::reverse_iterator myIt;
	myIt = co.rbegin();
	while (myIt != co.rend())
	{
		std::cout << *myIt << "\n";
		myIt++;
	}

	/*ft::map<int, char>::reverse_iterator myIt;
	myIt = con.rbegin();
	while (myIt != con.rend())
	{
		std::cout << myIt->first << "\n";
		myIt++;
	}*/
	
	//std::cout << con.begin() << "\n"


	//if (con > cont)
		std::cout << " dfdsf \n";
	//std::cout << myvec.end();
	//std::reverse_iterator<int>();
}